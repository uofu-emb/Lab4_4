add_executable(test_signal test_signal.c ../src/signaling.c unity_config.c)

target_link_libraries(test_signal PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  unity
)
add_executable(Lab4_test_fifo test_fifo.c ../src/fifo.c unity_config.c)
target_link_libraries(Lab4_test_fifo PRIVATE
  pico_stdlib
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  pico_cyw43_arch_none
  unity
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(test_signal PRIVATE
        pico_cyw43_arch_none
    )
endif()

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(test_signal 0)
pico_enable_stdio_usb(test_signal 1)

# This will speed up the simulation, since data won't be copied from the flash controller.
# It does make the binary non-persistent on a real microcontroller.
# pico_set_binary_type(test_signal no_flash)

find_program(RENODE renode
# This is extra stuff so it can find the mac installation paths.
 NAMES macos_run.command Renode.exe
 PATHS /Applications/Renode.app/Contents/MacOS)

set(RENODE_FLAGS
  --disable-xwt
  --port -2
  --pid-file renode.pid
  --console
  )

add_test(NAME simulate_test_signal COMMAND
    ${RENODE}
     ${RENODE_FLAGS}
    -e "$ELF=@$<TARGET_FILE:test_signal>; $WORKING=@${CMAKE_SOURCE_DIR}; include @${CMAKE_SOURCE_DIR}/test/simulate.resc; start"
    )

add_custom_target(flash_test picotool load -f $<TARGET_FILE:test_signal> DEPENDS test_signal)
