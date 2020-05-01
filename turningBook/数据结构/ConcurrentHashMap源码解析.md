# ConcurrentHashMap源码学习

一直以为了解了，大概的ConcurrentHashMap，然而并不是，那么重新学习一下，在这个过程中遇到什么没见过的，就详细的查查资料看一下。

#### 一、从构造方法说起

#### 1.1第一个是空的实现

```java
public ConcurrentHashMap() {
}
```

#### 1.2第二个有一个参数

```java
private static final int MAXIMUM_CAPACITY = 1 << 30;
private transient volatile int sizeCtl;

// initialCapacity 设置初始容量
public ConcurrentHashMap(int initialCapacity) {
    if (initialCapacity < 0)
        throw new IllegalArgumentException();
  	// 初始容量和最大支持容量相比较最大容量2^30，如果大于就用最大值否则的话做了一个计算
    int cap = ((initialCapacity >= (MAXIMUM_CAPACITY >>> 1)) ?
               MAXIMUM_CAPACITY :
               // 先不纠结这了// 1.2.1
               tableSizeFor(initialCapacity + (initialCapacity >>> 1) + 1));
  	// 对表初始化和扩容控制					 
    this.sizeCtl = cap;
}
```

##### 1.2.1 tableSizeFor(initialCapacity + (initialCapacity >>> 1) + 1))

```java
private static final int tableSizeFor(int c) {
  	// 位运算，距离感0100 1000， 不断的移动则会得到 0111 1111，当前大小的最距离2^n-1最近的值
    int n = c - 1;
    n |= n >>> 1;
    n |= n >>> 2;
    n |= n >>> 4;
    n |= n >>> 8;
    n |= n >>> 16;
    return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}
```

### 1.3第三个可以传入一个Map

```java
private static final int DEFAULT_CAPACITY = 16;
// hashmap里面可不是这么写的 1<<<3
public ConcurrentHashMap(Map<? extends K, ? extends V> m) {
  	// 默认的容量大小 16
    this.sizeCtl = DEFAULT_CAPACITY;
  	// 设置值了，// 1.3.1
    putAll(m);
}
```

##### 1.3.1 putAll(m)

```java
public void putAll(Map<? extends K, ? extends V> m) {
 		 // 1.3.2  做了初始化Node数组大小的操作判断
  	tryPresize(m.size());
    for (Map.Entry<? extends K, ? extends V> e : m.entrySet())
      	// 这个是单个值的设置，之后再看需要详细的去看一下
        putVal(e.getKey(), e.getValue(), false);
}
```

##### 1.3.2tryPresize(int size)

```java
private static final sun.misc.Unsafe U = sun.misc.Unsafe.getUnsafe();
private static final long SIZECTL;

private final void tryPresize(int size) {
  	// 这个和之前的相同，初始化大小
    int c = (size >= (MAXIMUM_CAPACITY >>> 1)) ? MAXIMUM_CAPACITY :
        tableSizeFor(size + (size >>> 1) + 1);
    int sc;
  	// 为什么是一个循环，Unsafe这种锁
    while ((sc = sizeCtl) >= 0) {
      	// 看到现在首次看到Node这个数据结构，很明显的看到是一个Node数组
        Node<K,V>[] tab = table; int n;
      	// tab == null 说明是首次初始化，执行初始化的操作
        if (tab == null || (n = tab.length) == 0) {
          	// sc sizeCtl的初始化要比c这个值早，所以选择合适的大小
            n = (sc > c) ? sc : c;
          	// U是啥玩意，遇到可新大陆Unsafe详细的了解一下
          	// SIZECTL 这个值是final的不知道用来做什么，所以从Unsafe是什么
          	// 1.3.3
            if (U.compareAndSwapInt(this, SIZECTL, sc, -1)) {
                try {
                    if (table == tab) {
                      	// 首次初始化创建一个table
                        @SuppressWarnings("unchecked")
                        Node<K,V>[] nt = (Node<K,V>[])new Node<?,?>[n];
                        table = nt;
                        sc = n - (n >>> 2);
                    }
                } finally {
                  	// 更新大小
                    sizeCtl = sc;
                }
            }
        }
      	// 已经初始化过了，判断一下是否已经满足了那么这个过程就可以跳过了
        else if (c <= sc || n >= MAXIMUM_CAPACITY)
            break;
        else if (tab == table) {
            int rs = resizeStamp(n);
            if (U.compareAndSwapInt(this, SIZECTL, sc,
                                    (rs << RESIZE_STAMP_SHIFT) + 2))
              	// 这先不看了，先看主要流程，之后再看
                transfer(tab, null);
        }
    }
}
```

