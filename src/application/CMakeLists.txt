# ---------------------- 基础配置 ----------------------
# 定义可执行文件名和主源码
add_executable(nine_puzzle
        main.cpp
        runtime/MPIcontext.cpp
)

# ---------------------- 源文件收集 ----------------------
# 递归收集 runtime 子目录中的所有源文件（支持子目录嵌套）
file(GLOB_RECURSE app_sources
        "${CMAKE_CURRENT_SOURCE_DIR}/runtime/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/runtime/*.cxx"
)
# 将收集的源文件添加到可执行目标
target_sources(nine_puzzle PRIVATE
        ${app_sources}
)

# ---------------------- 头文件路径 ----------------------
# 如果 runtime 目录中有私有头文件（非接口层），添加路径
target_include_directories(nine_puzzle PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/runtime"
)

# ---------------------- 依赖项链接 ----------------------
# 链接接口层库（自动传递头文件路径）
target_link_libraries(nine_puzzle PRIVATE
        interfaces  # 来自 src/interfaces
)

# ---------------------- 高级配置 ----------------------
# 可选：设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# 可选：添加编译定义（按需）
# target_compile_definitions(nine_puzzle PRIVATE USE_MPI=1)

install(TARGETS nine_puzzle DESTINATION bin)