# HashMap源码解析

### 一、提出问题

- 源码分析
- 数据结构
- 数组长度2^n原因
- 插入过程
- 扩容过程
- 扩容的重hash原理
- 获取过程

### 二、先从构造函数说起

#### 2.1 构造函数

```java
static final float DEFAULT_LOAD_FACTOR = 0.75f;
public HashMap() {
  	// 默认的负载因子，也就是扩容因子，默认是0.75
    this.loadFactor = DEFAULT_LOAD_FACTOR; // all other fields defaulted
}

public HashMap(Map<? extends K, ? extends V> m) {
  // 默认的负载因子，也就是扩容因子，默认是0.75
  this.loadFactor = DEFAULT_LOAD_FACTOR;
  // 标题2.2 
  putMapEntries(m, false);
}

public HashMap(int initialCapacity) {
  this(initialCapacity, DEFAULT_LOAD_FACTOR);
}

public HashMap(int initialCapacity, float loadFactor) {
  if (initialCapacity < 0)
    throw new IllegalArgumentException("Illegal initial capacity: " +
                                       initialCapacity);
  if (initialCapacity > MAXIMUM_CAPACITY)
    initialCapacity = MAXIMUM_CAPACITY;
  if (loadFactor <= 0 || Float.isNaN(loadFactor))
    throw new IllegalArgumentException("Illegal load factor: " +
                                       loadFactor);
  this.loadFactor = loadFactor;
  // 临界值的大小 总大小*负载因子
  this.threshold = tableSizeFor(initialCapacity);
}

```

#### 2.2 putMapEntries

```java
final void putMapEntries(Map<? extends K, ? extends V> m, boolean evict) {
  	// 准备存入的Map的大小
    int s = m.size();
  	// 有数据则进行存储
    if (s > 0) {
      	// 判断table是否进行了初始化
        if (table == null) { // pre-size
          	/**求出需要的容量，因为实际使用的长度=容量*0.75得来的，+1是因为小数相除，基本都不会是整数，容量大小不能为小数的，后面转换为int，多余的小数就要被丢掉，所以+1，例如，map实际长度22，22/0.75=29.3,所需要的容量肯定为30，有人会问如果刚刚好除得整数呢，除得整数的话，容量大小多1也没什么影响**/
            float ft = ((float)s / loadFactor) + 1.0F;
          	//判断该容量大小是否超出上限。
            int t = ((ft < (float)MAXIMUM_CAPACITY) ?
                     (int)ft : MAXIMUM_CAPACITY);
          	/**对临界值进行初始化，tableSizeFor(t)这个方法会返回大于t值的，且离其最近的2次幂，例如t为29，则返回的值是32**/
            if (t > threshold)
                threshold = tableSizeFor(t);
        }
        else if (s > threshold)
          	//如果table已经初始化，则进行扩容操作，resize()就是扩容。
            resize();
      	//遍历，把map中的数据转到hashMap中。
        for (Map.Entry<? extends K, ? extends V> e : m.entrySet()) {
            K key = e.getKey();
            V value = e.getValue();
            putVal(hash(key), key, value, false, evict);
        }
    }
}
```

先往下吧，位运算还是不太熟练

### 三、put(K key, V value) 

```java
public V put(K key, V value) {
  	// 计算hash值,传递Key，Value.
    return putVal(hash(key), key, value, false, true);
}

final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
                   boolean evict) {
  			//tab 哈希数组，p 该哈希桶的首节点，n hashMap的长度，i 计算出的数组下标
        Node<K,V>[] tab; Node<K,V> p; int n, i;
  			
  			// 首次的时候table是为null的，那么需要进行初始化，使用的是懒加载
        if ((tab = table) == null || (n = tab.length) == 0)
            n = (tab = resize()).length;
  			
  			// 这里不是一个else的操作。所以执行插入操作了
				// i = (n - 1) & hash进行计算插入位置，保证落在当前数组的大小范围内
        if ((p = tab[i = (n - 1) & hash]) == null)
          	// 如果所插入的位置是null的则可以直接创建一个节点
            tab[i] = newNode(hash, key, value, null);
        else {
          	// 发生hash冲突的解决方案就在这里了，细细的读一下
            Node<K,V> e; K k;
            if (p.hash == hash &&
                ((k = p.key) == key || (key != null && key.equals(k))))
           	// hash值相同，并且key相同，那么首节点匹配
                e = p;
            else if (p instanceof TreeNode)
              	// 检查首节点是否是TreeNode，如果是的话话，则进行红黑树的操作
                e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
            else {
              	// 进行链表的插入
                for (int binCount = 0; ; ++binCount) {
                  	// 如果找到尾部，则进行插入操作
                    if ((e = p.next) == null) {
                        p.next = newNode(hash, key, value, null);
                      	// 如果单条链达到 8 的长度那么转为红黑树
                        if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st
                            treeifyBin(tab, hash);
                        break;
                    }
                  	// 如果不是尾部则进行比较hash值可key值是否相等
                    if (e.hash == hash &&
                        ((k = e.key) == key || (key != null && key.equals(k))))
                        break;
                    p = e;
                }
            }
          	//有重复的key，则用待插入值进行覆盖，返回旧值。
            if (e != null) { // existing mapping for key
                V oldValue = e.value;
                if (!onlyIfAbsent || oldValue == null)
                    e.value = value;
                afterNodeAccess(e);
              	// 替换的话就直接返回了，不会存在扩容操作
                return oldValue;
            }
        }
  			// 不是替换的话，size进行增加，判断是否达到扩容的系数
        ++modCount;
        if (++size > threshold)
          	// 达到扩容系数进行扩容 3.2 
            resize();
        afterNodeInsertion(evict);
        return null;
    }
```

