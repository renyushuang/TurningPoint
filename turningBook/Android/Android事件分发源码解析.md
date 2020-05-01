# Android事件分发源码解析

## 一、基础知识

```java
// 对事件进行分发
public boolean dispatchTouchEvent(MotionEvent ev);
// 判断是否要拦截某一个事件
public boolean onInterceptTouchEvent(MotionEvent ev)
// 用来消耗事件  
public boolean onTouchEvent(MotionEvent event)
```

先简单的知道大致三个方法都是做什么的，然后在事件分发的源码部分再详细的去看都是如何工作的。

#### 1.1Android事件分发中的核心类

| 方法                  | Avtivity | View | ViewGroup |
| --------------------- | -------- | ---- | --------- |
| dispatchTouchEvent    | √        | √    | √         |
| onInterceptTouchEvent | ×        | ×    | √         |
| onTouchEvent          | √        | √    | √         |

- 这里就有了一个问题
  - 为什么Activity没有onInterceptTouchEvent方法
  - 为什么View没有onInterceptTouchEvent方法

那么暂时我也不知道，向后看逐步的分析一下

#### 1.2事件分发的顺序是什么

**Activity->Window(PhoneWindow)->ViewGroup->View**

当View不进行处理事件时，事件又会被传递回来

**View->ViewGroup->Window(PhoneWindow)->Activity**

#### 1.3完整的事件

DOWN(1)->MOVE(N)->UP(1)

#### 1.4总结

基础的东西大致就时这些，可以在很多书上看到，然后就去和其他人讲，遇到一些问题的时候，死的很惨，为什么会出现这种情况呢？就算试验过很多的情景，那么可能会有覆盖不到的，这时候源码的阅读，源码的鞭策就很重要了。个人的血的教训。接下来开始进行源码的分析



## 二、事件分发源码分析，从Activity开始

#### 2.1Activity.dispatchTouchEvent

```java
    public boolean dispatchTouchEvent(MotionEvent ev) {
      // 判断是不是down事件，做了一个事情  
      if (ev.getAction() == MotionEvent.ACTION_DOWN) {
        // 这是一个空的方法，注释标明说，如果你希望与用户做一些交互 
        onUserInteraction();
        }
        // 获取Window，也就是PhoneWindow进行事件的分发
        if (getWindow().superDispatchTouchEvent(ev)) {
            return true;
        }
        // 如果PhoneWindow的事件分发没有处理，那么交给Activity进行处理
        return onTouchEvent(ev);
    }

    public void onUserInteraction() {
    }
		


```

#### 2.1Activity.onTouchEvent

```java
public boolean onTouchEvent(MotionEvent event) {
  	// 当前窗口需要关闭时，消耗掉Event
    if (mWindow.shouldCloseOnTouch(this, event)) {、
        finish();
        return true;
    }

    return false;
}
```
#### 2.3 总结

- 这里面遇到了两个Window的方法，之后进行查看

## 三、PhoneWindow

#### 3.1 PhoneWindow.superDispatchTouchEvent(MotionEvent event)

```java
@Override
public boolean superDispatchTouchEvent(MotionEvent event) {
  	// 通过mDecor继续进行分发，DecorView
    return mDecor.superDispatchTouchEvent(event);
}
```

## 四、DecorView

```java
// DecorView是一个FrameLayout
DecorView extends FrameLayout
```

#### 4.1 DecorView.superDispatchTouchEvent(MotionEvent event)

```java
public boolean superDispatchTouchEvent(MotionEvent event) {
    return super.dispatchTouchEvent(event);
}
```

#### 4.2常规方法

```java
@Override
public boolean dispatchTouchEvent(MotionEvent ev) {
    final Window.Callback cb = mWindow.getCallback();
    return cb != null && !mWindow.isDestroyed() && mFeatureId < 0
            ? cb.dispatchTouchEvent(ev) : super.dispatchTouchEvent(ev);
}
```

```java
@Override
public boolean onTouchEvent(MotionEvent event) {
    return onInterceptTouchEvent(event);
}
```

