# Android消息机制
ThreadLocal、Handler、MessageQueue、Looper源码解析
## 一、Android消息机制

先从一个实例说起

```java
    class LooperThread extends Thread {
        public Handler mHandler;

        public void run() {
            Looper.prepare();

            mHandler = new Handler() {
                public void handleMessage(Message msg) {
                    // process incoming messages here
                }
            };

            Looper.loop();
        }
    }
```

## 二、从线程中的Looper源码分析

#### 2.1初始化 Looper.prepare()

```java
// ThreadLocal 是一个全局的静态的不可变对象
static final ThreadLocal<Looper> sThreadLocal = new ThreadLocal<Looper>();

public static void prepare() {
    prepare(true);
}
// quitAllowed参数是否准许退出，主线程的是false，其他的是true
private static void prepare(boolean quitAllowed) {
  	// 只准许初始化一次
    if (sThreadLocal.get() != null) {
        throw new RuntimeException("Only one Looper may be created per thread");
    }
  	// 将创建的lopper存放到ThreadLocal中
    sThreadLocal.set(new Looper(quitAllowed));
}
```

##### 2.1.1构造方法 new Looper(quitAllowed)

```java
private Looper(boolean quitAllowed) {
  	// 初始化MessageQueue，quitAllowed这个参数传递到了MessageQueue,之后详细看一下
    mQueue = new MessageQueue(quitAllowed);
    mThread = Thread.currentThread();
}
```
#### 2.2同prepare()还有prepareMainLooper()

```java
// 强引用的主线程Lopper
private static Looper sMainLooper;  // guarded by Looper.class
// 主线程进行初始化的时候进行调用
public static void prepareMainLooper() {
  	// 主线程传递的参数是false，不准许退出
    prepare(false);
    synchronized (Looper.class) {
        if (sMainLooper != null) {
            throw new IllegalStateException("The main Looper has already been prepared.");
        }
      	// 将创建的Lopper指向一个强引用
        sMainLooper = myLooper();
    }
}

public static @Nullable Looper myLooper() {
  	// 从sThreadLocal获取你存入的Looper对象
		return sThreadLocal.get();
}
// 可以通过该方法获取主线程的Looper
public static Looper getMainLooper() {
    synchronized (Looper.class) {
        return sMainLooper;
    }
}
```

#### 2.3开启Looper的循环 Looper.loop();

```java
public static void loop() {
  	// 获取ThreadLocal中存储的Lopper对象
    final Looper me = myLooper();
    if (me == null) {
        throw new RuntimeException("没有Lopper会抛出异常");
    }
  	// 获取Lopper中的消息队列
    final MessageQueue queue = me.mQueue;
		// 重置当前线程上传入的IPC身份，C层的不太了解，之后必须学习C++了
    Binder.clearCallingIdentity();
    final long ident = Binder.clearCallingIdentity();

    for (;;) {
      	// 获取消息
        Message msg = queue.next();
      	//如果消息为null。那么相当于进行退出
        if (msg == null) {
            return;
        }

        // 默认为null，可通过setMessageLogging()方法来指定输出，用于debug功能
        final Printer logging = me.mLogging;
        if (logging != null) {
            logging.println(">>>>> Dispatching to " + msg.target + " " +
                    msg.callback + ": " + msg.what);
        }
				
      	//如果设置，则如果消息分发花费的时间超过时间，则循环程序将显示警告日志。
        final long slowDispatchThresholdMs = me.mSlowDispatchThresholdMs;

        final long traceTag = me.mTraceTag;
        if (traceTag != 0 && Trace.isTagEnabled(traceTag)) {
            Trace.traceBegin(traceTag, msg.target.getTraceName(msg));
        }
        final long start = (slowDispatchThresholdMs == 0) ? 0 : SystemClock.uptimeMillis();
        final long end;
        try {
          	// target就是发送消息的handler，对handler发送的事件进行分发
            msg.target.dispatchMessage(msg);
            end = (slowDispatchThresholdMs == 0) ? 0 : SystemClock.uptimeMillis();
        } finally {
            if (traceTag != 0) {
                Trace.traceEnd(traceTag);
            }
        }
        if (slowDispatchThresholdMs > 0) {
            final long time = end - start;
            if (time > slowDispatchThresholdMs) {
                Slog.w(TAG, "Dispatch took " + time + "ms on "
                        + Thread.currentThread().getName() + ", h=" +
                        msg.target + " cb=" + msg.callback + " msg=" + msg.what);
            }
        }

        if (logging != null) {
            logging.println("<<<<< Finished to " + msg.target + " " + msg.callback);
        }

        // 恢复调用者信息
        final long newIdent = Binder.clearCallingIdentity();
        if (ident != newIdent) {
            Log.wtf(TAG, "Thread identity changed from 0x"
                    + Long.toHexString(ident) + " to 0x"
                    + Long.toHexString(newIdent) + " while dispatching to "
                    + msg.target.getClass().getName() + " "
                    + msg.callback + " what=" + msg.what);
        }
				// 将Message放入消息池中
        msg.recycleUnchecked();
    }
}
```

