file(GLOB_RECURSE app_sources
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)
add_library(controllers STATIC
        ${app_sources}
)
target_include_directories(controllers PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # 暴露 controllers 头文件
)
target_link_libraries(controllers PUBLIC
        interfaces  # 依赖接口层
)