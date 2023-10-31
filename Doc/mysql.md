ubuntu环境安装mysql-server和mysql开发包，包括mysql头文件和动态库文件，命令如下：


```shell
sudo apt-get install mysql-server 
sudo apt-get install libmysqlclient-dev =》 安装开发包
```

ubuntu默认安装最新的mysql，但是初始的用户名和密码是自动生成的，按下面步骤修改mysql的root用户密码为123456

【step 1】tony@tony-virtual-machine:~$ sudo cat /etc/mysql/debian.cnf
 host = localhost
 user = debian-sys-maint        《==============  初始的用户名
 password = Kk3TbShbFNvjvhpM   《==============  初始的密码
 【step 2】用上面初始的用户名和密码，登录mysql server，修改root用户的密码，命令如下：
 
```shell
 tony@tony-virtual-machine:~$ mysql -u debian-sys-maint -pKk3TbShbFNvjvhpM 
```
命令解释： -u后面是上面查看的用户名 -p后面紧跟上面查看的密码

```shell
mysql> update mysql.user set authentication_string=password('123456') where user='root' and host='localhost';
mysql> update mysql.user set plugin="mysql_native_password";
mysql> flush privileges;
Query OK, 0 rows affected (0.01 sec)
mysql> exit
Bye
```

创建相关数据库以及设置编码