####2.4 退出Looper.quit()

```java
public void quit() {
  	// 调用MessageQueue的quit方法，参数为false
    mQueue.quit(false);
}

public void quitSafely() {
  	// 调用MessageQueue的quit方法，参数为true
    mQueue.quit(true);
}
```

#### Looper总结

- Looper是用来做什么的
  - prepare()创建Looper并放入ThreadLocal中
  - 开启循环不断的从MessageQueue.next()获取消息
  - 当获取消息不为null时进行消息的分发msg.target.dispatchMessage(msg);



- Looper可能存在的问题
  - 为什么主线程是不能退出的？
  - Looper会一直循环吗？
  - 主线程Looper为什么会指向一个强引用
  - ThreadLocal是如何保证Looper的唯一性的
  - dispatchMessage(msg)事件分发内部是如何处理的
  - 重置IPC身份内部都做了什么事情



- 接下来的分析顺序将会按照Looper用到的顺序进行分析
  - ThreadLocal是个什么
  - Handler如何进行消息发送，并且如何处理Looper的事件分发
  - MessageQueue都做了什么
  - Message的消息池到底是什么

## 三、ThreadLocal源码解析

### 3.1 使用位置

Thread是Lopper中的全局变量，保证当前线程可以拿到唯一的Lopper

```java
public final class Looper {
    // ...
    static final ThreadLocal<Looper> sThreadLocal = new ThreadLocal<Looper>();
    // ...
```

#### 3.2构造方法

```java
// 构造方法是个空的，没有做什么事情
public ThreadLocal() {
}
```

#### 3.3 存入值sThreadLocal.set(new Looper(quitAllowed));

```java
	 public void set(T value) {
        Thread t = Thread.currentThread();
        // 获取当前线程存储的map, ThreadLocalMap
        ThreadLocalMap map = getMap(t);
        if (map != null)
          	// ThreadLocalMap不为null 就以ThreadLocal为key将值进行存储
            map.set(this, value);
        else
          	// 否则map为null，则创建map，并以ThreadLocal为key将值进行存储
            createMap(t, value);
    }

    ThreadLocalMap getMap(Thread t) {
      	// getMap 就是Thread的里面的一个全局变量threadLocals
        return t.threadLocals;
    }

    void createMap(Thread t, T firstValue) {
      	// 创建了一个ThreadLocalMap并将并以ThreadLocal为key将值进行存储
        t.threadLocals = new ThreadLocalMap(this, firstValue);
    }

```

- 这里会看到一个ThreadLocalMap的存储数据的类，说完ThreadLocal的主要接口后对ThreadLocalMap有一个细致的分析

#### 3.4获取值sThreadLocal.get()

```java
public T get() {
    Thread t = Thread.currentThread();
  	// 与set一样先获取map
    ThreadLocalMap map = getMap(t);
    if (map != null) {
      	// ThreadLocalMap不为null则以当前ThreadLocal为key获取值
        ThreadLocalMap.Entry e = map.getEntry(this);
        if (e != null) {
          	// 获取到的值不为null则讲值进行返回
            @SuppressWarnings("unchecked")
            T result = (T)e.value;
            return result;
        }
    }
  	// 如果map为null，或者获取的值为null，则进行初始化
    return setInitialValue();
}

private T setInitialValue() {
  	// initialValue 返回了一个null，看来这个ThreadLocalMap是可以存放null值的
    T value = initialValue();
    Thread t = Thread.currentThread();
    ThreadLocalMap map = getMap(t);
    if (map != null)
      	// 与之前类似
        map.set(this, value);
    else
      	// 与之前类似
        createMap(t, value);
    return value;
}

protected T initialValue() {
	return null;
}

```