```java
@Override
public boolean onInterceptTouchEvent(MotionEvent event) {
    return false;
}
```

####4.3 看到这有一个特别大的疑问，DecorView的dispatchTouchEvent是谁来调用的。

PhoneWindow、DecorView、ViewRootImpl、Activity关系

- ViewRootImpl中注册了

  ```java
  mInputEventReceiver = new WindowInputEventReceiver(mInputChannel,
          Looper.myLooper());
  ```

- Native层调用了InputEventReceiver(WindowInputEventReceiver的父类)dispatchInputEvent

```java
// Called from native code.
@SuppressWarnings("unused")
private void dispatchInputEvent(int seq, InputEvent event, int displayId) {
    mSeqMap.put(event.getSequenceNumber(), seq);
    onInputEvent(event, displayId);
}
```

- 回调到 WindowInputEventReceiver 的onInputEvent，中的enqueueInputEvent

```java
@Override
public void onInputEvent(InputEvent event, int displayId) {
    enqueueInputEvent(event, this, 0, true);
}
```

```java

void enqueueInputEvent(InputEvent event,
        InputEventReceiver receiver, int flags, boolean processImmediately) {
    adjustInputEventForCompatibility(event);
    QueuedInputEvent q = obtainQueuedInputEvent(event, receiver, flags);

    // Always enqueue the input event in order, regardless of its time stamp.
    // We do this because the application or the IME may inject key events
    // in response to touch events and we want to ensure that the injected keys
    // are processed in the order they were received and we cannot trust that
    // the time stamp of injected events are monotonic.
    QueuedInputEvent last = mPendingInputEventTail;
    if (last == null) {
        mPendingInputEventHead = q;
        mPendingInputEventTail = q;
    } else {
        last.mNext = q;
        mPendingInputEventTail = q;
    }
    mPendingInputEventCount += 1;
    Trace.traceCounter(Trace.TRACE_TAG_INPUT, mPendingInputEventQueueLengthCounterName,
            mPendingInputEventCount);

    if (processImmediately) {
        doProcessInputEvents();
    } else {
        scheduleProcessInputEvents();
    }
}
```

- 然后调用到doProcessInputEvents()

```java
void doProcessInputEvents() {
    // Deliver all pending input events in the queue.
    while (mPendingInputEventHead != null) {
        QueuedInputEvent q = mPendingInputEventHead;
        mPendingInputEventHead = q.mNext;
        if (mPendingInputEventHead == null) {
            mPendingInputEventTail = null;
        }
        q.mNext = null;

        mPendingInputEventCount -= 1;
        Trace.traceCounter(Trace.TRACE_TAG_INPUT, mPendingInputEventQueueLengthCounterName,
                mPendingInputEventCount);

        long eventTime = q.mEvent.getEventTimeNano();
        long oldestEventTime = eventTime;
        if (q.mEvent instanceof MotionEvent) {
            MotionEvent me = (MotionEvent)q.mEvent;
            if (me.getHistorySize() > 0) {
                oldestEventTime = me.getHistoricalEventTimeNano(0);
            }
        }
        mChoreographer.mFrameInfo.updateInputEventTime(eventTime, oldestEventTime);

        deliverInputEvent(q);
    }

    // We are done processing all input events that we can process right now
    // so we can clear the pending flag immediately.
    if (mProcessInputEventsScheduled) {
        mProcessInputEventsScheduled = false;
        mHandler.removeMessages(MSG_PROCESS_INPUT_EVENTS);
    }
}
```

- deliverInputEvent(QueuedInputEvent q);

```java
private void deliverInputEvent(QueuedInputEvent q) {
    Trace.asyncTraceBegin(Trace.TRACE_TAG_VIEW, "deliverInputEvent",
            q.mEvent.getSequenceNumber());
    if (mInputEventConsistencyVerifier != null) {
        mInputEventConsistencyVerifier.onInputEvent(q.mEvent, 0);
    }

    InputStage stage;
    if (q.shouldSendToSynthesizer()) {
        stage = mSyntheticInputStage;
    } else {
        stage = q.shouldSkipIme() ? mFirstPostImeInputStage : mFirstInputStage;
    }

    if (q.mEvent instanceof KeyEvent) {
        mUnhandledKeyManager.preDispatch((KeyEvent) q.mEvent);
    }

    if (stage != null) {
        handleWindowFocusChanged();
        stage.deliver(q);
    } else {
        finishInputEvent(q);
    }
}
```

