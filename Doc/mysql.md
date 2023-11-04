在Ubuntu环境中安装MySQL Server和MySQL开发包。

1. 安装MySQL Server和MySQL开发包
   ```bash
   sudo apt update
   sudo apt install mysql-server libmysqlclient-dev
   ```

2. 安装过程中会提示设置root用户的密码，输入并确认密码。

3. 修改MySQL密码为123456
   - 以root用户身份登录MySQL
     ```bash
     sudo mysql -u root -p
     ```
   - 输入之前设置的root密码
   - 修改root用户的密码为123456
     ```sql
     ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '123456';
     FLUSH PRIVILEGES;
     ```

通过以上步骤，你就可以在Ubuntu环境中安装MySQL Server和MySQL开发包，并将MySQL密码修改为123456了。