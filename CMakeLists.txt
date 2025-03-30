cmake_minimum_required(VERSION 3.30)
project(Nine_Puzzle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 必须使用 C++17，否则报错
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# set root of location to find PETSc's pkg-config
set(PETSC $ENV{PETSC_DIR}/$ENV{PETSC_ARCH})
set(ENV{PKG_CONFIG_PATH} ${PETSC}/lib/pkgconfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(PETSC REQUIRED IMPORTED_TARGET PETSc)

# Remove the lines below if you do not wish to have PETSc determine the compilers
execute_process ( COMMAND pkg-config PETSc --variable=ccompiler COMMAND tr -d '\n' OUTPUT_VARIABLE C_COMPILER)
SET(CMAKE_C_COMPILER ${C_COMPILER})
execute_process ( COMMAND pkg-config PETSc --variable=cxxcompiler COMMAND tr -d '\n' OUTPUT_VARIABLE CXX_COMPILER)
if (CXX_COMPILER)
    SET(CMAKE_CXX_COMPILER ${CXX_COMPILER})
endif (CXX_COMPILER)
execute_process ( COMMAND pkg-config PETSc --variable=fcompiler COMMAND tr -d '\n' OUTPUT_VARIABLE FORTRAN_COMPILER)
if (FORTRAN_COMPILER)
    SET(CMAKE_Fortran_COMPILER ${FORTRAN_COMPILER})
    enable_language(Fortran)
endif (FORTRAN_COMPILER)

find_package(yaml-cpp REQUIRED)

# 设置源码根目录为 ${PROJECT_SOURCE_DIR}
set(ROOT_DIR ${PROJECT_SOURCE_DIR})
# 定义源码和头文件路径
set(SRC_DIR ${ROOT_DIR}/src)
set(INCLUDE_DIR ${ROOT_DIR}/include)
# 收集源文件和头文件（自动扫描）
file(GLOB SOURCES "${SRC_DIR}/*.cpp")    # 包含所有 .cpp 文件
file(GLOB HEADERS "${INCLUDE_DIR}/*.h")  # 包含所有 .h 文件

add_executable(Nine_Puzzle ${SOURCES})

target_include_directories(Nine_Puzzle PRIVATE ${INCLUDE_DIR})

target_link_libraries(Nine_Puzzle PRIVATE yaml-cpp::yaml-cpp PkgConfig::PETSC)

# 编译选项（可选）
#if(MSVC)
#    target_compile_options(Nine_Puzzle PRIVATE /W4 /WX)
#else()
#    target_compile_options(Nine_Puzzle PRIVATE -Wall -Wextra -Werror -pedantic)
#endif()

install(
        TARGETS Nine_Puzzle
        RUNTIME DESTINATION bin     # 安装到 ${CMAKE_INSTALL_PREFIX}/bin
# ARCHIVE DESTINATION lib   # 如果是静态库则启用
)