- 一系列的Stage操作后processPointerEvent(q)

```java
final class ViewPostImeInputStage extends InputStage {
    public ViewPostImeInputStage(InputStage next) {
        super(next);
    }

    @Override
    protected int onProcess(QueuedInputEvent q) {
        if (q.mEvent instanceof KeyEvent) {
            return processKeyEvent(q);
        } else {
            final int source = q.mEvent.getSource();
            if ((source & InputDevice.SOURCE_CLASS_POINTER) != 0) {
                return processPointerEvent(q);
            } else if ((source & InputDevice.SOURCE_CLASS_TRACKBALL) != 0) {
                return processTrackballEvent(q);
            } else {
                return processGenericMotionEvent(q);
            }
        }
    }
```

- processPointerEvent()

```java
private int processPointerEvent(QueuedInputEvent q) {
    final MotionEvent event = (MotionEvent)q.mEvent;

    mAttachInfo.mUnbufferedDispatchRequested = false;
    mAttachInfo.mHandlingPointerEvent = true;
    boolean handled = mView.dispatchPointerEvent(event);
    maybeUpdatePointerIcon(event);
    maybeUpdateTooltip(event);
    mAttachInfo.mHandlingPointerEvent = false;
    if (mAttachInfo.mUnbufferedDispatchRequested && !mUnbufferedInputDispatch) {
        mUnbufferedInputDispatch = true;
        if (mConsumeBatchedInputScheduled) {
            scheduleConsumeBatchedInputImmediately();
        }
    }
    return handled ? FINISH_HANDLED : FORWARD;
}
```

- mView.dispatchPointerEvent(event)实现进行分发

```java
public final boolean dispatchPointerEvent(MotionEvent event) {
    if (event.isTouchEvent()) {
        return dispatchTouchEvent(event);
    } else {
        return dispatchGenericMotionEvent(event);
    }
}
```

## 五、ViewGroup

#### 5.1ViewGroup.dispatchTouchEvent

