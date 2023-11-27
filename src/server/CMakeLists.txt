# 将server的项目源代码添加到server的编译列表中
aux_source_directory(. SRC_LIST)
aux_source_directory(./database DATABASE_LIST)
aux_source_directory(./model MODEL_LIST)
# 生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DATABASE_LIST} ${MODEL_LIST})
# 定义链接时的依赖库
target_link_libraries(ChatServer muduo_net muduo_base pthread mysqlclient)