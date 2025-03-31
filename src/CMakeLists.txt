cmake_minimum_required(VERSION 3.15)
# -----------------------------------------------------------------------------
# 动态收集所有子目录并添加为子模块
# -----------------------------------------------------------------------------
# Step 1: 获取所有子目录（排除当前目录、测试目录、隐藏目录等）
set(SUB_MODULES)
file(GLOB SUB_DIRS
        LIST_DIRECTORIES true    # 只返回目录
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"  # 生成相对路径
        "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
list(FILTER SUB_DIRS EXCLUDE REGEX [[^(\\..*|CMakeFiles|tests?|doc|_.*)$]])  # 过滤临时/无效目录

# Step 2: 遍历所有有效子目录并添加构建
foreach(subdir ${SUB_DIRS})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        # subdir 中必须包含 CMakeLists.txt 才认为是有效模块
        message(STATUS "添加子模块目录: ${subdir}")
        # ⭐关键修改: 清除当前 MODULE_NAME 状态以防污染
        unset(MODULE_NAME PARENT_SCOPE)
        add_subdirectory(${subdir})
        # ⭐核心逻辑: 检查子模块是否正确定义了 MODULE_NAME
        if(NOT DEFINED MODULE_NAME)
            message(FATAL_ERROR "子模块 ${subdir} 未定义 MODULE_NAME!")
        endif()
        # 将子模块名添加到列表
        list(APPEND SUB_MODULES ${MODULE_NAME})
        message(STATUS "已收集子模块: ${MODULE_NAME}")
    else()
        message(STATUS "忽略非模块目录: ${subdir}")
    endif()
endforeach()

set(SUB_MODULES ${SUB_MODULES} CACHE INTERNAL "已配置的子模块列表")

# 🔥新增：动态处理依赖关系
foreach(module ${SUB_MODULES})
    if(DEFINED ${module}_DEPENDENCIES)
        # 获取该模块的依赖列表
        set(deps ${${module}_DEPENDENCIES})
        # 链接依赖库
        target_link_libraries(${module} PRIVATE ${deps})
        message(STATUS "模块 ${module} 已链接依赖项: ${deps}")
    endif()
endforeach()

# Step 3: 收集所有子模块名称（需模块 CMakeLists.txt 中的显式定义）
# -----------------------------------------------------
# 原理：每个子模块需要在自己的 CMakeLists.txt 中通过 `set(MODULE_NAME ... PARENT_SCOPE)` 将模块名暴露给上级
# -----------------------------------------------------
if(DEFINED SUB_MODULES)
    message(STATUS "所有子模块列表为：${SUB_MODULES}")
else()
    message(WARNING "未找到任何子模块！请检查子目录是否包含 CMakeLists.txt 并定义了 MODULE_NAME。")
endif()

# -----------------------------------------------------------------------------
# 可选：交叉模块依赖管理（如需要，此处追加依赖关系）
# -----------------------------------------------------------------------------
# target_link_libraries(fileManager PRIVATE globalVars)
