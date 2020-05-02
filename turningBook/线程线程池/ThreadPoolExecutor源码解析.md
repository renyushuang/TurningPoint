# ThreadPoolExecutor源码解析

### 一、先从构造方法说起

```java
public ThreadPoolExecutor(int corePoolSize,
                          int maximumPoolSize,
                          long keepAliveTime,
                          TimeUnit unit,
                          BlockingQueue<Runnable> workQueue) {
    this(corePoolSize, maximumPoolSize, keepAliveTime, unit, workQueue,
         Executors.defaultThreadFactory(), defaultHandler);
}

public ThreadPoolExecutor(int corePoolSize,
                          int maximumPoolSize,
                          long keepAliveTime,
                          TimeUnit unit,
                          BlockingQueue<Runnable> workQueue,
                          ThreadFactory threadFactory,
                          RejectedExecutionHandler handler) {
  // 核心线程数不能小于0
  // 最大线程数不能小于0
  // 最大线程数不能小于核心线程数
  // 线程池维护线程所允许的空闲时间。当线程池中的线程数量大于corePoolSize的时候，如果这时没有新的任务提交，核心线程外的线程不会立即销毁，而是会等待，直到等待的时间超过了keepAliveTime；
  if (corePoolSize < 0 ||
      maximumPoolSize <= 0 ||
      maximumPoolSize < corePoolSize ||
      keepAliveTime < 0)
    throw new IllegalArgumentException();
  if (workQueue == null || threadFactory == null || handler == null)
    throw new NullPointerException();
  this.corePoolSize = corePoolSize;
  this.maximumPoolSize = maximumPoolSize;
  // 等待队列
  this.workQueue = workQueue;
  this.keepAliveTime = unit.toNanos(keepAliveTime);
  // 用来创建新线程
  this.threadFactory = threadFactory;
  // 饱和策略，没有空闲线程然后还要提交，则要采取一定的措施
  this.handler = handler;
}

```

#### 二、execute(Runnable command)

### 2.1 execute(Runnable command) 

```java
private final AtomicInteger ctl = new AtomicInteger(ctlOf(RUNNING, 0));
public void execute(Runnable command) {
    if (command == null)
        throw new NullPointerException();
		
  	// ctl是对线程池的运行状态和线程池中有效线程的数量进行控制的一个字段， 它包含两部分的信息: 线程池的运行状态 (runState) 和线程池内有效线程的数量 (workerCount)，这里可以看到，使用了Integer类型来保存，高3位保存runState，低29位保存workerCount。COUNT_BITS 就是29，CAPACITY就是1左移29位减1（29个1），这个常量表示workerCount的上限值，大约是5亿。
    int c = ctl.get();
  	// 计算核心线程数 2.1.1
    if (workerCountOf(c) < corePoolSize) {
      	// 如果没有达到核心线程数那么进行 // 2.1
        if (addWorker(command, true))
            return;
      	// 如果添加失败重新获取ctl
        c = ctl.get();
    }
  	// 如果当前线程池是运行状并且任务添加到队列成功 isRunning是啥// 2.1.2
    if (isRunning(c) && workQueue.offer(command)) {
        int recheck = ctl.get();
				// 双重判断，如果不再运行了，执行拒绝策略 // remove 2.1.3
        if (! isRunning(recheck) && remove(command))
          	// 2.1.4 执行拒绝策略
            reject(command);
      	// 判断核心线程数是否已经到达最大了，到了的话执行非核心线程数添加线程逻辑
        else if (workerCountOf(recheck) == 0)
            addWorker(null, false);
    }
  	// 线程不是RUNNING状态
  	// 是RUNNING状态，但是核心线程数满了，阻塞队列也满了
    else if (!addWorker(command, false))
        reject(command);
}
```

####  2.1.1 workerCountOf(int c)

```java
private static final int COUNT_BITS = Integer.SIZE - 3;
private static final int CAPACITY   = (1 << COUNT_BITS) - 1;

// Integer最大数值是32位，向左移动29位，那么就是前三位记录记录核心线程数
private static int workerCountOf(int c)  { return c & CAPACITY; }
```

####  2.1.2isRunning(int c)

```java
private static final int RUNNING    = -1 << COUNT_BITS;
private static final int SHUTDOWN   =  0 << COUNT_BITS;
private static final int STOP       =  1 << COUNT_BITS;
private static final int TIDYING    =  2 << COUNT_BITS;
private static final int TERMINATED =  3 << COUNT_BITS;
private static boolean isRunning(int c) {
  	// c<SHUTDOWN 代表是running状态
    return c < SHUTDOWN;
}
```

#### 2.1.3 remove(Runnable task)

