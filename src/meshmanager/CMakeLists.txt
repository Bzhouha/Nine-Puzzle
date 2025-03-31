# 获取目录名并设置为模块名
get_property(current_subdir GLOBAL PROPERTY PROJECT_CURRENT_SUBDIR)
if(NOT current_subdir)
    message(FATAL_ERROR "    -> 无法获取 PROJECT_CURRENT_SUBDIR，父脚本需设置此属性！")
endif()
set(MODULE_NAME ${current_subdir})
set_property(GLOBAL PROPERTY "${current_subdir}_MODULE_NAME" "${MODULE_NAME}")

# 定义依赖并存入全局属性
set_property(GLOBAL PROPERTY ${MODULE_NAME}_DEPS "globalvars fileManager")

# 指定源码和头文件
file(GLOB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)
file(GLOB HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

# 创建静态/动态库
add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})  # 或 SHARED

# 暴露头文件目录（外部可访问）
target_include_directories(${MODULE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