#### 1.4 Node

```java
// 和hash参数差不多，但是大多数都增加了线程安全相关的修饰，而且值是不可变的
static class Node<K,V> implements Map.Entry<K,V> {
    final int hash;
    final K key;
    volatile V val;
    volatile Node<K,V> next;

    Node(int hash, K key, V val, Node<K,V> next) {
        this.hash = hash;
        this.key = key;
        this.val = val;
        this.next = next;
    }

    public final K getKey()     { return key; }
    public final V getValue()   { return val; }
    public final int hashCode() { return key.hashCode() ^ val.hashCode(); }
    public final String toString() {
        return Helpers.mapEntryToString(key, val);
    }
    public final V setValue(V value) {
        throw new UnsupportedOperationException();
    }
}
```





### 二、Unsafe

java提供的一个直接操控内存和线程的底层操作，

#### 2.1 U.compareAndSwapInt简称CAS

```java
// 这里是有四个参数
// 读取传入变量var1在内存中的偏移量位var2，并且与期望值var4进行比较，相等的话就吧var5赋值给var2，否则就返回false
public final native boolean compareAndSwapInt(Object var1, long var2, int var4, int var5);
U.compareAndSwapInt(this, SIZECTL, sc,(rs << RESIZE_STAMP_SHIFT) + 2)
```

至此初始化中的内容就已经完成了

### 三、put(K key, V value)

```java
public V put(K key, V value) {
  return putVal(key, value, false);
}

/** Implementation for put and putIfAbsent */
final V putVal(K key, V value, boolean onlyIfAbsent) {
  	// key和value都不能为null
    if (key == null || value == null) throw new NullPointerException();
  	// 计算hash值，此刻还没有定位到要插入到哪个位置
    int hash = spread(key.hashCode());
    int binCount = 0;
  	// 这里又是一个循环死循环，估计还是UnSafe的CAS问题
    for (Node<K,V>[] tab = table;;) {
        Node<K,V> f; int n, i, fh;
      	// 这里和HashMap有点不同，都死if else关系，首次也是执行可懒加载
        if (tab == null || (n = tab.length) == 0)
          	// 3.1 懒加载初始化table，初始化完成，执行下一次循环
            tab = initTable();
      	// tabAt(tab, i = (n - 1) & hash))这里确定插入的位置 // 3.2
        else if ((f = tabAt(tab, i = (n - 1) & hash)) == null) {
          	// 进行比较赋值操作
            if (casTabAt(tab, i, null,
                         new Node<K,V>(hash, key, value, null)))
                break;                   // no lock when adding to empty bin
        }
        else if ((fh = f.hash) == MOVED)
          	// 3.3 // 如果正在调整大小有助于传输，不知道干了什么，现在去看看
            tab = helpTransfer(tab, f);
        else {
          	// 这一定是发生了Hash冲突了
            V oldVal = null;
          	// 对当前这个头节点进行加锁，类似于1.8之前的segment，也属于分段的一种
            synchronized (f) {
              	// 判断头节点是否相等，还是二次确认，不相同就放弃
                if (tabAt(tab, i) == f) {
                  	// 大于0不懂看后面，再回来分析
                  	// fh是f.hash，也就是存在头节点，原来TreeBin里面存储的是TreeNode
                  	// TreeBin的hash为-2
                    if (fh >= 0) {
                        binCount = 1;
                        for (Node<K,V> e = f;; ++binCount) {
                            K ek;
                            if (e.hash == hash &&
                                ((ek = e.key) == key ||
                                 (ek != null && key.equals(ek)))) {
                              	// 替换过程
                                oldVal = e.val;
                                if (!onlyIfAbsent)
                                    e.val = value;
                                break;
                            }
                            Node<K,V> pred = e;
                            if ((e = e.next) == null) {
                              	// 创建新的过程
                                pred.next = new Node<K,V>(hash, key,
                                                          value, null);
                                break;
                            }
                        }
                    }
                  	// 如果是一个树节点则进行树节点的插入
                    else if (f instanceof TreeBin) {
                        Node<K,V> p;
                        binCount = 2;
                        if ((p = ((TreeBin<K,V>)f).putTreeVal(hash, key,
                                                       value)) != null) {
                            oldVal = p.val;
                            if (!onlyIfAbsent)
                                p.val = value;
                        }
                    }
                  	// 这又是个什么node奇怪
                    else if (f instanceof ReservationNode)
                        throw new IllegalStateException("Recursive update");
                }
            }
            if (binCount != 0) {
              	// 单条链上超过8个
                if (binCount >= TREEIFY_THRESHOLD)
                  	// 转化成树 // 3.4
                    treeifyBin(tab, i);
                if (oldVal != null)
                    return oldVal;
                break;
            }
        }
    }
  	// 走到这说明是一个插入的操作
    addCount(1L, binCount);
    return null;
}
```

