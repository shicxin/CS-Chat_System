# 设置CMake版本
cmake_minimum_required(VERSION 3.0)
project(chat)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置可执行文件生成目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/database)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/include/server/user)

# 加栽子目录
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# //                            _ooOoo_  
# //                           o8888888o  
# //                           88" . "88  
# //                           (| -_- |)  
# //                            O\ = /O  
# //                        ____/`---'\____  
# //                      .   ' \\| |// `.  
# //                       / \\||| : |||// \  
# //                     / _||||| -:- |||||- \  
# //                       | | \\\ - /// | |  
# //                     | \_| ''\---/'' | |  
# //                      \ .-\__ `-` ___/-. /  
# //                   ___`. .' /--.--\ `. . __  
# //                ."" '< `.___\_<|>_/___.' >'"".  
# //               | | : `- \`.;`\ _ /`;.`/ - ` : | |  
# //                 \ \ `-. \_ __\ /__ _/ .-` / /  
# //         ======`-.____`-.___\_____/___.-`____.-'======  
# //                            `=---='  
# //  
# //         .............................................  
# //                  佛祖保佑             永无BUG 
# //          佛曰:  
# //                  写字楼里写字间，写字间里程序员；  
# //                  程序人员写程序，又拿程序换酒钱。  
# //                  酒醒只在网上坐，酒醉还来网下眠；  
# //                  酒醉酒醒日复日，网上网下年复年。  
# //                  但愿老死电脑间，不愿鞠躬老板前；  
# //                  奔驰宝马贵者趣，公交自行程序员。  
# //                  别人笑我忒疯癫，我笑自己命太贱；  
# //                  不见满街漂亮妹，哪个归得程序员？