```java
public boolean remove(Runnable task) {
  	// 从工作线程队列中移除
    boolean removed = workQueue.remove(task);
  	// 2.3
    tryTerminate(); // In case SHUTDOWN and now empty
    return removed;
}
```

#### 2.1.4 reject(Runnable command)

```java
final void reject(Runnable command) {
  	// handler默认是AbortHandler，一会对这些handler进行分析
    handler.rejectedExecution(command, this);
}
```


#### 2.2 addWorker(command, true)

```java
 */
private boolean addWorker(Runnable firstTask, boolean core) {
   	// core为true则是创建核心线程
    retry:
    for (;;) {
        int c = ctl.get();
      	// 2.2.1
        int rs = runStateOf(c);

        // Check if queue empty only if necessary.
      	// rs>SHUTDOWN 此时不再接收新任务
      	// 
      	// ! (rs == SHUTDOWN &&firstTask == null &&! workQueue.isEmpty()))
      	// 这个情况下不需要创建新的线程 直接返回
        if (rs >= SHUTDOWN &&
            ! (rs == SHUTDOWN &&firstTask == null &&! workQueue.isEmpty()))
            return false;
				
        for (;;) {
          	// 获取核心线程数
            int wc = workerCountOf(c);
          	// wc >= CAPACITY 大于最大的支持的线程数
          	// 
          	// wc >= (core ? corePoolSize : maximumPoolSize)
          	// 如果是核心线程，判断核心线程数，否则判断最大线程数
            if (wc >= CAPACITY ||
                wc >= (core ? corePoolSize : maximumPoolSize))
                return false;
          	// 尝试获取锁并将线程数增加1
            if (compareAndIncrementWorkerCount(c))
                break retry;
          	// 线程数增加1的操作失败了，再尝试获取一次ctl的值
            c = ctl.get();  // Re-read ctl
            if (runStateOf(c) != rs)
                continue retry;
            // else CAS failed due to workerCount change; retry inner loop
        }
    }

    boolean workerStarted = false;
    boolean workerAdded = false;
    Worker w = null;
    try {
      	// 创建了一个Worker // 
      	// 2.4 Worker 也是一个Runable
        w = new Worker(firstTask);
      	// 获取新创建的那个Thread
        final Thread t = w.thread;
        if (t != null) {
            final ReentrantLock mainLock = this.mainLock;
            mainLock.lock();
            try {
                // Recheck while holding lock.
                // Back out on ThreadFactory failure or if
                // shut down before lock acquired.
                int rs = runStateOf(ctl.get());
								// 之前都没有加锁，执行添加的过程增加锁
                if (rs < SHUTDOWN ||
                    (rs == SHUTDOWN && firstTask == null)) {
                    if (t.isAlive()) // precheck that t is startable
                        throw new IllegalThreadStateException();
                    workers.add(w);
                    int s = workers.size();
                    if (s > largestPoolSize)
                        largestPoolSize = s;
                    workerAdded = true;
                }
            } finally {
                mainLock.unlock();
            }
            if (workerAdded) {
                t.start();
                workerStarted = true;
            }
        }
    } finally {
        if (! workerStarted)
            addWorkerFailed(w);
    }
    return workerStarted;
}
```

#### 2.2.1 runStateOf

```java
// 取了一个反 那就是 拿后29位的值
private static int runStateOf(int c)     { return c & ~CAPACITY; }
```

### 2.3 tryTerminate()

```java
final void tryTerminate() {
    for (;;) {
        int c = ctl.get();
        if (isRunning(c) ||
            runStateAtLeast(c, TIDYING) ||
            (runStateOf(c) == SHUTDOWN && ! workQueue.isEmpty()))
            return;
        if (workerCountOf(c) != 0) { // Eligible to terminate
            interruptIdleWorkers(ONLY_ONE);
            return;
        }

        final ReentrantLock mainLock = this.mainLock;
        mainLock.lock();
        try {
            if (ctl.compareAndSet(c, ctlOf(TIDYING, 0))) {
                try {
                    terminated();
                } finally {
                    ctl.set(ctlOf(TERMINATED, 0));
                    termination.signalAll();
                }
                return;
            }
        } finally {
            mainLock.unlock();
        }
        // else retry on failed CAS
    }
}
```

#### 2.4 Worker