####  3.1 initTable

```java
private final Node<K,V>[] initTable() {
    Node<K,V>[] tab; int sc;
    while ((tab = table) == null || tab.length == 0) {
        if ((sc = sizeCtl) < 0)
          	// 放弃执行时间片的时间，把自己放到同优先级等待队列的队尾，等待同优先级的
          	// 线程调度完成后才能获得执行机会
            Thread.yield(); // lost initialization race; just spin
        else if (U.compareAndSwapInt(this, SIZECTL, sc, -1)) {
            try {
              	// 初始化大小并进行赋值
              	// 双重判断，保证只初始化一次
                if ((tab = table) == null || tab.length == 0) {
                    int n = (sc > 0) ? sc : DEFAULT_CAPACITY;
                    @SuppressWarnings("unchecked")
                    Node<K,V>[] nt = (Node<K,V>[])new Node<?,?>[n];
                    table = tab = nt;
                    sc = n - (n >>> 2);
                }
            } finally {
                sizeCtl = sc;
            }
            break;
        }
    }
    return tab;
}
```

#### 3.2 tabAt(Node<K,V>[] tab, int i)

```java
@SuppressWarnings("unchecked")
static final <K,V> Node<K,V> tabAt(Node<K,V>[] tab, int i) {
  	// 获取指定位置的值，能保证可见性
    return (Node<K,V>)U.getObjectVolatile(tab, ((long)i << ASHIFT) + ABASE);
}
```

#### 3.3 helpTransfer(Node<K,V>[] tab, Node<K,V> f)

```java
/**
 * Helps transfer if a resize is in progress.
 */
final Node<K,V>[] helpTransfer(Node<K,V>[] tab, Node<K,V> f) {
  	// 第一个参数是table，第二个参数是某一个数组位置的头节点
    Node<K,V>[] nextTab; int sc;
  	// 在这的疑问是为什么会是 ForwardingNode，还是再看看吧
    if (tab != null && (f instanceof ForwardingNode) &&
        (nextTab = ((ForwardingNode<K,V>)f).nextTable) != null) {
        int rs = resizeStamp(tab.length);
        while (nextTab == nextTable && table == tab &&
               (sc = sizeCtl) < 0) {
          	// 不断遍历，直到可以增添节点
            if ((sc >>> RESIZE_STAMP_SHIFT) != rs || sc == rs + 1 ||
                sc == rs + MAX_RESIZERS || transferIndex <= 0)
                break;
            if (U.compareAndSwapInt(this, SIZECTL, sc, sc + 1)) {
              	// 这个方法看来很对地方用啊
                transfer(tab, nextTab);
                break;
            }
        }
        return nextTab;
    }
    return table;
}
```

#### 3.4 treeifyBin(Node<K,V>[] tab, int index)

```java
private final void treeifyBin(Node<K,V>[] tab, int index) {
    Node<K,V> b; int n;
    if (tab != null) {
        if ((n = tab.length) < MIN_TREEIFY_CAPACITY)
            tryPresize(n << 1);
        else if ((b = tabAt(tab, index)) != null && b.hash >= 0) {
            synchronized (b) {
                if (tabAt(tab, index) == b) {
                    TreeNode<K,V> hd = null, tl = null;
                    for (Node<K,V> e = b; e != null; e = e.next) {
                        TreeNode<K,V> p =
                            new TreeNode<K,V>(e.hash, e.key, e.val,
                                              null, null);
                        if ((p.prev = tl) == null)
                            hd = p;
                        else
                            tl.next = p;
                        tl = p;
                    }
                    setTabAt(tab, index, new TreeBin<K,V>(hd));
                }
            }
        }
    }
}
```

