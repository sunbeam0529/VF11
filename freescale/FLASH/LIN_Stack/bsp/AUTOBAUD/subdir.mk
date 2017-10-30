################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud.c" \

C_SRCS += \
../LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud.c \

OBJS += \
./LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.obj \

OBJS_QUOTED += \
"./LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.obj" \

C_DEPS += \
./LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.d \

C_DEPS_QUOTED += \
"./LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.d" \

OBJS_OS_FORMAT += \
./LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.obj \


# Each subdirectory must supply rules for building sources it contributes
LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.obj: ../LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud.args" -o "LIN_Stack/bsp/AUTOBAUD/lin_lld_autobaud_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

LIN_Stack/bsp/AUTOBAUD/%.d: ../LIN_Stack/bsp/AUTOBAUD/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


