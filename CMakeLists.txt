cmake_minimum_required(VERSION 3.30)
project(Nine_Puzzle)

# ---------- 编译器设置 ----------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# ---------- PETSC 配置 ----------
set(PETSC $ENV{PETSC_DIR}/$ENV{PETSC_ARCH})
set(ENV{PKG_CONFIG_PATH} ${PETSC}/lib/pkgconfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(PETSC REQUIRED IMPORTED_TARGET PETSc)
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

# ---------- 第三方依赖 ----------
find_package(yaml-cpp REQUIRED)
find_package(Boost REQUIRED)

# ---------- 集成子模块 ----------
add_subdirectory(src)

# ---------- 编译选项 ----------
#if(MSVC)
#    target_compile_options(Nine_Puzzle PRIVATE /W4 /WX)
#else()
#    target_compile_options(Nine_Puzzle PRIVATE -Wall -Wextra -Werror -pedantic)
#endif()

# ---------- 安装规则 ----------
#install(TARGETS Nine_Puzzle RUNTIME DESTINATION bin)     # 安装到 ${CMAKE_INSTALL_PREFIX}/bin
