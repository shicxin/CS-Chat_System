[toc]

# 项目需求

## 背景

在接触到集群服务器这个概念后一直想写个项目练练手，正好对于之前烂尾的使用C语言写的Linux聊天服务器不是很满意，于是使用C++重新编写这个项目。（旧版代码放置于`history`目录下）

## 集群服务器优势

集群服务器是一种计算机系统，它通过一组松散集成的计算机软件或硬件连接起来高度紧密地协作完成计算任务。相比于普通服务器，集群服务器有以下优点：

1.  **高性能**: 集群服务器可以将多台服务器协同工作，共同处理任务，从而提高系统的整体性能，特别是对于需要大量计算或处理的应用程序。
2.  **高可用性和可靠性**: 集群服务器提供了冗余和容错机制，当一个节点发生故障时，其他节点可以接管工作，确保系统的持续可用性。这种架构足以满足企业的业务需求，需要支持7*24时不间断的服务。
3.  **低成本**: 采用计算机集群比用同等计算性能的大型或超级计算机的成本更理想，性价比更高。
4.  **扩展性强**: 集群系统中节点数目可以增长到几千、甚至上万，其扩展性远超单台超级计算机。当服务器的负载压力增高时，集群的架构模式方便增加服务器来应付这种负载带来的压力，同时，如果负载比原来低了，也可以将某一组服务器协调出来作其他的应用服务，调配方便。
5.  **可管理性**: 整个系统可能在物理上很大，要使集群系统变得易管理，就像管理一个单一映像系统一样。在理想状况下，软硬件模块的插入能做到即插即用。

## 项目功能设计

1.   聊天
2.   加好友
3.   群聊
4.   存储离线消息
5.   部署集群

## 项目使用开源模组

1.   muduo C++网络库构造网络模块
2.   MySQL做数据库存储服务器实例数据
3.   JSON for Modern C++为JSON消息格式序列化与反序列化
4.   CMake管理项目源码与编译
5.   nginx的反向代理做负载均衡服务器
6.   redis 使用其发布订阅的功能做服务器中间件，

# 需求具体实现

## 服务器模块划分

1. 基础模块

    定义了基础类：

    1.   用户
    2.   群组

2. 网络模块

    网络模块负责消息的发送与接收；

    直接使用muduo网络库的`TcpServer`类，并使用`EventLoop`类记录事件循环。

3. 业务模块

    1. 添加用户
        通过客户端的注册请求创建一个新的用户

    2. 添加群聊

        通过用户申请创建群聊

    3. 记录离线消息

        用户不在线时存储聊天消息


4.   数据模块

     1.   表设计
     2.   `user `表：记录注册用户信息；
     3.   `allgroup`表：记录群组信息
     4.   `friend`表：记录好友信息
     5.   `groupuser`表：记录群组承成员信息
     6.   `offlinemessage`表：存储离线消息

5.   服务器中间件设计

     使用redis实现的基于发布订阅机制的服务器中间件

## 各个模块实现

### 基础模块

#### 用户

```mermaid
classDiagram
    class user{
        -int id_
        -string name_
        -string password_
        -string state_
        +User(int, string, string, string)
        +SetId(int) void
        +SetName(string)
        +SetPswd(string)
        +SetState(string)
        +GetId() const int
        +GetName() const string
        +GetPswd() const string
        +GetState() const string
    }
```



#### 群组

```mermaid
classDiagram
    GroupUser --|> User
    GroupUser *-- Group
    class GroupUser {
        -string role
        +setRole(string) void
        +getRole() const string
    }
    class Group {
        -int id
        -string name
        -string desc
        -vector~GroupUser~ users
        +Group(int, string, string)
        +setId(int)
        +setName(string)
        +setDesc(string)
        +getId() const int
        +getName() const string
        +getDesc() const string
        +getUsers() vector~GroupUser~&
    }
```



### 数据模块

#### 表设计

`user `表:

```sql
CREATE TABLE `user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT NULL,
  `password` varchar(50) DEFAULT NULL,
  `state` enum('online','offline') CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT 'offline',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8mb3