- ThreadLocal主要做了什么事情
  - get方法中，获取Thread中的ThreadLocalMap，不存在则创建，如果map存在则以当前ThreadLocal为key查询，查询不到则新创建一个ThreadLocal为key值为null的键值对，并返回null
  - set方法中,获取Thread中的ThreadLocalMap，不存在则创建，如果map存在则以当前ThreadLocal为key进行存储

- ThreadLocalMap是其中的主要存储方式，那么接下来先对ThreadLocalMap进行分析

#### 3.4ThreadLocalMap源码分析

###### 3.4.1构造方法

```java
private static final int INITIAL_CAPACITY = 16;

ThreadLocalMap(ThreadLocal<?> firstKey, Object firstValue) {
  	// ThreadLocalMap的数据结构 Entry[] table的数据，默认大小是16
    table = new Entry[INITIAL_CAPACITY];
  	// 计算存储位置
    int i = firstKey.threadLocalHashCode & (INITIAL_CAPACITY - 1);
    table[i] = new Entry(firstKey, firstValue);
    size = 1;
  	// 设置扩容阈值
    setThreshold(INITIAL_CAPACITY);
}
```

###### 3.4.2一些公用方法

```java
        // 扩容因子是长度2/3
				private void setThreshold(int len) {
            threshold = len * 2 / 3;
        }

				// 获取下一个值，如果下一个值大于len那么，就取表中的第一个值
        private static int nextIndex(int i, int len) {
            return ((i + 1 < len) ? i + 1 : 0);
        }

       	// 获取前一个位置 如果位置<0则取最后一个值
        private static int prevIndex(int i, int len) {
            return ((i - 1 >= 0) ? i - 1 : len - 1);
        }
```

###### 3.4.3数据结构

```java
static class Entry extends WeakReference<ThreadLocal<?>> {
    /** The value associated with this ThreadLocal. */
    Object value;
		// key ThreadLocal弱引用，value是全局变量
    Entry(ThreadLocal<?> k, Object v) {
        super(k);
        value = v;
    }
}
```

**弱引用**

弱引用有两个指向，一个是弱引用的指向，一个是强引用的指向，如果强引用的指向为null，那么弱引用会在GC的时候进行回收。

ThreadLocalMap的生命周期和Thread是相同的，ThreadLocal可能会没有强引用可达，那么就需要被回收

###### 3.4.4 获取值 ThreadLocalMap ->getEntry(ThreadLocal<?> key)

```java
private Entry getEntry(ThreadLocal<?> key) {
    int i = key.threadLocalHashCode & (table.length - 1);
    Entry e = table[i];
  	// 如果不为null，并且key值相等的话，那么就代表已经命中可以进行返回 
    if (e != null && e.get() == key)
        return e;
    else
      	// 没有直接命中，线性探测法向后查询
        return getEntryAfterMiss(key, i, e);
}

private Entry getEntryAfterMiss(ThreadLocal<?> key, int i, Entry e) {
    Entry[] tab = table;
    int len = tab.length;
		// 基于线性探测不断的向后探测，直到遇到null
    while (e != null) {
      	// 弱引用获取值
        ThreadLocal<?> k = e.get();
      	// 找到目标
        if (k == key)
            return e;
        if (k == null)
          	// 将已经回收的进行清理
            expungeStaleEntry(i);
        else
          	// 没有匹配到，并且没有被回收，遍历下一个位置
            i = nextIndex(i, len);
        e = tab[i];
    }
  	// 没有匹配到返回null
    return null;
}


private int expungeStaleEntry(int staleSlot) {
    Entry[] tab = table;
    int len = tab.length;

    // expunge entry at staleSlot
  	// 清理当前的位置
    tab[staleSlot].value = null;
    tab[staleSlot] = null;
    size--;

    // Rehash until we encounter null
  	// 进行重新hash
    Entry e;
    int i;
  	// 当tab[i]位置不为Null的时候进行重新排位置
    for (i = nextIndex(staleSlot, len);
         (e = tab[i]) != null;
         i = nextIndex(i, len)) {
        ThreadLocal<?> k = e.get();
      	// 获取i位置的值，如果被回收了就会进行清理
        if (k == null) {
            e.value = null;
            tab[i] = null;
            size--;
        } else {
          	// 如果没有被回收 通过线性探测重新安排它的位置
            int h = k.threadLocalHashCode & (len - 1);
            if (h != i) {
                tab[i] = null;

                // Unlike Knuth 6.4 Algorithm R, we must scan until
                // null because multiple entries could have been stale.
              // 找到重新hash位置，线性探测到为null的位置  
              while (tab[h] != null)
                    h = nextIndex(h, len);
                tab[h] = e;
            }
        }
    }
    return i;
}

```