```java
@Override
public boolean dispatchTouchEvent(MotionEvent ev) {
    if (mInputEventConsistencyVerifier != null) {
        mInputEventConsistencyVerifier.onTouchEvent(ev, 1);
    }

    if (ev.isTargetAccessibilityFocus() && isAccessibilityFocusedViewOrHost()) {
        ev.setTargetAccessibilityFocus(false);
    }

    boolean handled = false;
  	// 窗口被遮挡,则丢弃该事件
    if (onFilterTouchEventForSecurity(ev)) {
        final int action = ev.getAction();
        final int actionMasked = action & MotionEvent.ACTION_MASK;

        if (actionMasked == MotionEvent.ACTION_DOWN) {
						// 发生ACTION_DOWN事件, 则取消并清除之前所有的触摸targets
            cancelAndClearTouchTargets(ev);
          	// 重置触摸状态
            resetTouchState();
        }

        // 发生过ACTION_DOWN或者已发生过ACTION_DOWN事件之行下面的方法
      	// mFirstTouchTarget != null是已经发生或ACTION_DOWN的标志
        final boolean intercepted;
        if (actionMasked == MotionEvent.ACTION_DOWN
                || mFirstTouchTarget != null) {
          	//可通过调用requestDisallowInterceptTouchEvent，不让父View拦截事件
            final boolean disallowIntercept = (mGroupFlags & FLAG_DISALLOW_INTERCEPT) != 0;
            if (!disallowIntercept) {
              	// 调用拦截方法
                intercepted = onInterceptTouchEvent(ev);
                ev.setAction(action); // restore action in case it was changed
            } else {
                intercepted = false;
            }
        } else {
          	// 没有触摸targets并且这个Action不是Down事件
            // 这个ViewGroup进行拦截
            intercepted = true;
        }

        // If intercepted, start normal event dispatch. Also if there is already
        // a view that is handling the gesture, do normal event dispatch.
        if (intercepted || mFirstTouchTarget != null) {
            ev.setTargetAccessibilityFocus(false);
        }

        // 检查当前事件是否被取消了
        final boolean canceled = resetCancelNextUpFlag(this)
                || actionMasked == MotionEvent.ACTION_CANCEL;

        // Update list of touch targets for pointer down, if needed.
        final boolean split = (mGroupFlags & FLAG_SPLIT_MOTION_EVENTS) != 0;
        TouchTarget newTouchTarget = null;
        boolean alreadyDispatchedToNewTouchTarget = false;
      	// 没有取消并且没有被拦截
        if (!canceled && !intercepted) {

            // 把事件分发给子视图，寻找可以获取焦点的视图
            View childWithAccessibilityFocus = ev.isTargetAccessibilityFocus()
                    ? findChildWithAccessibilityFocus() : null;

            if (actionMasked == MotionEvent.ACTION_DOWN
                    || (split && actionMasked == MotionEvent.ACTION_POINTER_DOWN)
                    || actionMasked == MotionEvent.ACTION_HOVER_MOVE) {
                final int actionIndex = ev.getActionIndex(); // DOWN事件为0
                final int idBitsToAssign = split ? 1 << ev.getPointerId(actionIndex)
                        : TouchTarget.ALL_POINTER_IDS;

                // 清理idBitsToAssign之前的targets，防止他们已经不同步了
                removePointersFromTouchTargets(idBitsToAssign);

                final int childrenCount = mChildrenCount;
                if (newTouchTarget == null && childrenCount != 0) {
                    final float x = ev.getX(actionIndex);
                    final float y = ev.getY(actionIndex);
                    // 从视图的上层到下层，获得能够接收到该事件的子视图
                    final ArrayList<View> preorderedList = buildTouchDispatchChildList();
                    final boolean customOrder = preorderedList == null
                            && isChildrenDrawingOrderEnabled();
                  	/* 从最底层的父视图开始遍历， ** 找寻newTouchTarget，并赋予view与 pointerIdBits； ** 如果已经存在找寻newTouchTarget，说明正在接收触摸事件，则跳出循环。 */
                    final View[] children = mChildren;
                    for (int i = childrenCount - 1; i >= 0; i--) {
                        final int childIndex = getAndVerifyPreorderedIndex(
                                childrenCount, i, customOrder);
                        final View child = getAndVerifyPreorderedView(
                                preorderedList, children, childIndex);

                        // 如果当前视图无法获取用户焦点，则跳过本次循环
                        if (childWithAccessibilityFocus != null) {
                            if (childWithAccessibilityFocus != child) {
                                continue;
                            }
                            childWithAccessibilityFocus = null;
                            i = childrenCount - 1;
                        }
												//如果view不可见，或者触摸的坐标点不在view的范围内，则跳过本次循环
                        if (!canViewReceivePointerEvents(child)
                                || !isTransformedTouchPointInView(x, y, child, null)) {
                            ev.setTargetAccessibilityFocus(false);
                            continue;
                        }

                        newTouchTarget = getTouchTarget(child);
                        if (newTouchTarget != null) {
												// 已经开始接收触摸事件,并退出整个循环。
                            newTouchTarget.pointerIdBits |= idBitsToAssign;
                            break;
                        }
												//重置取消或抬起标志位
                        //如果触摸位置在child的区域内，则把事件分发给子View或ViewGroup
                        resetCancelNextUpFlag(child);
                        if (dispatchTransformedTouchEvent(ev, false, child, idBitsToAssign)) {
                            // 获取TouchDown的时间点
                            mLastTouchDownTime = ev.getDownTime();
                            if (preorderedList != null) {
                                // 获取TouchDown的Index
                                for (int j = 0; j < childrenCount; j++) {
                                    if (children[childIndex] == mChildren[j]) {
                                        mLastTouchDownIndex = j;
                                        break;
                                    }
                                }
                            } else {
                                mLastTouchDownIndex = childIndex;
                            }
                          	// 获取touch的x，y坐标
                            mLastTouchDownX = ev.getX();
                            mLastTouchDownY = ev.getY();
                          	//添加TouchTarget,则mFirstTouchTarget != null。
                          	// mFirstTouchTarget之前一直有一个疑问mFirstTouchTarget是什么
                          	// 什么时候赋值的mFirstTouchTarget是一个点击链上的节点
                            newTouchTarget = addTouchTarget(child, idBitsToAssign);
                          	//表示以及分发给NewTouchTarget
                            alreadyDispatchedToNewTouchTarget = true;
                            break;
                        }

                        // The accessibility focus didn't handle the event, so clear
                        // the flag and do a normal dispatch to all children.
                        ev.setTargetAccessibilityFocus(false);
                    }
                  	// 清除视图列表
                    if (preorderedList != null) preorderedList.clear();
                }

                if (newTouchTarget == null && mFirstTouchTarget != null) {
                    // 如果没有子视图接收事件
                  	//将mFirstTouchTarget的链表最后的touchTarget赋给newTouchTarget
                    newTouchTarget = mFirstTouchTarget;
                    while (newTouchTarget.next != null) {
                        newTouchTarget = newTouchTarget.next;
                    }
                    newTouchTarget.pointerIdBits |= idBitsToAssign;
                }
            }
        }

        // mFirstTouchTarget赋值是在通过addTouchTarget方法获取的；
        // 只有处理ACTION_DOWN事件，才会进入addTouchTarget方法。
        // 这也正是当View没有消费ACTION_DOWN事件，则不会接收其他MOVE,UP等事件的原因
        if (mFirstTouchTarget == null) {
            //没有触摸target,则由当前ViewGroup来处理
            handled = dispatchTransformedTouchEvent(ev, canceled, null,
                    TouchTarget.ALL_POINTER_IDS);
        } else {
						//如果View消费ACTION_DOWN事件，那么MOVE,UP等事件相继开始执行
            TouchTarget predecessor = null;
            TouchTarget target = mFirstTouchTarget;
            while (target != null) {
                final TouchTarget next = target.next;
                if (alreadyDispatchedToNewTouchTarget && target == newTouchTarget) {
                    handled = true;
                } else {
                    final boolean cancelChild = resetCancelNextUpFlag(target.child)
                            || intercepted;
                    if (dispatchTransformedTouchEvent(ev, cancelChild,
                            target.child, target.pointerIdBits)) {
                        handled = true;
                    }
                    if (cancelChild) {
                        if (predecessor == null) {
                            mFirstTouchTarget = next;
                        } else {
                            predecessor.next = next;
                        }
                        target.recycle();
                        target = next;
                        continue;
                    }
                }
                predecessor = target;
                target = next;
            }
        }

        // Update list of touch targets for pointer up or cancel, if needed.
        if (canceled
                || actionMasked == MotionEvent.ACTION_UP
                || actionMasked == MotionEvent.ACTION_HOVER_MOVE) {
            resetTouchState();
        } else if (split && actionMasked == MotionEvent.ACTION_POINTER_UP) {
            final int actionIndex = ev.getActionIndex();
            final int idBitsToRemove = 1 << ev.getPointerId(actionIndex);
            removePointersFromTouchTargets(idBitsToRemove);
        }
    }

    if (!handled && mInputEventConsistencyVerifier != null) {
        mInputEventConsistencyVerifier.onUnhandledEvent(ev, 1);
    }
    return handled;
}
```

#### 5.2 onFilterTouchEventForSecurity

```java
public boolean onFilterTouchEventForSecurity(MotionEvent event) {
    if ((mViewFlags & FILTER_TOUCHES_WHEN_OBSCURED) != 0
            && (event.getFlags() & MotionEvent.FLAG_WINDOW_IS_OBSCURED) != 0) {
        // 窗口被遮挡,则丢弃该事件
        return false;
    }
    return true;
}
```



























#### 参考

http://gityuan.com/2015/09/19/android-touch/