#### 3.1 hash值的计算

```java
static final int hash(Object key) {
int h;
return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}
```

#### 3.2  resize()扩容处理

```java
final Node<K,V>[] resize() {
    Node<K,V>[] oldTab = table;
  	// 计算旧的数组的大小
    int oldCap = (oldTab == null) ? 0 : oldTab.length;
  	// 旧的扩容大小
    int oldThr = threshold;
  		
    int newCap, newThr = 0;
    if (oldCap > 0) {
        if (oldCap >= MAXIMUM_CAPACITY) {
            threshold = Integer.MAX_VALUE;
            return oldTab;
        }
      	// 向左移动一位，相当于扩大了2倍，不可以超过最大值，oldCap也要大于16
        else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY &&
                 oldCap >= DEFAULT_INITIAL_CAPACITY)
            newThr = oldThr << 1; // double threshold
    }
  /**如果oldCap<0，但是已经初始化了，像把元素删除完之后的情况，那么它的临界值肯定还存在，        
           如果是首次初始化，它的临界值则为0
        **/  	
    else if (oldThr > 0) // initial capacity was placed in threshold
        newCap = oldThr;
    else {               // zero initial threshold signifies using defaults
        newCap = DEFAULT_INITIAL_CAPACITY;
        newThr = (int)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
    }
    if (newThr == 0) {
        float ft = (float)newCap * loadFactor;
        newThr = (newCap < MAXIMUM_CAPACITY && ft < (float)MAXIMUM_CAPACITY ?
                  (int)ft : Integer.MAX_VALUE);
    }
    threshold = newThr;
    @SuppressWarnings({"rawtypes","unchecked"})
        Node<K,V>[] newTab = (Node<K,V>[])new Node[newCap];
    table = newTab;
    if (oldTab != null) {
        for (int j = 0; j < oldCap; ++j) {
            Node<K,V> e;
            if ((e = oldTab[j]) != null) {
                oldTab[j] = null;
                if (e.next == null)
                  	//把该变量的值存入newCap中，e.hash & (newCap - 1)并不等于j
                    newTab[e.hash & (newCap - 1)] = e;
                else if (e instanceof TreeNode)
                  	//该节点为红黑树结构，也就是存在哈希冲突，该哈希桶中有多个元素
                    ((TreeNode<K,V>)e).split(this, newTab, j, oldCap);
                else { // 这个链表的操作没有弄懂，再看
                    Node<K,V> loHead = null, loTail = null;
                    Node<K,V> hiHead = null, hiTail = null;
                    Node<K,V> next;
                    do {
                        next = e.next;
                        if ((e.hash & oldCap) == 0) {
                            if (loTail == null)
                                loHead = e;
                            else
                                loTail.next = e;
                            loTail = e;
                        }
                        else {
                            if (hiTail == null)
                                hiHead = e;
                            else
                                hiTail.next = e;
                            hiTail = e;
                        }
                    } while ((e = next) != null);
                    if (loTail != null) {
                        loTail.next = null;
                        newTab[j] = loHead;
                    }
                    if (hiTail != null) {
                        hiTail.next = null;
                        newTab[j + oldCap] = hiHead;
                    }
                }
            }
        }
    }
    return newTab;
}
```

### 四、get

```java
public V get(Object key) {
  Node<K,V> e;
  // 计算hash值和传入key值
  return (e = getNode(hash(key), key)) == null ? null : e.value;
}

final Node<K,V> getNode(int hash, Object key) {
  Node<K,V>[] tab; Node<K,V> first, e; int n; K k;
  // 判断table数组是初始化了的，并且计算插入位置，判断位置的数据不为null
  if ((tab = table) != null && (n = tab.length) > 0 &&
      (first = tab[(n - 1) & hash]) != null) {
    // 判断首位是否匹配
    if (first.hash == hash && // always check first node
        ((k = first.key) == key || (key != null && key.equals(k))))
      return first;
    if ((e = first.next) != null) {
      // 判断首位是否是树的节点
      if (first instanceof TreeNode)
        return ((TreeNode<K,V>)first).getTreeNode(hash, key);
      do {
        // 进行遍历判断
        if (e.hash == hash &&
            ((k = e.key) == key || (key != null && key.equals(k))))
          return e;
      } while ((e = e.next) != null);
    }
  }
  return null;
}
```



#### 参考

https://zhuanlan.zhihu.com/p/72381837

https://zhuanlan.zhihu.com/p/100250328