```java
int i = key.threadLocalHashCode & (table.length - 1);
```

###### 3.4.5 ThreadLocalMap ->set(ThreadLocal<?> key, Object value)

```java
private void set(ThreadLocal<?> key, Object value) {

    Entry[] tab = table;
    int len = tab.length;
    int i = key.threadLocalHashCode & (len-1);

    for (Entry e = tab[i];
         e != null;
         e = tab[i = nextIndex(i, len)]) {
        ThreadLocal<?> k = e.get();
				// 进行线性探测
      	// 如果已经存在这个key ThreadLocal，那么将Value进行替换并结束
        if (k == key) {
            e.value = value;
            return;
        }
				// 如果之前存入的值已经失效，则进行替换
        if (k == null) {
            replaceStaleEntry(key, value, i);
            return;
        }
    }

    tab[i] = new Entry(key, value);
    int sz = ++size;
  	// 清理成功的话则不进行扩容，否则超过阈值则进行扩容
    if (!cleanSomeSlots(i, sz) && sz >= threshold)
        rehash();
}

private void replaceStaleEntry(ThreadLocal<?> key, Object value,
                               int staleSlot) {
    Entry[] tab = table;
    int len = tab.length;
    Entry e;

    int slotToExpunge = staleSlot;
  	// 向前探测知道遇到为null的
    for (int i = prevIndex(staleSlot, len);
         (e = tab[i]) != null;
         i = prevIndex(i, len))
        if (e.get() == null)
            slotToExpunge = i;

		// 向后遍历table
    for (int i = nextIndex(staleSlot, len);
         (e = tab[i]) != null;
         i = nextIndex(i, len)) {
        ThreadLocal<?> k = e.get();

      	// 找到了key，将其与无效的slot交换
        if (k == key) {
            e.value = value;

            tab[i] = tab[staleSlot];
            tab[staleSlot] = e;

            /*
             * 如果在整个扫描过程中（包括函数一开始的向前扫描与i之前的向后扫描）
             * 找到了之前的无效slot则以那个位置作为清理的起点，
             * 否则则以当前的i作为清理起点
             */
            if (slotToExpunge == staleSlot)
                slotToExpunge = i;
            cleanSomeSlots(expungeStaleEntry(slotToExpunge), len);
            return;
        }

				// 如果当前的slot已经无效，并且向前扫描过程中没有无效slot，则更新slotToExpunge为当前位置
        if (k == null && slotToExpunge == staleSlot)
            slotToExpunge = i;
    }

   // 如果key在table中不存在，则在原地放一个即可
    tab[staleSlot].value = null;
    tab[staleSlot] = new Entry(key, value);

    // 在探测过程中如果发现任何无效slot，则做一次清理（连续段清理+启发式清理）
    if (slotToExpunge != staleSlot)
        cleanSomeSlots(expungeStaleEntry(slotToExpunge), len);
}

private boolean cleanSomeSlots(int i, int n) {
    boolean removed = false;
    Entry[] tab = table;
    int len = tab.length;
    do {
        i = nextIndex(i, len);
        Entry e = tab[i];
        if (e != null && e.get() == null) {
            n = len;
            removed = true;
            i = expungeStaleEntry(i);
        }
    } while ( (n >>>= 1) != 0);
    return removed;
}

private void rehash() {
  	// 做一次全量清理
    expungeStaleEntries();

    /*
     * 因为做了一次清理，所以size很可能会变小。
     * ThreadLocalMap这里的实现是调低阈值来判断是否需要扩容，
     * threshold默认为len*2/3，所以这里的threshold - threshold / 4相当于len/2
     */    
    if (size >= threshold - threshold / 4)
        resize();
}

/**
 * 扩容，因为需要保证table的容量len为2的幂，所以扩容即扩大2倍
 */
private void resize() {
    Entry[] oldTab = table;
    int oldLen = oldTab.length;
    int newLen = oldLen * 2;
  	// 创建新的table
    Entry[] newTab = new Entry[newLen];
    int count = 0;
		
    for (int j = 0; j < oldLen; ++j) {
        Entry e = oldTab[j];
        if (e != null) {
            ThreadLocal<?> k = e.get();
            if (k == null) {
              	// 也会做一次清理，帮助GC
                e.value = null; 
            } else {
              	// 线性探测来存放Entry
                int h = k.threadLocalHashCode & (newLen - 1);
                while (newTab[h] != null)
                    h = nextIndex(h, newLen);
                newTab[h] = e;
                count++;
            }
        }
    }

    setThreshold(newLen);
    size = count;
    table = newTab;
}

private void expungeStaleEntries() {
    Entry[] tab = table;
    int len = tab.length;
    for (int j = 0; j < len; j++) {
        Entry e = tab[j];
        if (e != null && e.get() == null)
            expungeStaleEntry(j);
    }
}

```



