# meshManager/CMakeLists.txt
# -----------------------------------------------------------------------------
# 子模块的唯一名称（应与目录名保持一致）
set(MODULE_NAME meshManager)
set(MODULE_NAME ${MODULE_NAME} PARENT_SCOPE)  # ⭐核心：将模块名向上传递到父作用域

# 显式声明依赖（新增）
set(MODULE_DEPENDENCIES fileManager)  # ⭐依赖的模块名
set(MODULE_DEPENDENCIES ${MODULE_DEPENDENCIES} PARENT_SCOPE)  # 暴露给父级

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
target_include_directories(${MODULE_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

