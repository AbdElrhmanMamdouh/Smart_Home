################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Interface.c \
../HKP_Interface.c \
../LCD_Program.c \
../SERVOMOTOR_Program.c \
../main.c 

OBJS += \
./DIO_Interface.o \
./HKP_Interface.o \
./LCD_Program.o \
./SERVOMOTOR_Program.o \
./main.o 

C_DEPS += \
./DIO_Interface.d \
./HKP_Interface.d \
./LCD_Program.d \
./SERVOMOTOR_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

