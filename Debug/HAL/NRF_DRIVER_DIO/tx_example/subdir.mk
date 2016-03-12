################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/NRF_DRIVER_DIO/tx_example/main.c 

OBJS += \
./HAL/NRF_DRIVER_DIO/tx_example/main.o 

C_DEPS += \
./HAL/NRF_DRIVER_DIO/tx_example/main.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/NRF_DRIVER_DIO/tx_example/%.o: ../HAL/NRF_DRIVER_DIO/tx_example/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


