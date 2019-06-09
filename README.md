# 学习muduo库时遇到的一些知识点的总结
## __thread 关键字（注意是两个横线）
 * __thread使用规则：只能修饰POD类型(类似整型指针的标量，不带自定义的构造、拷贝、赋值、析构的类型，二进制内容可以任意复制memset,memcpy,且内容可以复原)，不能修饰class类型，因为无法自动调用构造函数和析构函数，可以用于修饰全局变量，函数内的静态变量，不能修饰函数的局部变量或者class的普通成员变量，且__thread变量值只能初始化为编译器常量(值在编译器就可以确定const int i=5,运行期常量是运行初始化后不再改变const int i=rand()).
 * __thread变量是每个线程有一份独立实体，各个线程的变量值互不干扰。除了这个用途，他还可以修饰那些“值可能会变，带有全局性，但是又不值得用全局锁保护”的变量
## eventfd
  eventfd()创建一个“eventfd对象”，这个对象能被用户空间应用用作一个事件等待/响应机制，靠内核去响应用户空间应用事件。这个对象包含一个由内核保持的无符号64位整型计数器。这个计数器由参数initval说明的值来初始化。它的标记可以有以下属性：
  * EFD_CLOEXEC：FD_CLOEXEC，简单说就是fork子进程时不继承，对于多线程的程序设上这个值不会有错的。
  * EFD_NONBLOCK：文件会被设置成O_NONBLOCK，一般要设置。
  * EFD_SEMAPHORE：（2.6.30以后支持）支持semophore语义的read，简单说就值递减1。
## ssize_t 和 size_t
ssize_t是什么类型的？

* 解释一：为了增强程序的可移植性，便有了size_t，它是为了方便系统之间的移植而定义的，不同的系统上，定义size_t可能不一样。

     在32位系统上 定义为 unsigned int 也就是说在32位系统上是32位无符号整形。在64位系统上定义为 unsigned long 也就是说在64位系统上是64位无符号整形。size_t一般用来表示一种计数，比如有多少东西被拷贝等。例如：sizeof操作符的结果类型是size_t，该类型保证能容纳实现所建立的最大对象的字节大小。 它的意义大致是“适于计量内存中可容纳的数据项目个数的无符号整数类型”。所以，它在数组下标和内存管理函数之类的地方广泛使用。而ssize_t这个数据类型用来表示可以被执行读写操作的数据块的大小.它和size_t类似,但必需是signed.意即：它表示的是signed size_t类型的。

    typedef unsigned long size_t

* 解释二：ssize_t是signed size_t，

    size_t是标准C库中定义的，应为unsigned int。定义为typedef int ssize_t。

    而ssize_t:这个数据类型用来表示可以被执行读写操作的数据块的大小.它和size_t类似,但必需是signed.意即：它表示的是sign size_t类型的。
## assert（）
 assert的作用是先计算表达式expression，如果其值为假（即为0），那么它先想stderr打印一条出错信息，谈后通过调用abort来终止程序运行
```
#inclide<assert.h>
void assert(int expression);
```
## epoll
```
#include <sys/epoll.h>
int epoll_create1(int flags);
功能：创建一个多路复用的实例
参数：
flags：
0:如果这个参数是0，这个函数等价于poll_create（0）
EPOLL_CLOEXEC：这是这个参数唯一的有效值，如果这个参数设置为这个。那么当进程替换映像的时候会关闭这个文件描述符，这样新的映像中就无法对这个文件描述符操作，适用于多进程编程+映像替换的环境里
返回值：
success：返回一个非0 的未使用过的最小的文件描述符
error：-1 errno被设置
在 epoll_create () 的最初实现版本时， size参数的作用是创建epoll实例时候告诉内核需要使用多少个文件描述符。内核会使用 size 的大小去申请对应的内存(如果在使用的时候超过了给定的size， 内核会申请更多的空间)。现在，这个size参数不再使用了（内核会动态的申请需要的内存）。但要注意的是，这个size必须要大于0，为了兼容旧版的linux 内核的代码。
  
--------------------------------------------------------------------

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
功能：操作一个多路复用的文件描述符
参数：
epfd：epoll_create1的返回值
op：要执行的命令
EPOLL_CTL_ADD：向多路复用实例加入一个连接socket的文件描述符
EPOLL_CTL_MOD：改变多路复用实例中的一个socket的文件描述符的触发事件
EPOLL_CTL_DEL：移除多路复用实例中的一个socket的文件描述符
fd：要操作的socket的文件描述符
event：
typedef union epoll_data {
               void        *ptr;
               int          fd;
               uint32_t     u32;
               uint64_t     u64;
           } epoll_data_t;

struct epoll_event {
               uint32_t     events;      /* Epoll events */
               epoll_data_t data;        /* User data variable */
};
events可以是下列命令的任意按位与
EPOLLIN：对应的文件描述有可以读取的内容
EPOLLOUT：对应的文件描述符有可以写入
EPOLLRDHUP：写到一半的时候连接断开
EPOLLPRI：发生异常情况，比如所tcp连接中收到了带外消息
EPOLLET：设置多路复用实例的文件描述符的事件触发机制为边沿触发，默认为水平触发
1、当多路复用的实例中注册了一个管道，并且设置了触发事件EPOLLIN，
2、管道对端的写入2kb的数据，
3、epoll_wait收到了一个可读事件，并向上层抛出，这个文件描述符
4、调用者调用read读取了1kb的数据，
5、再次调用epoll_wait
```