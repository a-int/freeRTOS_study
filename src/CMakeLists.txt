project(${CMAKE_PROJECT_NAME})

set(SOURCES	
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/startup_stm32f411xe.s
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/system_stm32f4xx.c
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/segger_fault_handler.c
	freertos.c
)

add_executable( freertos.elf 
	${SOURCES}
)

target_include_directories(freertos.elf  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/)
target_include_directories(freertos.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/freertos/)
target_include_directories(freertos.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/llcm4/include/llcm/)

target_link_options(freertos.elf  PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
)

target_link_libraries(freertos.elf
	llcm
	freertos_kernel
)
