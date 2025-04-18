## 动态收集所有子目录并添加为子模块
#
## 获取所有子目录（排除当前目录、测试目录、隐藏目录等）
#file(GLOB SUB_DIRS
#        LIST_DIRECTORIES true    # 只返回目录
#        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"  # 生成相对路径
#        "${CMAKE_CURRENT_SOURCE_DIR}/*"
#)
#list(FILTER SUB_DIRS EXCLUDE REGEX [[^(\\..*|CMakeFiles|tests?|doc|_.*)$]])  # 过滤临时/无效目录
#
## 遍历所有有效子目录并添加构建
#set(SUB_LAYERS "" CACHE INTERNAL "初始化空的子模块列表")
#message(STATUS "<1> 层目录扫描")
#foreach(subdir ${SUB_DIRS})
#    message(STATUS "  -> /" ${subdir})
#    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
#        # subdir 中必须包含 CMakeLists.txt 才认为是有效模块
#        message(STATUS "    -> 添加子层目录: ${subdir}")
#        # 用全局属性标识当前处理的子目录
#        set_property(GLOBAL PROPERTY PROJECT_CURRENT_SUBDIR "${subdir}")
#        message(STATUS "N->" ${PROJECT_CURRENT_SUBDIR})
#        add_subdirectory(${subdir})
#        # 核心逻辑: 检查子模块是否正确定义了 LAYER_NAME
#        get_property(LAYER_NAME GLOBAL PROPERTY "${subdir}_LAYER_NAME")
#        if(NOT LAYER_NAME)
#            message(FATAL_ERROR "    -> 子层 ${subdir} 未在全局属性中设置 LAYER_NAME!")
#        endif()
#        # 将子模块名添加到列表
#        list(APPEND SUB_LAYERS ${LAYER_NAME})
#        message(STATUS "    -> 已收集子层: ${LAYER_NAME}")
#    else()
#        message(STATUS "    -> 非层忽略")
#    endif()
#endforeach()
#
#set(SUB_LAYERS ${SUB_LAYERS} CACHE INTERNAL "已配置的子层列表")
#
## 动态处理依赖关系
##message(STATUS "<2> 构造依赖关系")
##foreach(layer ${SUB_LAYERS})
##    # 从全局属性读取该模块的依赖
##    get_property(deps GLOBAL PROPERTY ${layer}_DEPS)
##    if(deps)
##        target_link_libraries(${layer} PRIVATE ${deps})
##        message(STATUS "  -> 层 ${layer} 链接依赖: ${deps}")
##    endif()
##endforeach()
#
## 收集所有子模块名称
#if(DEFINED SUB_MODULES)
#    message(STATUS "发现 < ${SUB_LAYERS} > layers")
#else()
#    message(WARNING "* 未找到任何子层！请检查子目录是否包含 CMakeLists.txt 并定义了 LAYER_NAME。")
#endif()
#
#
## ---------- 主程序配置 ----------
##add_executable(Nine_Puzzle main.cpp)
##target_link_libraries(Nine_Puzzle PRIVATE
##        ${SUB_MODULES}
##        yaml-cpp::yaml-cpp
##        Boost::boost
##        PkgConfig::PETSC
##)

# 自动搜索并添加包含CMakeLists.txt的直接子目录
file(GLOB SUBDIRS LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/CMakeLists.txt)
            message(STATUS "Adding subdirectory: ${SUBDIR}")
            add_subdirectory(${SUBDIR})
        endif()
    endif()
endforeach()