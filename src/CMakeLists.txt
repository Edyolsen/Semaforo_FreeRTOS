add_executable(picow_freertos_Exercicio_11
    main.c
)

# Corrige a saída para build/ em vez de build/src/
set_target_properties(picow_freertos_Exercicio_11 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_sources(picow_freertos_Exercicio_11
    PRIVATE
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
)

target_include_directories(picow_freertos_Exercicio_11 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../config
    ${CMAKE_CURRENT_LIST_DIR}/../tasks
    ${CMAKE_CURRENT_LIST_DIR}/../drivers
)

target_link_libraries(picow_freertos_Exercicio_11 
    pico_stdlib 
    FreeRTOS-Kernel
)

pico_add_extra_outputs(picow_freertos_Exercicio_11)
