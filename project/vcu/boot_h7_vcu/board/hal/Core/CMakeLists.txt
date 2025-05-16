# add the sources here
set(sources
Src/flash.c
Src/gpio.c
Src/stm32h7xx_it.c 
Src/stm32h7xx_hal_msp.c
Src/system_stm32h7xx.c
Src/usart.c
Src/fdcan.c
Src/dma.c
startup_stm32h743xx.s
)

# callback cmake module
include(file)
add_src_list(${sources})