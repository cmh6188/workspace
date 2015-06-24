################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/adc_drv.c" \
"../Sources/adc_init.c" \
"../Sources/adc_trigger_init.c" \
"../Sources/clcd.c" \
"../Sources/control.c" \
"../Sources/dcMotor.c" \
"../Sources/distanceSensor.c" \
"../Sources/emios_init.c" \
"../Sources/filter.c" \
"../Sources/gpio_drv.c" \
"../Sources/intc_init.c" \
"../Sources/intc_pit.c" \
"../Sources/intc_siu.c" \
"../Sources/intc_sw_vecttable.c" \
"../Sources/lineScan.c" \
"../Sources/linflex_init.c" \
"../Sources/linflex_var.c" \
"../Sources/main.c" \
"../Sources/pit_init.c" \
"../Sources/rappid_utils.c" \
"../Sources/rchw_init.c" \
"../Sources/romcopy.c" \
"../Sources/rtc_init.c" \
"../Sources/servo.c" \
"../Sources/siu_init.c" \
"../Sources/stm_init.c" \
"../Sources/swt_init.c" \
"../Sources/sys_init.c" \
"../Sources/sysclk_init.c" \
"../Sources/uart.c" \

C_SRCS += \
../Sources/adc_drv.c \
../Sources/adc_init.c \
../Sources/adc_trigger_init.c \
../Sources/clcd.c \
../Sources/control.c \
../Sources/dcMotor.c \
../Sources/distanceSensor.c \
../Sources/emios_init.c \
../Sources/filter.c \
../Sources/gpio_drv.c \
../Sources/intc_init.c \
../Sources/intc_pit.c \
../Sources/intc_siu.c \
../Sources/intc_sw_vecttable.c \
../Sources/lineScan.c \
../Sources/linflex_init.c \
../Sources/linflex_var.c \
../Sources/main.c \
../Sources/pit_init.c \
../Sources/rappid_utils.c \
../Sources/rchw_init.c \
../Sources/romcopy.c \
../Sources/rtc_init.c \
../Sources/servo.c \
../Sources/siu_init.c \
../Sources/stm_init.c \
../Sources/swt_init.c \
../Sources/sys_init.c \
../Sources/sysclk_init.c \
../Sources/uart.c \

S_SRCS += \
../Sources/crt0.s \
../Sources/excep_handler.s \
../Sources/rappid_func.s \
../Sources/sw_handlers.s \

S_SRCS_QUOTED += \
"../Sources/crt0.s" \
"../Sources/excep_handler.s" \
"../Sources/rappid_func.s" \
"../Sources/sw_handlers.s" \

S_DEPS_QUOTED += \
"./Sources/crt0_s.d" \
"./Sources/excep_handler_s.d" \
"./Sources/rappid_func_s.d" \
"./Sources/sw_handlers_s.d" \

OBJS += \
./Sources/adc_drv_c.obj \
./Sources/adc_init_c.obj \
./Sources/adc_trigger_init_c.obj \
./Sources/clcd_c.obj \
./Sources/control_c.obj \
./Sources/crt0_s.obj \
./Sources/dcMotor_c.obj \
./Sources/distanceSensor_c.obj \
./Sources/emios_init_c.obj \
./Sources/excep_handler_s.obj \
./Sources/filter_c.obj \
./Sources/gpio_drv_c.obj \
./Sources/intc_init_c.obj \
./Sources/intc_pit_c.obj \
./Sources/intc_siu_c.obj \
./Sources/intc_sw_vecttable_c.obj \
./Sources/lineScan_c.obj \
./Sources/linflex_init_c.obj \
./Sources/linflex_var_c.obj \
./Sources/main_c.obj \
./Sources/pit_init_c.obj \
./Sources/rappid_func_s.obj \
./Sources/rappid_utils_c.obj \
./Sources/rchw_init_c.obj \
./Sources/romcopy_c.obj \
./Sources/rtc_init_c.obj \
./Sources/servo_c.obj \
./Sources/siu_init_c.obj \
./Sources/stm_init_c.obj \
./Sources/sw_handlers_s.obj \
./Sources/swt_init_c.obj \
./Sources/sys_init_c.obj \
./Sources/sysclk_init_c.obj \
./Sources/uart_c.obj \

S_DEPS += \
./Sources/crt0_s.d \
./Sources/excep_handler_s.d \
./Sources/rappid_func_s.d \
./Sources/sw_handlers_s.d \

