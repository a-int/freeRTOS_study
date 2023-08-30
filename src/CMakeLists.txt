project(${CMAKE_PROJECT_NAME})

set(SOURCES	
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/startup_stm32f411xe.s
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/system_stm32f4xx.c
	${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/segger_fault_handler.c
)

add_executable( queue10.elf 
	${SOURCES}
	queue10.c
)

target_include_directories(queue10.elf  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/)
target_include_directories(queue10.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/freertos_study/)
target_include_directories(queue10.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/llcm4/include/llcm/)

target_link_options(queue10.elf  PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
)

target_link_libraries(queue10.elf
	llcm
	usart
	freertos_kernel
)

add_executable( queue11.elf 
	${SOURCES}
	queue11.c
)

target_include_directories(queue11.elf  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/)
target_include_directories(queue11.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/freertos_study/)
target_include_directories(queue11.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/llcm4/include/llcm/)

target_link_options(queue11.elf  PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
)

target_link_libraries(queue11.elf
	freertos_kernel
	llcm
	usart
)

add_executable( queue12.elf 
	${SOURCES}
	queue12.c
)

target_include_directories(queue12.elf  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/)
target_include_directories(queue12.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/freertos_study/)
target_include_directories(queue12.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/llcm4/include/llcm/)

target_link_options(queue12.elf  PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
)

target_link_libraries(queue12.elf
	freertos_kernel
	llcm
	usart
)

add_executable( timers13.elf 
	${SOURCES}
	timers13.c
)

target_include_directories(queue13.elf  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/vendor/)
target_include_directories(queue13.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/freertos_study/)
target_include_directories(queue13.elf PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../external/llcm4/include/llcm/)

target_link_options(queue13.elf  PRIVATE 
    ${arch_flags} 
    ${common_flags}
    ${link_flags}
)

target_link_libraries(queue13.elf
	freertos_kernel
	llcm
	usart
)
