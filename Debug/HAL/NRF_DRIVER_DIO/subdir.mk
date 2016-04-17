################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/NRF_DRIVER_DIO/nrf24.c 

OBJS += \
./HAL/NRF_DRIVER_DIO/nrf24.o 

C_DEPS += \
./HAL/NRF_DRIVER_DIO/nrf24.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/NRF_DRIVER_DIO/%.o: ../HAL/NRF_DRIVER_DIO/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=4000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


