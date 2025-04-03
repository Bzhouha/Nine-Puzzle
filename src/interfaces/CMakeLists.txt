# 定义接口库
add_library(interfaces INTERFACE
        ../application/runtime/configparser.h)

# 暴露头文件路径（递归包含所有子目录）
target_include_directories(interfaces INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 可选：收集头文件增强 IDE 支持
file(GLOB_RECURSE interface_headers "*.h" "*.hpp")
target_sources(interfaces INTERFACE ${interface_headers})

# 可选：传递依赖（如仅头文件库）
target_link_libraries(interfaces INTERFACE
        PkgConfig::PETSC
)
