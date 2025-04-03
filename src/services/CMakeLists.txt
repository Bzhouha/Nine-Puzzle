# 递归收集所有工具模块源码
file(GLOB_RECURSE services_sources
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

# 生成工具模块静态库
add_library(services STATIC
        ${services_sources}
)
# 自动收集 services/ 下所有子目录的路径
file(GLOB_RECURSE services_include_dirs
        LIST_DIRECTORIES true
        "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
# 过滤出目录（排除文件）
list(FILTER services_include_dirs INCLUDE REGEX ".*/$")
# 添加所有子目录到包含路径
target_include_directories(services PUBLIC ${services_include_dirs})

target_link_libraries(controllers PUBLIC
        interfaces  # 依赖接口层
)