现在整个插入流程应该已经清晰了，接下来看看addcount做了什么



#### 3.5addCount(long x, int check)

```java
//check if <0, don't check resize, if <= 1 only check if uncontended
private final void addCount(long x, int check) {
    CounterCell[] as; long b, s;
  	// counterCells 不知道是什么
    if ((as = counterCells) != null ||
        !U.compareAndSwapLong(this, BASECOUNT, b = baseCount, s = b + x)) {
        CounterCell a; long v; int m;
        boolean uncontended = true;
        if (as == null || (m = as.length - 1) < 0 ||
            (a = as[ThreadLocalRandom.getProbe() & m]) == null ||
            !(uncontended =
              U.compareAndSwapLong(a, CELLVALUE, v = a.value, v + x))) {
            fullAddCount(x, uncontended);
            return;
        }
      
        if (check <= 1)
            return;
        s = sumCount();
    }
  	// 尝试扩容
    if (check >= 0) {
        Node<K,V>[] tab, nt; int n, sc;
        while (s >= (long)(sc = sizeCtl) && (tab = table) != null &&
               (n = tab.length) < MAXIMUM_CAPACITY) {
            int rs = resizeStamp(n);
            if (sc < 0) {
                if ((sc >>> RESIZE_STAMP_SHIFT) != rs || sc == rs + 1 ||
                    sc == rs + MAX_RESIZERS || (nt = nextTable) == null ||
                    transferIndex <= 0)
                    break;
                if (U.compareAndSwapInt(this, SIZECTL, sc, sc + 1))
                    transfer(tab, nt);
            }
            else if (U.compareAndSwapInt(this, SIZECTL, sc,
                                         (rs << RESIZE_STAMP_SHIFT) + 2))
                transfer(tab, null);
            s = sumCount();
        }
    }
}
```



### 四 get(Object key)

```java
public V get(Object key) {
    Node<K,V>[] tab; Node<K,V> e, p; int n, eh; K ek;
    int h = spread(key.hashCode());
    if ((tab = table) != null && (n = tab.length) > 0 &&
        (e = tabAt(tab, (n - 1) & h)) != null) {
      	// 是不是首位
        if ((eh = e.hash) == h) {
            if ((ek = e.key) == key || (ek != null && key.equals(ek)))
                return e.val;
        }
      	// 是不是树
        else if (eh < 0)
            return (p = e.find(h, key)) != null ? p.val : null;
      	// 进行链表的遍历
        while ((e = e.next) != null) {
            if (e.hash == h &&
                ((ek = e.key) == key || (ek != null && key.equals(ek))))
                return e.val;
        }
    }
    return null;
}
```

突然产生了一个疑问，ConcurrentHashMap如何能保证主线程不会因为阻塞而ANR的呢，再细看看



### 是时候看一下 transfer(tab, null);做了什么

