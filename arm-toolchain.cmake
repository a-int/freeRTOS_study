set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(arm-toolchain-path "" CACHE PATH "The path to the arm toolcahin folder")


set(CMAKE_C_COMPILER ${arm-toolchain-path}/bin/arm-none-eabi-gcc CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER ${arm-toolchain-path}/bin/arm-none-eabi-g++ CACHE INTERNAL "")
set(CMAKE_LINKER ${arm-toolchain-path}/bin/arm-none-eabi-ld CACHE INTERNAL "")
set(CMAKE_AR ${arm-toolchain-path}/bin/arm-none-eabi-ar CACHE INTERNAL "")
set(CMAKE_OBJCOPY ${arm-toolchain-path}/bin/arm-none-eabi-objcopy
    CACHE FILEPATH "The toolchain objcopy command " FORCE)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