#### 总结：

- get过程
  - 根据当前的Thread获取Map
  - 如果Map不为null，则获取值，如果有值则返回
  - 如果map为null，或者没有要获取的值
  - 则进行初始化map，并存入当前key是this，value为null，将null返回
- set过程
  - 根据当前的Thread获取Map
  - 如果map为null则创建一个map
  - 如果不为null则进行map的插入流程
  - 通过hash值和数组长度进行&运算获取当前要插入的位置
  - 进行线性探测，key已存在则进行替换，key已失效则进行清理和重新赋值
  - 否则找到为null的位置进行新的Entry的创建
  - 进行清理，并计算扩容阈值进行比较
  - 重新设置大小，重hash




## 四、Handler

#### 4.1构造函数

```java
    public Handler(Callback callback, boolean async) {
    		//匿名类、内部类或本地类都必须申明为static，否则会警告可能出现内存泄露
        if (FIND_POTENTIAL_LEAKS) {
            final Class<? extends Handler> klass = getClass();
            if ((klass.isAnonymousClass() || klass.isMemberClass() || klass.isLocalClass()) &&
                    (klass.getModifiers() & Modifier.STATIC) == 0) {
                    klass.getCanonicalName());
            }
        }

        mLooper = Looper.myLooper();// 从当前的线程中取lopper
        if (mLooper == null) {
            throw new RuntimeException(
                "Can't create handler inside thread that has not called Looper.prepare()");
        }
        mQueue = mLooper.mQueue;//消息队列，来自Looper对象
        mCallback = callback;//回调方法
        mAsynchronous = async;//设置消息是否为异步处理方式
    }
    
    
	public Handler(Looper looper, Callback callback, boolean async) {
        mLooper = looper;
        mQueue = looper.mQueue;
        mCallback = callback;
    		// 这个字段没有搞明白
        mAsynchronous = async;
    }
    
```

##### 4.2 Looper中的消息分发

```java
public void dispatchMessage(Message msg) {
    if (msg.callback != null) { 
      	// 先分发post的runable
        handleCallback(msg);
    } else {
        if (mCallback != null) {
          	// 分发handle的callback
            if (mCallback.handleMessage(msg)) {
                return;
            }
        }
      	// 分发Handler自身的回调方法
        handleMessage(msg);
    }
}
```

##### 4.3 handler通过obtainMessage创建Message

```java
    public final Message obtainMessage()
    {		
        // 创建消息 message的后面会介绍
        return Message.obtain(this);
    }
    public final Message obtainMessage(int what)
    public final Message obtainMessage(int what, Object obj)
    public final Message obtainMessage(int what, int arg1, int arg2)
    public final Message obtainMessage(int what, int arg1, int arg2, Object obj)

```
##### 4.4 消息发送
```java
    public final boolean post(Runnable r)
    public final boolean postAtTime(Runnable r, long uptimeMillis)
    public final boolean postAtTime(Runnable r, Object token, long uptimeMillis)
    public final boolean postDelayed(Runnable r, long delayMillis)
 		public final boolean sendMessage(Message msg)
    public final boolean sendEmptyMessage(int what)
    public final boolean sendEmptyMessageDelayed(int what, long delayMillis) {
    public final boolean sendEmptyMessageAtTime(int what, long uptimeMillis) {
        Message msg = Message.obtain();
        msg.what = what;
        return sendMessageAtTime(msg, uptimeMillis);
    }

    public final boolean sendMessageDelayed(Message msg, long delayMillis)
    {
        if (delayMillis < 0) {
            delayMillis = 0;
        }
      	// 当前时间+延迟时间，将消息添加到队列
        return sendMessageAtTime(msg, SystemClock.uptimeMillis() + delayMillis);
    }

```
**实际上大家都是在调用sendMessageAtTime**

