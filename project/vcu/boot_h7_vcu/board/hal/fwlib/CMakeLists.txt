# add the sources here
set(sources
   
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c 
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c 
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_fdcan.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c 
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c 
STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc.c
)

# callback cmake module
include(file)
add_src_list(${sources})
