################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/led.c \
../Src/main.c \
../Src/rcc.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/led.o \
./Src/main.o \
./Src/rcc.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/led.d \
./Src/main.d \
./Src/rcc.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32WB -DP_NUCLEO_WB55_NUCLEO -DSTM32WB55RGVx -c -I../Inc -I/home/neillsyard/Dropbox/Repository/STM32Cube_FW_WB_V1.12.1/Drivers/CMSIS/Device/ST/STM32WBxx/Include -I/home/neillsyard/Dropbox/Repository/STM32Cube_FW_WB_V1.12.1/Drivers/CMSIS/Include -I/home/neillsyard/Dropbox/Repository/STM32Cube_FW_WB_V1.12.1/Drivers/CMSIS/Core/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

