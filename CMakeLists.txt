cmake_minimum_required(VERSION 3.15)
project(sebbypass)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -m64)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -m64)

set(MAIN_SRC
    src/Main.cpp
)

set(MINHOOK_SRC
    src/thirdparty/minhook/buffer.c
    src/thirdparty/minhook/hook.c
    src/thirdparty/minhook/trampoline.c
    src/thirdparty/minhook/hde/hde32.c
    src/thirdparty/minhook/hde/hde64.c
)

set(HOOKS_SRC
    src/hooks/Hooks.cpp
    src/hooks/CallNextHookEx.cpp
    src/hooks/NtQuerySystemInformation.cpp
    src/hooks/SetWindowDisplayAffinity.cpp
    src/hooks/SetWindowsHookExA.cpp
    src/hooks/SetWinEventHook.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${MINHOOK_SRC}
    ${HOOKS_SRC}
    ${MAIN_SRC}
)

target_compile_options(${PROJECT_NAME} PRIVATE -mavx -mavx2)
target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/thirdparty
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/hooks
)