```java
private final void transfer(Node<K,V>[] tab, Node<K,V>[] nextTab) {
    int n = tab.length, stride;
    if ((stride = (NCPU > 1) ? (n >>> 3) / NCPU : n) < MIN_TRANSFER_STRIDE)
        stride = MIN_TRANSFER_STRIDE; // subdivide range
    if (nextTab == null) {            // initiating
        try {
            @SuppressWarnings("unchecked")
            Node<K,V>[] nt = (Node<K,V>[])new Node<?,?>[n << 1];
            nextTab = nt;
        } catch (Throwable ex) {      // try to cope with OOME
            sizeCtl = Integer.MAX_VALUE;
            return;
        }
        nextTable = nextTab;
        transferIndex = n;
    }
    int nextn = nextTab.length;
    ForwardingNode<K,V> fwd = new ForwardingNode<K,V>(nextTab);
    boolean advance = true;
    boolean finishing = false; // to ensure sweep before committing nextTab
    for (int i = 0, bound = 0;;) {
        Node<K,V> f; int fh;
        while (advance) {
            int nextIndex, nextBound;
            if (--i >= bound || finishing)
                advance = false;
            else if ((nextIndex = transferIndex) <= 0) {
                i = -1;
                advance = false;
            }
            else if (U.compareAndSwapInt
                     (this, TRANSFERINDEX, nextIndex,
                      nextBound = (nextIndex > stride ?
                                   nextIndex - stride : 0))) {
                bound = nextBound;
                i = nextIndex - 1;
                advance = false;
            }
        }
        if (i < 0 || i >= n || i + n >= nextn) {
            int sc;
            if (finishing) {
                nextTable = null;
                table = nextTab;
                sizeCtl = (n << 1) - (n >>> 1);
                return;
            }
            if (U.compareAndSwapInt(this, SIZECTL, sc = sizeCtl, sc - 1)) {
                if ((sc - 2) != resizeStamp(n) << RESIZE_STAMP_SHIFT)
                    return;
                finishing = advance = true;
                i = n; // recheck before commit
            }
        }
        else if ((f = tabAt(tab, i)) == null)
            advance = casTabAt(tab, i, null, fwd);
        else if ((fh = f.hash) == MOVED)
            advance = true; // already processed
        else {
            synchronized (f) {
                if (tabAt(tab, i) == f) {
                    Node<K,V> ln, hn;
                    if (fh >= 0) {
                        int runBit = fh & n;
                        Node<K,V> lastRun = f;
                        for (Node<K,V> p = f.next; p != null; p = p.next) {
                            int b = p.hash & n;
                            if (b != runBit) {
                                runBit = b;
                                lastRun = p;
                            }
                        }
                        if (runBit == 0) {
                            ln = lastRun;
                            hn = null;
                        }
                        else {
                            hn = lastRun;
                            ln = null;
                        }
                        for (Node<K,V> p = f; p != lastRun; p = p.next) {
                            int ph = p.hash; K pk = p.key; V pv = p.val;
                            if ((ph & n) == 0)
                                ln = new Node<K,V>(ph, pk, pv, ln);
                            else
                                hn = new Node<K,V>(ph, pk, pv, hn);
                        }
                        setTabAt(nextTab, i, ln);
                        setTabAt(nextTab, i + n, hn);
                        setTabAt(tab, i, fwd);
                        advance = true;
                    }
                    else if (f instanceof TreeBin) {
                        TreeBin<K,V> t = (TreeBin<K,V>)f;
                        TreeNode<K,V> lo = null, loTail = null;
                        TreeNode<K,V> hi = null, hiTail = null;
                        int lc = 0, hc = 0;
                        for (Node<K,V> e = t.first; e != null; e = e.next) {
                            int h = e.hash;
                            TreeNode<K,V> p = new TreeNode<K,V>
                                (h, e.key, e.val, null, null);
                            if ((h & n) == 0) {
                                if ((p.prev = loTail) == null)
                                    lo = p;
                                else
                                    loTail.next = p;
                                loTail = p;
                                ++lc;
                            }
                            else {
                                if ((p.prev = hiTail) == null)
                                    hi = p;
                                else
                                    hiTail.next = p;
                                hiTail = p;
                                ++hc;
                            }
                        }
                        ln = (lc <= UNTREEIFY_THRESHOLD) ? untreeify(lo) :
                            (hc != 0) ? new TreeBin<K,V>(lo) : t;
                        hn = (hc <= UNTREEIFY_THRESHOLD) ? untreeify(hi) :
                            (lc != 0) ? new TreeBin<K,V>(hi) : t;
                        setTabAt(nextTab, i, ln);
                        setTabAt(nextTab, i + n, hn);
                        setTabAt(tab, i, fwd);
                        advance = true;
                    }
                }
            }
        }
    }
}
```

### 优势

1.它进行的不是整体的扩容，而是单独 对Segment进行扩容

2.因为不再使用Segment，初始化操作大大简化，修改为lazy-load形式，这样可以有效避免初始开销，解决了老版本很多人抱怨的这一点。

3.数据存储利用volatile来保证可见性。

4.使用CAS等操作，在特定场景进行无锁并发操作。

5.使用Unsafe、LongAdder之类底层手段，进行极端情况的优化。



#### 参考：

https://www.cnblogs.com/loading4/p/6239441.html

https://www.cnblogs.com/java-chen-hao/p/10327280.html

https://www.cnblogs.com/CherryTab/p/12169045.html