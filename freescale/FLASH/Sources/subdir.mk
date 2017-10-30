################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/AD1.c" \
"../Sources/CPU.c" \
"../Sources/DMK-VF11-03.c" \
"../Sources/EInt1.c" \
"../Sources/IEE1.c" \
"../Sources/IIC.c" \
"../Sources/PWM1.c" \
"../Sources/PWM2.c" \
"../Sources/PWM3.c" \
"../Sources/TI1.c" \
"../Sources/diagnostic_service_slave.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/AD1.c \
../Sources/CPU.c \
../Sources/DMK-VF11-03.c \
../Sources/EInt1.c \
../Sources/IEE1.c \
../Sources/IIC.c \
../Sources/PWM1.c \
../Sources/PWM2.c \
../Sources/PWM3.c \
../Sources/TI1.c \
../Sources/diagnostic_service_slave.c \
../Sources/main.c \

OBJS += \
./Sources/AD1_c.obj \
./Sources/CPU_c.obj \
./Sources/DMK-VF11-03_c.obj \
./Sources/EInt1_c.obj \
./Sources/IEE1_c.obj \
./Sources/IIC_c.obj \
./Sources/PWM1_c.obj \
./Sources/PWM2_c.obj \
./Sources/PWM3_c.obj \
./Sources/TI1_c.obj \
./Sources/diagnostic_service_slave_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/AD1_c.obj" \
"./Sources/CPU_c.obj" \
"./Sources/DMK-VF11-03_c.obj" \
"./Sources/EInt1_c.obj" \
"./Sources/IEE1_c.obj" \
"./Sources/IIC_c.obj" \
"./Sources/PWM1_c.obj" \
"./Sources/PWM2_c.obj" \
"./Sources/PWM3_c.obj" \
"./Sources/TI1_c.obj" \
"./Sources/diagnostic_service_slave_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/AD1_c.d \
./Sources/CPU_c.d \
./Sources/DMK-VF11-03_c.d \
./Sources/EInt1_c.d \
./Sources/IEE1_c.d \
./Sources/IIC_c.d \
./Sources/PWM1_c.d \
./Sources/PWM2_c.d \
./Sources/PWM3_c.d \
./Sources/TI1_c.d \
./Sources/diagnostic_service_slave_c.d \
./Sources/main_c.d \

C_DEPS_QUOTED += \
"./Sources/AD1_c.d" \
"./Sources/CPU_c.d" \
"./Sources/DMK-VF11-03_c.d" \
"./Sources/EInt1_c.d" \
"./Sources/IEE1_c.d" \
"./Sources/IIC_c.d" \
"./Sources/PWM1_c.d" \
"./Sources/PWM2_c.d" \
"./Sources/PWM3_c.d" \
"./Sources/TI1_c.d" \
"./Sources/diagnostic_service_slave_c.d" \
"./Sources/main_c.d" \

OBJS_OS_FORMAT += \
./Sources/AD1_c.obj \
./Sources/CPU_c.obj \
./Sources/DMK-VF11-03_c.obj \
./Sources/EInt1_c.obj \
./Sources/IEE1_c.obj \
./Sources/IIC_c.obj \
./Sources/PWM1_c.obj \
./Sources/PWM2_c.obj \
./Sources/PWM3_c.obj \
./Sources/TI1_c.obj \
./Sources/diagnostic_service_slave_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/AD1_c.obj: ../Sources/AD1.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/AD1.args" -o "Sources/AD1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/CPU_c.obj: ../Sources/CPU.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/CPU.args" -o "Sources/CPU_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/DMK-VF11-03_c.obj: ../Sources/DMK-VF11-03.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/DMK-VF11-03.args" -o "Sources/DMK-VF11-03_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/EInt1_c.obj: ../Sources/EInt1.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/EInt1.args" -o "Sources/EInt1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/IEE1_c.obj: ../Sources/IEE1.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/IEE1.args" -o "Sources/IEE1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/IIC_c.obj: ../Sources/IIC.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/IIC.args" -o "Sources/IIC_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/PWM1_c.obj: ../Sources/PWM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/PWM1.args" -o "Sources/PWM1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/PWM2_c.obj: ../Sources/PWM2.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/PWM2.args" -o "Sources/PWM2_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/PWM3_c.obj: ../Sources/PWM3.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/PWM3.args" -o "Sources/PWM3_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/TI1_c.obj: ../Sources/TI1.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/TI1.args" -o "Sources/TI1_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/diagnostic_service_slave_c.obj: ../Sources/diagnostic_service_slave.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/diagnostic_service_slave.args" -o "Sources/diagnostic_service_slave_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: S12Z Compiler'
	"$(S12Z_ToolsDirEnv)/mwccs12lisa" -c @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