```

`friend`表：

```sql
CREATE TABLE `friend` (
  `userid` int NOT NULL,
  `friendid` int NOT NULL,
  KEY `userid` (`userid`,`friendid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3
```

`allgroup`表

```sql
CREATE TABLE `allgroup` (
  `id` int NOT NULL AUTO_INCREMENT,
  `groupname` varchar(50) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `groupdesc` varchar(200) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `groupname` (`groupname`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb3
```

`groupuser`表：

```sql
CREATE TABLE `groupuser` (
  `groupid` int NOT NULL,
  `userid` int NOT NULL,
  `grouprole` enum('creator','normal') CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT NULL,
  KEY `groupid` (`groupid`,`userid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3
```

`offlinemessage`表：

```sql
CREATE TABLE `offlinemessage` (
  `userid` int NOT NULL,
  `message` varchar(500) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1
```

#### 数据库类图

```mermaid
classDiagram
	class MySQL {
	-MYSQL *_conn
	+MySQL()
	+~MySQL()
	+*query(string sql) MYSQL_RES
	+update(string sql) bool
	+connect()
	}
```



#### 数据表ER关系图

```mermaid
erDiagram
  USER ||--|{ FRIEND : "has"
  USER {
    int id
    string name
    string password
    enum state
  }
  FRIEND ||--|{ USER : is
  FRIEND {
    int userid
    int friendid
  }
  USER ||--|{ GROUPUSER : joins
  GROUPUSER {
    int groupid
    int userid
    enum grouprole
  }
  ALLGROUP ||--|{ GROUPUSER : contains
  ALLGROUP {
    int id
    string groupname
    string groupdesc
  }
  USER ||--|{ OFFLINEMESSAGE : receives
  OFFLINEMESSAGE {
    int userid
    string message
  }

```


### 网络模块

使用开源项目muduo的TcpServer，在这里列出使用到的方法。

```mermaid
classDiagram
    TcpServer --|> InetAddress
    TcpServer --|> EventLoop
    class TcpServer {
    +TcpServer(EventLoop*, const InetAddress&, const string&)
    +~TcpServer()
    +start()
    +setConnectionCallback(const ConnectionCallback& cb)
    +setMessageCallback(const MessageCallback& cb)
    +setThreadNum(int numThreads)
    }
    class EventLoop {
    +EventLoop()
    +~EventLoop()
    }
    class InetAddress {
        +InetAddress(const StringArg& ip, uint16_t port)
        +~InetAddress()
    }
```



### 业务模块

#### 基础用户模块

```mermaid
classDiagram
    class UserModel {
		+Insert(User &user) bool
		+updataState(User &user) bool
		+query(int id) User
		+resetState() void
    }
```

#### 好友模块

```mermaid
classDiagram
	class FriendModel{
        +insert(int userid, int friendid) 
        +query(int userid) vector~User~
	}
```

#### 群聊模块

```mermaid
classDiagram
    class GroupModel{
        +createGroup(Group &group) bool
        +addGroup(int userid, int groupid, string role) void
        +queryGroups(int userid) vector~Group~
        +queryGroupUsers(int userid, int groupid) vector~int~
    }
```

#### 离线消息模块

```mermaid
classDiagram
    class offlineMsgModel {
        +insert(int userid, string msg) 
        +quert(int userid) vector~string~
        +emove(int userid) void
    }
```



#### 中间件设计

使用redis订阅发布的功能实现的服务器中间件。

## 项目框架

### 单服务器运行逻辑

#### 连接与断开

```mermaid
sequenceDiagram
	actor client as 用户
	participant server as 服务器
	client->>server: 连接\
	server->>server: muduo::net::TcpServer
	Note over server: 1. 调用Acceptor的handleRead()方法，<br>该方法会调用accept()函数来接受新的连接，<br>并获取连接的套接字和地址。<br>2. 调用用户设置的新连接回调函数，<br>该函数可以对新连接进行一些初始化操作，<br>如设置读写回调函数，启动或停止连接等。<br>3. 调用TcpConnection的connectEstablished()方法，<br>该方法会将连接的套接字和地址封装成Channel对象，<br>并注册到EventLoop中，关注可读事件。<br>4. 调用用户设置的连接建立回调函数，<br>该函数可以对连接建立后进行一些操作，<br>如发送欢迎信息，记录日志等。
	client-Xserver: 注销/意外断开连接
```

#### 注册、登录、注销

```mermaid
sequenceDiagram
	actor client as 用户
	participant server as 服务器
	participant database as 数据库
	participant redis as 服务器中间件
	client-)server: 注册/登录
	server-)server: 检查
	alt 密码正确
	server-)server: 记录连接
	server-)database: 插入信息/更新状态
	server-)redis: 注册消息
	server-)database: 查询离线消息
	server-)client: 登录成功、离线消息
	else 账号密码错误
	server-)client: 登录失败
	end
    client-Xserver: 注销/意外断开
	alt 已登录
	server-)database: 更新状态
	server-)redis: 下线消息
	else 未登录
	Note over server: 直接断开
	end
```

#### 加好友、创建群聊、加入群聊

```mermaid
sequenceDiagram
	actor client as 用户
	participant server as 服务器
	participant database as 数据库
	participant redis as 服务器中间件
	client-)server: 加好友/创建群聊/加入群聊
	server-)database: 查询相关信息
	server-)server: 检查
	alt 可以执行
	server-)database: 插入信息/更新状态
	server-)redis: 订阅好友消息
	server-)client: 成功
	else 无权限/无待加用户/无待加群聊
	server-)client: 失败
	end
```

#### 发消息

```mermaid
sequenceDiagram
	actor client1 as 用户
	actor clientx as 需要收消息的用户
	participant server as 服务器
	participant database as 数据库
    client1-)server: 向人发消息
	server-)database: 查询相关信息
    server->>server: 检查好友状态
	alt 在线
    server->>clientx: 收到消息
	else 不在线
    server->>database: 存储离线消息
	end
	client1-)server: 向群聊发消息
	server-)database: 查询相关信息
    server->>server: 检查群聊成员状态
	alt 在线
    server->>clientx: 收到消息
	else 不在线
    server->>database: 存储离线消息
	end
```



### 集群框架

```mermaid
graph LR
	redis(服务器中间件)
    client1(客户端1) o----o root
    client2(客户端2) o----o root
    client3(客户端3) o----o root
    client4(客户端4) o----o root
    clientx(客户端...) o----o root
    subgraph jq [服务器集群]
    	server1(服务器1)
	    server3(服务器3)
    	server2(服务器2)
		server1 -.- server3
		server1 -.- server2
		server2 -.- server3
    end
    root o----o server1
    root o----o server2
    root o----o server3
    client1-.-server1
    client2-.-server2
    client3-.-server3
    client4-.-server1
    clientx-.-server2
	root{负载均衡服务器}
    server1 o----o redis
    server2 o----o redis
    server3 o----o redis
```


# 项目性能评估