OBJS_QUOTED += \
"./Sources/adc_drv_c.obj" \
"./Sources/adc_init_c.obj" \
"./Sources/adc_trigger_init_c.obj" \
"./Sources/clcd_c.obj" \
"./Sources/control_c.obj" \
"./Sources/crt0_s.obj" \
"./Sources/dcMotor_c.obj" \
"./Sources/distanceSensor_c.obj" \
"./Sources/emios_init_c.obj" \
"./Sources/excep_handler_s.obj" \
"./Sources/filter_c.obj" \
"./Sources/gpio_drv_c.obj" \
"./Sources/intc_init_c.obj" \
"./Sources/intc_pit_c.obj" \
"./Sources/intc_siu_c.obj" \
"./Sources/intc_sw_vecttable_c.obj" \
"./Sources/lineScan_c.obj" \
"./Sources/linflex_init_c.obj" \
"./Sources/linflex_var_c.obj" \
"./Sources/main_c.obj" \
"./Sources/pit_init_c.obj" \
"./Sources/rappid_func_s.obj" \
"./Sources/rappid_utils_c.obj" \
"./Sources/rchw_init_c.obj" \
"./Sources/romcopy_c.obj" \
"./Sources/rtc_init_c.obj" \
"./Sources/servo_c.obj" \
"./Sources/siu_init_c.obj" \
"./Sources/stm_init_c.obj" \
"./Sources/sw_handlers_s.obj" \
"./Sources/swt_init_c.obj" \
"./Sources/sys_init_c.obj" \
"./Sources/sysclk_init_c.obj" \
"./Sources/uart_c.obj" \

C_DEPS += \
./Sources/adc_drv_c.d \
./Sources/adc_init_c.d \
./Sources/adc_trigger_init_c.d \
./Sources/clcd_c.d \
./Sources/control_c.d \
./Sources/dcMotor_c.d \
./Sources/distanceSensor_c.d \
./Sources/emios_init_c.d \
./Sources/filter_c.d \
./Sources/gpio_drv_c.d \
./Sources/intc_init_c.d \
./Sources/intc_pit_c.d \
./Sources/intc_siu_c.d \
./Sources/intc_sw_vecttable_c.d \
./Sources/lineScan_c.d \
./Sources/linflex_init_c.d \
./Sources/linflex_var_c.d \
./Sources/main_c.d \
./Sources/pit_init_c.d \
./Sources/rappid_utils_c.d \
./Sources/rchw_init_c.d \
./Sources/romcopy_c.d \
./Sources/rtc_init_c.d \
./Sources/servo_c.d \
./Sources/siu_init_c.d \
./Sources/stm_init_c.d \
./Sources/swt_init_c.d \
./Sources/sys_init_c.d \
./Sources/sysclk_init_c.d \
./Sources/uart_c.d \

OBJS_OS_FORMAT += \
./Sources/adc_drv_c.obj \
./Sources/adc_init_c.obj \
./Sources/adc_trigger_init_c.obj \
./Sources/clcd_c.obj \
./Sources/control_c.obj \
./Sources/crt0_s.obj \
./Sources/dcMotor_c.obj \
./Sources/distanceSensor_c.obj \
./Sources/emios_init_c.obj \
./Sources/excep_handler_s.obj \
./Sources/filter_c.obj \
./Sources/gpio_drv_c.obj \
./Sources/intc_init_c.obj \
./Sources/intc_pit_c.obj \
./Sources/intc_siu_c.obj \
./Sources/intc_sw_vecttable_c.obj \
./Sources/lineScan_c.obj \
./Sources/linflex_init_c.obj \
./Sources/linflex_var_c.obj \
./Sources/main_c.obj \
./Sources/pit_init_c.obj \
./Sources/rappid_func_s.obj \
./Sources/rappid_utils_c.obj \
./Sources/rchw_init_c.obj \
./Sources/romcopy_c.obj \
./Sources/rtc_init_c.obj \
./Sources/servo_c.obj \
./Sources/siu_init_c.obj \
./Sources/stm_init_c.obj \
./Sources/sw_handlers_s.obj \
./Sources/swt_init_c.obj \
./Sources/sys_init_c.obj \
./Sources/sysclk_init_c.obj \
./Sources/uart_c.obj \