```java
    public boolean sendMessageAtTime(Message msg, long uptimeMillis) {
      	// uptimeMillis是未来的需要执行的时间SystemClock.uptimeMillis() + delayMillis
      	
      	// 当前的message队列
        MessageQueue queue = mQueue;
        if (queue == null) {
            RuntimeException e = new RuntimeException(
                    this + " sendMessageAtTime() called with no mQueue");
            Log.w("Looper", e.getMessage(), e);
            return false;
        }
      	// 将新增的message添加到队列中
        return enqueueMessage(queue, msg, uptimeMillis);
    }
    private boolean enqueueMessage(MessageQueue queue, Message msg, long uptimeMillis) {
        msg.target = this;
        if (mAsynchronous) {
            msg.setAsynchronous(true);
        }
        // 添加队列方法
        return queue.enqueueMessage(msg, uptimeMillis);
    }
```


## 五、MessageQueue

Message中存储了Message链表，Lopper通过next取Message，handler通过enqueueMessage插入Message

#### 5.1消息插入

```java
boolean enqueueMessage(Message msg, long when) {
  	// 每一个Message必须有一个targert，也就是Handler
    if (msg.target == null) {
        throw new IllegalArgumentException("Message must have a target.");
    }
    if (msg.isInUse()) {
        throw new IllegalStateException(msg + " This message is already in use.");
    }

    synchronized (this) {
      	// 正在退出时，回收消息到消息池
        if (mQuitting) {
            IllegalStateException e = new IllegalStateException(
                    msg.target + " sending message to a Handler on a dead thread");
            Log.w(TAG, e.getMessage(), e);
            msg.recycle();
            return false;
        }

        msg.markInUse();
        msg.when = when;
        Message p = mMessages;
        boolean needWake;
        if (p == null || when == 0 || when < p.when) {
            // p为null代表当前的消息队列中没有消息，when代表当前进入的是最早的消息，when < p.when当前消息的触发时间要比头节点消息早
            msg.next = p;
            mMessages = msg;
          	// 当阻塞时需要唤醒
            needWake = mBlocked;
        } else {
          	//将消息按时间顺序插入到MessageQueue。一般地，不需要唤醒事件队列，除非
            //消息队头存在barrier，并且同时Message是队列中最早的异步消息。
            needWake = mBlocked && p.target == null && msg.isAsynchronous();
            Message prev;
            for (;;) {
                prev = p;
                p = p.next;
                if (p == null || when < p.when) {
                    break;
                }
                if (needWake && p.isAsynchronous()) {
                    needWake = false;
                }
            }
            msg.next = p; 
            prev.next = msg;
        }

        // We can assume mPtr != 0 because mQuitting is false.
        if (needWake) {
            nativeWake(mPtr);
        }
    }
    return true;
}
```

#### 5.2消息的获取

