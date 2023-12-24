################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../Application_Header.c \
../DIO.c \
../HomemadeRTOS.c \
../I2C.c \
../Internal_EEPROM.c \
../Interrupt.c \
../Keypad.c \
../LCD.c \
../SPI.c \
../Timer0.c \
../Timer1.c \
../UART.c \
../croutine.c \
../ds3231.c \
../heap_4.c \
../list.c \
../main.c \
../port.c \
../queue.c \
../ssd1306.c \
../tasks.c \
../timers.c 

OBJS += \
./ADC.o \
./Application_Header.o \
./DIO.o \
./HomemadeRTOS.o \
./I2C.o \
./Internal_EEPROM.o \
./Interrupt.o \
./Keypad.o \
./LCD.o \
./SPI.o \
./Timer0.o \
./Timer1.o \
./UART.o \
./croutine.o \
./ds3231.o \
./heap_4.o \
./list.o \
./main.o \
./port.o \
./queue.o \
./ssd1306.o \
./tasks.o \
./timers.o 

C_DEPS += \
./ADC.d \
./Application_Header.d \
./DIO.d \
./HomemadeRTOS.d \
./I2C.d \
./Internal_EEPROM.d \
./Interrupt.d \
./Keypad.d \
./LCD.d \
./SPI.d \
./Timer0.d \
./Timer1.d \
./UART.d \
./croutine.d \
./ds3231.d \
./heap_4.d \
./list.d \
./main.d \
./port.d \
./queue.d \
./ssd1306.d \
./tasks.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


