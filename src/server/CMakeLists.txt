# 将server的项目源代码添加到server的编译列表中
aux_source_directory(. SRC_LIST)
# 生成可执行文件
add_executable(ChatServer ${SRC_LIST})
# 定义链接时的依赖库
target_link_libraries(ChatServer muduo_net muduo_base pthread)