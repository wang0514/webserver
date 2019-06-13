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
EPOLL_CLOEXEC：这是这个参数唯一的有效值，如果这个参数设置为这个。那么当进程替换映像的时候会关闭这个文件描述符，
这样新的映像中就无法对这个文件描述符操作，适用于多进程编程+映像替换的环境里
返回值：
success：返回一个非0 的未使用过的最小的文件描述符
error：-1 errno被设置
在 epoll_create () 的最初实现版本时， size参数的作用是创建epoll实例时候告诉内核需要使用多少个文件描述符。
内核会使用 size 的大小去申请对应的内存(如果在使用的时候超过了给定的size， 内核会申请更多的空间)。
现在，这个size参数不再使用了（内核会动态的申请需要的内存）。但要注意的是，这个size必须要大于0，
为了兼容旧版的linux 内核的代码。
  
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

## C++中std::bind、std::function
这篇帖子已经讲的很清楚了  
[C++ 之std::function()及std::bind() 学习](https://blog.csdn.net/p942005405/article/details/84760715)
## 进程id，线程id，唯一线程id（进程ID，内核线程ID，用户态线程ID
）
* pid，每个进程的id，类型为pid_t，可以通过getpid()取得。
* 线程id，类型为pthread_t，这个id在每个进程里是唯一的，它只用于在进程里区分某个线程，也就是说不同的进程里可能有两个线程的线程id是一样的。可以由pthread_self()取得。
* tid，线程的真实id，操作系统保证这个值对于每个线程是唯一的，也就是说进程1下面的线程要和进程2下面的线程沟通，只能使用tid。这个值只能通过linux的系统调用取得，syscall(SYS_gettid)

## string中c_str()的用法
c_str()函数返回一个指向正规C字符串的指针常量, 内容与本string串相同。这是为了与c语言兼容，在c语言中没有string类型，故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式。注意：一定要使用strcpy()函数 等来操作方法c_str()返回的指针。
```
 char c[20];
 string s="1234";
 strcpy(c,s.c_str());
```
## prctl()函数功能
```
int prctl ( int option,unsigned long arg2,unsigned long arg3,unsigned long arg4,unsigned long arg5 )
```
这个系统调用指令是为进程制定而设计的，明确的选择取决于option:
PR_GET_PDEATHSIG :返回处理器信号；  
PR_SET_PDEATHSIG :arg2作为处理器信号pdeath被输入，正如其名，如果父进程不能再用，进程接受这个信号。  
PR_GET_DUMPABLE :返回处理器标志dumpable;  
PR_SET_DUMPABLE :arg2作为处理器标志dumpable被输入。  
PR_GET_NAME :返回调用进程的进程名字给参数arg2; （Since Linux2.6.9）  
PR_SET_NAME :把参数arg2作为调用进程的经常名字。（SinceLinux 2.6.11）  
PR_GET_TIMING :  
PR_SET_TIMING :判定和修改进程计时模式,用于启用传统进程计时模式的  
PR_TIMING_STATISTICAL，或用于启用基于时间戳的进程计时模式的  
PR_TIMING_TIMESTAMP。

## static_cast和dynamic_cast详解
[static_cast和dynamic_cast详解](https://blog.csdn.net/u014624623/article/details/79837849)   
派生类不仅有自己的方法和属性，同时它还包括从父类继承来的方法和属性。当我们从派生类向基类转换时，不管用传统的c语言还是c++转换方式都可以百分百转换成功。但是可怕是向下转换类型，也就是我们从基类向派生类转换，当我们采用传统的C语言和c++转换时，就会出现意想不到的情况，因为转换后派生类自己的方法和属性丢失了，一旦我们去调用派生类的方法和属性那就糟糕了，这就是对类继承关系和内存分配理解不清晰导致的。好在c++增加了static_cast和dynamic_cast运用于继承关系类间的强制转化

1 static_cast和dynamic_cast使用方式
```
static_cast< new_type >(expression) 
dynamic_cast< new_type >(expression) 
备注：new_type为目标数据类型，expression为原始数据类型变量或者表达式。
```
2 static_cast详解：
static_cast相当于传统的C语言里的强制转换，该运算符把expression转换为new_type类型，用来强迫隐式转换如non-const对象转为const对象，编译时检查，用于非多态的转换，可以转换指针及其他，但没有运行时类型检查来保证转换的安全性。它主要有如下几种用法：  
* 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。   
-- 进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；   
-- 进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。 
* 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。 
* 把空指针转换成目标类型的空指针。 
* 把任何类型的表达式转换成void类型。 
* 注意：static_cast不能转换掉expression的const、volatile、或者__unaligned属性

3 dynamic_cast详解：
```
转换方式： 
dynamic_cast< type* >(e) //type必须是一个类类型且必须是一个有效的指针 
dynamic_cast< type& >(e) //type必须是一个类类型且必须是一个左值 
dynamic_cast< type&& >(e) //type必须是一个类类型且必须是一个右值
```
e的类型必须符合以下三个条件中的任何一个： 
* e的类型是目标类型type的公有派生类 
* e的类型是目标type的共有基类 
* e的类型就是目标type的类型。

如果一条dynamic_cast语句的转换目标是指针类型并且失败了，则结果为0。如果转换目标是引用类型并且失败了，则dynamic_cast运算符将抛出一个std::bad_cast异常(该异常定义在typeinfo标准库头文件中)。e也可以是一个空指针，结果是所需类型的空指针。

dynamic_cast主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换（cross cast）。

在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的；在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。dynamic_cast是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作  
（1）指针类型 
    举例，Base为包含至少一个虚函数的基类，Derived是Base的共有派生类，如果有一个指向Base的指针bp，我们可以在运行时将它转换成指向Derived的指针  
（2）引用类型
    因为不存在所谓空引用，所以引用类型的dynamic_cast转换与指针类型不同，在引用转换失败时，会抛出std::bad_cast异常，该异常定义在头文件typeinfo中。
    
## snprintf函数使用总结
```
【函数原型】

int snprintf(char *str, size_t size, const char *format, ...);

【函数参数】

str:目标字符串；size:拷贝字节数(Bytes); format:源字符串; ...格式

【函数功能】

最多从源字符串format中拷贝size字节的内容(含字符串结尾标志'\0')到目标字符串

The  functions  snprintf() write  at most size bytes (including the terminating null byte ('\0')) to str.

【返回值】

成功返回源串的长度(strlen, 不含'\0')

失败返回负值
```
