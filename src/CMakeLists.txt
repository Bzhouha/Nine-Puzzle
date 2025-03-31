# 动态收集所有子目录并添加为子模块

# 获取所有子目录（排除当前目录、测试目录、隐藏目录等）
file(GLOB SUB_DIRS
        LIST_DIRECTORIES true    # 只返回目录
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"  # 生成相对路径
        "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
list(FILTER SUB_DIRS EXCLUDE REGEX [[^(\\..*|CMakeFiles|tests?|doc|_.*)$]])  # 过滤临时/无效目录

# 遍历所有有效子目录并添加构建
set(SUB_MODULES "" CACHE INTERNAL "初始化空的子模块列表")
message(STATUS "<1> 解析文件")
foreach(subdir ${SUB_DIRS})
    message(STATUS "  -> " ${subdir})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        # subdir 中必须包含 CMakeLists.txt 才认为是有效模块
        message(STATUS "    -> 添加子模块目录: ${subdir}")
        # 用全局属性标识当前处理的子目录
        set_property(GLOBAL PROPERTY PROJECT_CURRENT_SUBDIR "${subdir}")
        add_subdirectory(${subdir})
        # ⭐核心逻辑: 检查子模块是否正确定义了 MODULE_NAME
        get_property(MODULE_NAME GLOBAL PROPERTY "${subdir}_MODULE_NAME")
        if(NOT MODULE_NAME)
            message(FATAL_ERROR "    -> 子模块 ${subdir} 未在全局属性中设置 MODULE_NAME!")
        endif()
        # 将子模块名添加到列表
        list(APPEND SUB_MODULES ${MODULE_NAME})
        message(STATUS "    -> 已收集子模块: ${MODULE_NAME}")
    else()
        message(STATUS "    -> 忽略非模块目录: ${subdir}")
    endif()
endforeach()

set(SUB_MODULES ${SUB_MODULES} CACHE INTERNAL "已配置的子模块列表")

# 动态处理依赖关系
message(STATUS "<2> 构造依赖关系")
foreach(module ${SUB_MODULES})
    # 从全局属性读取该模块的依赖
    get_property(deps GLOBAL PROPERTY ${module}_DEPS)
    if(deps)
        target_link_libraries(${module} PRIVATE ${deps})
        message(STATUS "  -> 模块 ${module} 链接依赖: ${deps}")
    endif()
endforeach()

# 收集所有子模块名称
if(DEFINED SUB_MODULES)
    message(STATUS "所有子模块列表为：${SUB_MODULES}")
else()
    message(WARNING "* 未找到任何子模块！请检查子目录是否包含 CMakeLists.txt 并定义了 MODULE_NAME。")
endif()
