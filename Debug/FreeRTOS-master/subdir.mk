################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS-master/croutine.c \
../FreeRTOS-master/heap_4.c \
../FreeRTOS-master/list.c \
../FreeRTOS-master/port.c \
../FreeRTOS-master/queue.c \
../FreeRTOS-master/tasks.c \
../FreeRTOS-master/timers.c 

OBJS += \
./FreeRTOS-master/croutine.o \
./FreeRTOS-master/heap_4.o \
./FreeRTOS-master/list.o \
./FreeRTOS-master/port.o \
./FreeRTOS-master/queue.o \
./FreeRTOS-master/tasks.o \
./FreeRTOS-master/timers.o 

C_DEPS += \
./FreeRTOS-master/croutine.d \
./FreeRTOS-master/heap_4.d \
./FreeRTOS-master/list.d \
./FreeRTOS-master/port.d \
./FreeRTOS-master/queue.d \
./FreeRTOS-master/tasks.d \
./FreeRTOS-master/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-master/%.o: ../FreeRTOS-master/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