C_DEPS_QUOTED += \
"./Sources/adc_drv_c.d" \
"./Sources/adc_init_c.d" \
"./Sources/adc_trigger_init_c.d" \
"./Sources/clcd_c.d" \
"./Sources/control_c.d" \
"./Sources/dcMotor_c.d" \
"./Sources/distanceSensor_c.d" \
"./Sources/emios_init_c.d" \
"./Sources/filter_c.d" \
"./Sources/gpio_drv_c.d" \
"./Sources/intc_init_c.d" \
"./Sources/intc_pit_c.d" \
"./Sources/intc_siu_c.d" \
"./Sources/intc_sw_vecttable_c.d" \
"./Sources/lineScan_c.d" \
"./Sources/linflex_init_c.d" \
"./Sources/linflex_var_c.d" \
"./Sources/main_c.d" \
"./Sources/pit_init_c.d" \
"./Sources/rappid_utils_c.d" \
"./Sources/rchw_init_c.d" \
"./Sources/romcopy_c.d" \
"./Sources/rtc_init_c.d" \
"./Sources/servo_c.d" \
"./Sources/siu_init_c.d" \
"./Sources/stm_init_c.d" \
"./Sources/swt_init_c.d" \
"./Sources/sys_init_c.d" \
"./Sources/sysclk_init_c.d" \
"./Sources/uart_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/adc_drv_c.obj: ../Sources/adc_drv.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/adc_drv.args" -o "Sources/adc_drv_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/adc_init_c.obj: ../Sources/adc_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/adc_init.args" -o "Sources/adc_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/adc_trigger_init_c.obj: ../Sources/adc_trigger_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/adc_trigger_init.args" -o "Sources/adc_trigger_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/clcd_c.obj: ../Sources/clcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/clcd.args" -o "Sources/clcd_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/control_c.obj: ../Sources/control.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/control.args" -o "Sources/control_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/crt0_s.obj: ../Sources/crt0.s
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: PowerPC Assembler'
	"$(PAToolsDirEnv)/mwasmeppc" @@"Sources/crt0.args" -o "Sources/crt0_s.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.s
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/dcMotor_c.obj: ../Sources/dcMotor.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/dcMotor.args" -o "Sources/dcMotor_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/distanceSensor_c.obj: ../Sources/distanceSensor.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/distanceSensor.args" -o "Sources/distanceSensor_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/emios_init_c.obj: ../Sources/emios_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/emios_init.args" -o "Sources/emios_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/excep_handler_s.obj: ../Sources/excep_handler.s
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC Assembler'
	"$(PAToolsDirEnv)/mwasmeppc" @@"Sources/excep_handler.args" -o "Sources/excep_handler_s.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/filter_c.obj: ../Sources/filter.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/filter.args" -o "Sources/filter_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpio_drv_c.obj: ../Sources/gpio_drv.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/gpio_drv.args" -o "Sources/gpio_drv_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/intc_init_c.obj: ../Sources/intc_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/intc_init.args" -o "Sources/intc_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/intc_pit_c.obj: ../Sources/intc_pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/intc_pit.args" -o "Sources/intc_pit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/intc_siu_c.obj: ../Sources/intc_siu.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/intc_siu.args" -o "Sources/intc_siu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/intc_sw_vecttable_c.obj: ../Sources/intc_sw_vecttable.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/intc_sw_vecttable.args" -o "Sources/intc_sw_vecttable_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/lineScan_c.obj: ../Sources/lineScan.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/lineScan.args" -o "Sources/lineScan_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/linflex_init_c.obj: ../Sources/linflex_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/linflex_init.args" -o "Sources/linflex_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/linflex_var_c.obj: ../Sources/linflex_var.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/linflex_var.args" -o "Sources/linflex_var_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pit_init_c.obj: ../Sources/pit_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/pit_init.args" -o "Sources/pit_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rappid_func_s.obj: ../Sources/rappid_func.s
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: PowerPC Assembler'
	"$(PAToolsDirEnv)/mwasmeppc" @@"Sources/rappid_func.args" -o "Sources/rappid_func_s.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rappid_utils_c.obj: ../Sources/rappid_utils.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/rappid_utils.args" -o "Sources/rappid_utils_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rchw_init_c.obj: ../Sources/rchw_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/rchw_init.args" -o "Sources/rchw_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/romcopy_c.obj: ../Sources/romcopy.c
	@echo 'Building file: $<'
	@echo 'Executing target #25 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/romcopy.args" -o "Sources/romcopy_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rtc_init_c.obj: ../Sources/rtc_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #26 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/rtc_init.args" -o "Sources/rtc_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/servo_c.obj: ../Sources/servo.c
	@echo 'Building file: $<'
	@echo 'Executing target #27 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/servo.args" -o "Sources/servo_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/siu_init_c.obj: ../Sources/siu_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #28 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/siu_init.args" -o "Sources/siu_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/stm_init_c.obj: ../Sources/stm_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #29 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/stm_init.args" -o "Sources/stm_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sw_handlers_s.obj: ../Sources/sw_handlers.s
	@echo 'Building file: $<'
	@echo 'Executing target #30 $<'
	@echo 'Invoking: PowerPC Assembler'
	"$(PAToolsDirEnv)/mwasmeppc" @@"Sources/sw_handlers.args" -o "Sources/sw_handlers_s.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/swt_init_c.obj: ../Sources/swt_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #31 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/swt_init.args" -o "Sources/swt_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sys_init_c.obj: ../Sources/sys_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #32 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/sys_init.args" -o "Sources/sys_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/sysclk_init_c.obj: ../Sources/sysclk_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #33 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/sysclk_init.args" -o "Sources/sysclk_init_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_c.obj: ../Sources/uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/uart.args" -o "Sources/uart_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


