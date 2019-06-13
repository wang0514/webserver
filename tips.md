## 2019-06-09 一些工作
1. EventLoop、Epoll还有Channel三个类是整个webwerver的核心部分，Channel类中根据前面分配过来的事件，分别对应处理的的函数，但是这个处理函数只是一个回调函数，并没有进行绑定，也就是说里面的读、写和连接等操作是由外部给定的，它只是留好了接口等调用者往里面填，你想干什么就干什么，只要绑定上去就好，真正实现了调用者和被调用者分离。调用者可以完全不了解底层的实现，但是只要注册一下回调函数米就能完成指定的操作
2. Channel类中的回调函数先申明，然后通过调用void setReadHandler(CallBack&& readHandler)，void setWriteHandler(CallBack&& writeHandler)，void setErrorHandler(CallBack&& errorHandler)，void setConnHandler(CallBack&& connHandler)四个函数进行操作，调用方通过bind函数将自己调用的处理函数放上去
## 2019-06-11
1. Epollevent、Epoll、Channel三个类基本上搞清楚了，大的思路也没问题，回调注册这些
2. 现在问题集中在epollevent中的wakeup相关的一系列操作，包括runInloop，queueInloop这些函数
3. 本来打算从主函数入手，看看这几个是怎么个操作运行的方式，但是遇到一个accept（）后，就会新建一个eventLoop对象的问题，包括建立线程池的考虑
4. 明天重点工作首先理解moduo的线程，了解他是怎么封装的，另外，对于代码中的EventLoopThread和EventLoopThreadPool两个类进行具体的分析