```java
Message next() {
    final long ptr = mPtr;
    if (ptr == 0) {
      	// 当前消息循环已经退出，直接返回
        return null;
    }

    int pendingIdleHandlerCount = -1; // 循环迭代的首次为-1
    int nextPollTimeoutMillis = 0;
    for (;;) {
        if (nextPollTimeoutMillis != 0) {
            Binder.flushPendingCommands();
        }
				//阻塞操作，当等待nextPollTimeoutMillis时长，或者消息队列被唤醒，都会返回
        nativePollOnce(ptr, nextPollTimeoutMillis);
				
        synchronized (this) {
            final long now = SystemClock.uptimeMillis();
            Message prevMsg = null;
            Message msg = mMessages;
            if (msg != null && msg.target == null) {
                // 当消息handelr为null时则查询异步消息
                do {
                    prevMsg = msg;
                    msg = msg.next;
                } while (msg != null && !msg.isAsynchronous());
            }
            if (msg != null) {
                if (now < msg.when) {
                  	// 当前消息没有达到触发事件，设置下一次轮寻的超时时常
                    nextPollTimeoutMillis = (int) Math.min(msg.when - now, Integer.MAX_VALUE);
                } else {
                    // 获取一条消息并返回
                    mBlocked = false;
                    if (prevMsg != null) {
                        prevMsg.next = msg.next;
                    } else {
                        mMessages = msg.next;
                    }
                    msg.next = null;
                    if (DEBUG) Log.v(TAG, "Returning message: " + msg);
                  	// 设置消息使用状态
                    msg.markInUse();
                    return msg;
                }
            } else {
                // 没有消息
                nextPollTimeoutMillis = -1;
            }

            // 消息正在退出返回null
            if (mQuitting) {
                dispose();
                return null;
            }

            // 当前消息队列为null，或者是消息队列的第一个消息时
            if (pendingIdleHandlerCount < 0
                    && (mMessages == null || now < mMessages.when)) {
                pendingIdleHandlerCount = mIdleHandlers.size();
            }
            if (pendingIdleHandlerCount <= 0) {
                //没有idle handlers 需要运行，则循环并等待。
                mBlocked = true;
                continue;
            }

            if (mPendingIdleHandlers == null) {
                mPendingIdleHandlers = new IdleHandler[Math.max(pendingIdleHandlerCount, 4)];
            }
            mPendingIdleHandlers = mIdleHandlers.toArray(mPendingIdleHandlers);
        }

        //只有第一次循环时，会运行idle handlers，执行完成后，重置pendingIdleHandlerCount为0.
        for (int i = 0; i < pendingIdleHandlerCount; i++) {
            final IdleHandler idler = mPendingIdleHandlers[i];
            mPendingIdleHandlers[i] = null; //去掉handler的引用

            boolean keep = false;
            try {
                keep = idler.queueIdle(); //idle时执行的方法
            } catch (Throwable t) {
                Log.wtf(TAG, "IdleHandler threw exception", t);
            }

            if (!keep) {
                synchronized (this) {
                    mIdleHandlers.remove(idler);
                }
            }
        }

        //重置idle handler个数为0，以保证不会再次重复运行
        pendingIdleHandlerCount = 0;

        //当调用一个空闲handler时，一个新message能够被分发，因此无需等待可以直接查询pending message.
        nextPollTimeoutMillis = 0;
    }
}
```

## Message

在代码中，可能经常看到recycle()方法，咋一看，可能是在做虚拟机的gc()相关的工作，其实不然，这是用于把消息加入到消息池的作用。这样的好处是，当消息池不为空时，可以直接从消息池中获取Message对象，而不是直接创建，提高效率。

静态变量`sPool`的数据类型为Message，通过next成员变量，维护一个消息池；静态变量`MAX_POOL_SIZE`代表消息池的可用大小；消息池的默认大小为50。

消息池常用的操作方法是obtain()和recycle()。

```java
public static Message obtain() {
    synchronized (sPoolSync) {
        if (sPool != null) {
            Message m = sPool;
            sPool = m.next;
            m.next = null;
            m.flags = 0; // clear in-use flag
            sPoolSize--;
            return m;
        }
    }
    return new Message();
}
```



```java
public void recycle() {
    if (isInUse()) {
        if (gCheckRecycle) {
            throw new IllegalStateException("This message cannot be recycled because it "
                    + "is still in use.");
        }
        return;
    }
    recycleUnchecked();
}

/**
 * Recycles a Message that may be in-use.
 * Used internally by the MessageQueue and Looper when disposing of queued Messages.
 */
private static final int MAX_POOL_SIZE = 50;
void recycleUnchecked() {
    // Mark the message as in use while it remains in the recycled object pool.
    // Clear out all other details.
    flags = FLAG_IN_USE;
    what = 0;
    arg1 = 0;
    arg2 = 0;
    obj = null;
    replyTo = null;
    sendingUid = -1;
    when = 0;
    target = null;
    callback = null;
    data = null;

    synchronized (sPoolSync) {
      	// 消息池的最大数量是50个
        if (sPoolSize < MAX_POOL_SIZE) {
            next = sPool;
            sPool = this;
            sPoolSize++;
        }
    }
}
```

#### 参考

https://www.cnblogs.com/micrari/p/6790229.html

http://gityuan.com/2015/12/26/handler-message-framework/