```java
// 这个类比较短直接全部粘贴
private final class Worker
    extends AbstractQueuedSynchronizer
    implements Runnable
{
    /**
     * This class will never be serialized, but we provide a
     * serialVersionUID to suppress a javac warning.
     */
    private static final long serialVersionUID = 6138294804551838833L;

    /** Thread this worker is running in.  Null if factory fails. */
    final Thread thread;
    /** Initial task to run.  Possibly null. */
    Runnable firstTask;
    /** Per-thread task counter */
    volatile long completedTasks;

    /**
     * Creates with given first task and thread from ThreadFactory.
     * @param firstTask the first task (null if none)
     */
    Worker(Runnable firstTask) {
        setState(-1); // inhibit interrupts until runWorker
        this.firstTask = firstTask;
      	// 这个Thread的Runable使用的就是当前这个Work的Runable
        this.thread = getThreadFactory().newThread(this);
    }

    /** Delegates main run loop to outer runWorker. */
    public void run() {
      	// 其他的好像都没做什么 // 2.4.1
        runWorker(this);
    }

    // Lock methods
    //
    // The value 0 represents the unlocked state.
    // The value 1 represents the locked state.

    protected boolean isHeldExclusively() {
        return getState() != 0;
    }

    protected boolean tryAcquire(int unused) {
        if (compareAndSetState(0, 1)) {
            setExclusiveOwnerThread(Thread.currentThread());
            return true;
        }
        return false;
    }

    protected boolean tryRelease(int unused) {
        setExclusiveOwnerThread(null);
        setState(0);
        return true;
    }

    public void lock()        { acquire(1); }
    public boolean tryLock()  { return tryAcquire(1); }
    public void unlock()      { release(1); }
    public boolean isLocked() { return isHeldExclusively(); }

    void interruptIfStarted() {
        Thread t;
        if (getState() >= 0 && (t = thread) != null && !t.isInterrupted()) {
            try {
                t.interrupt();
            } catch (SecurityException ignore) {
            }
        }
    }
}
```

#### 2.4.1 runWorker(Worker w)

```java
// 传入的RunAble的执行
final void runWorker(Worker w) {
    Thread wt = Thread.currentThread();
  	// 获取任务，获取完就可以置空了
    Runnable task = w.firstTask;
    w.firstTask = null;
    w.unlock(); // allow interrupts
    boolean completedAbruptly = true;
    try {
      	// task不位null，getTask 2.4.2
        while (task != null || (task = getTask()) != null) {
            w.lock();
            // If pool is stopping, ensure thread is interrupted;
            // if not, ensure thread is not interrupted.  This
            // requires a recheck in second case to deal with
            // shutdownNow race while clearing interrupt
            if ((runStateAtLeast(ctl.get(), STOP) ||
                 (Thread.interrupted() &&
                  runStateAtLeast(ctl.get(), STOP))) &&
                !wt.isInterrupted())
                wt.interrupt();
            try {
              	// 执行线程之前做点什么
                beforeExecute(wt, task);
                Throwable thrown = null;
                try {
                    task.run();
                } catch (RuntimeException x) {
                    thrown = x; throw x;
                } catch (Error x) {
                    thrown = x; throw x;
                } catch (Throwable x) {
                    thrown = x; throw new Error(x);
                } finally {
                  	// 执行线程之后做点什么
                    afterExecute(task, thrown);
                }
            } finally {
                task = null;
                w.completedTasks++;
                w.unlock();
            }
        }
        completedAbruptly = false;
    } finally {
      	// 执行完成，获取下一个队列中的内容，继续执行
        processWorkerExit(w, completedAbruptly);
    }
}
```

#### 2.4.2 getTask()

```java
private Runnable getTask() {
    boolean timedOut = false; // Did the last poll() time out?

    for (;;) {
        int c = ctl.get();
        int rs = runStateOf(c);

        // Check if queue empty only if necessary.
        if (rs >= SHUTDOWN && (rs >= STOP || workQueue.isEmpty())) {
            decrementWorkerCount();
            return null;
        }

        int wc = workerCountOf(c);

        // Are workers subject to culling?
        boolean timed = allowCoreThreadTimeOut || wc > corePoolSize;

        if ((wc > maximumPoolSize || (timed && timedOut))
            && (wc > 1 || workQueue.isEmpty())) {
            if (compareAndDecrementWorkerCount(c))
                return null;
            continue;
        }

        try {
          	// 获取一个可用的队列中的Runable
            Runnable r = timed ?
                workQueue.poll(keepAliveTime, TimeUnit.NANOSECONDS) :
                workQueue.take();
            if (r != null)
                return r;
            timedOut = true;
        } catch (InterruptedException retry) {
            timedOut = false;
        }
    }
}
```



### 三、流程差不多了，可以看看常用的BlockingQueue和RejectedExecutionHandler了

#### 3.1 RejectedExecutionHandler

##### 3.1.1 AbortPolicy 默认的

```java
public static class AbortPolicy implements RejectedExecutionHandler {
    public AbortPolicy() { }
    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
      // 抛出异常
      throw new RejectedExecutionException("Task " + r.toString() +
                                             " rejected from " +
                                             e.toString());
    }
}
```

##### 3.1.2 DiscardPolicy

```java
public static class DiscardPolicy implements RejectedExecutionHandler {

    public DiscardPolicy() { }

    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
      	// 什么否不做
    }
}
```

##### 3.1.3 DiscardOldestPolicy

```java
public static class DiscardOldestPolicy implements RejectedExecutionHandler {
    /**
     * Creates a {@code DiscardOldestPolicy} for the given executor.
     */
    public DiscardOldestPolicy() { }

    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
        if (!e.isShutdown()) {
          	// 丢弃靠前的任务
            e.getQueue().poll();
            e.execute(r);
        }
    }
}
```

##### 3.1.4 CallerRunsPolicy

```java
public static class CallerRunsPolicy implements RejectedExecutionHandler {
    /**
     * Creates a {@code CallerRunsPolicy}.
     */
    public CallerRunsPolicy() { }

    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
        if (!e.isShutdown()) {
          	// 在调用者线程执行
            r.run();
        }
    }
}
```

#### 3.2 BlockingQueue

##### 3.2.1 SynchronousQueue

```
没有容量，是无缓冲等待队列，是一个不存储元素的阻塞队列，会直接将任务交给消费者，必须等队列中的添加元素被消费后才能继续添加新的元素。
```

##### 3.2.2 LinkedBlockingQueue

```
是一个无界缓存等待队列。当前执行的线程数量达到corePoolSize的数量时，剩余的元素会在阻塞队列里等待。（所以在使用此阻塞队列时maximumPoolSizes就相当于无效了），每个线程完全独立于其他线程。生产者和消费者使用独立的锁来控制数据的同步，即在高并发的情况下可以并行操作队列中的数据。
```

```java
public boolean offer(E e) {
    if (e == null) throw new NullPointerException();
    final AtomicInteger count = this.count;
    if (count.get() == capacity)
        return false;
    int c = -1;
    Node<E> node = new Node<E>(e);
    final ReentrantLock putLock = this.putLock;
    putLock.lock();
    try {
        if (count.get() < capacity) {
            enqueue(node);
            c = count.getAndIncrement();
            if (c + 1 < capacity)
                notFull.signal();
        }
    } finally {
        putLock.unlock();
    }
    if (c == 0)
        signalNotEmpty();
    return c >= 0;
}
```

##### 3.2.3 ArrayBlockingQueue

```
是一个有界缓存等待队列，可以指定缓存队列的大小，当正在执行的线程数等于corePoolSize时，多余的元素缓存在ArrayBlockingQueue队列中等待有空闲的线程时继续执行，当ArrayBlockingQueue已满时，加入ArrayBlockingQueue失败
```

```java
public boolean offer(E e) {
    Objects.requireNonNull(e);
    final ReentrantLock lock = this.lock;
    lock.lock();
    try {
        if (count == items.length)
            return false;
        else {
            enqueue(e);
            return true;
        }
    } finally {
        lock.unlock();
    }
}
```

##### 3.2.4 PriorityBlockingQueue

```java
public boolean offer(E e) {
    if (e == null)
        throw new NullPointerException();
    final ReentrantLock lock = this.lock;
    lock.lock();
    int n, cap;
    Object[] array;
    while ((n = size) >= (cap = (array = queue).length))
        tryGrow(array, cap);
    try {
        Comparator<? super E> cmp = comparator;
        if (cmp == null)
            siftUpComparable(n, e, array);
        else
            siftUpUsingComparator(n, e, array, cmp);
        size = n + 1;
        notEmpty.signal();
    } finally {
        lock.unlock();
    }
    return true;
}
```

### 四、还有一个

```java
private static class DefaultThreadFactory implements ThreadFactory {
    private static final AtomicInteger poolNumber = new AtomicInteger(1);
    private final ThreadGroup group;
    private final AtomicInteger threadNumber = new AtomicInteger(1);
    private final String namePrefix;

    DefaultThreadFactory() {
        SecurityManager s = System.getSecurityManager();
        group = (s != null) ? s.getThreadGroup() :
                              Thread.currentThread().getThreadGroup();
        namePrefix = "pool-" +
                      poolNumber.getAndIncrement() +
                     "-thread-";
    }

    public Thread newThread(Runnable r) {
        Thread t = new Thread(group, r,
                              namePrefix + threadNumber.getAndIncrement(),
                              0);
        if (t.isDaemon())
            t.setDaemon(false);
        if (t.getPriority() != Thread.NORM_PRIORITY)
            t.setPriority(Thread.NORM_PRIORITY);
        return t;
    }
}
```



#### 参考

https://juejin.im/entry/58fada5d570c350058d3aaad

