################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lvgl/src/hal/%.o: ../lvgl/src/hal/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2030/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c -mcpu=cortex-m33 -mfloat-abi=soft -mfpu=none -mlittle-endian -O2 -I"C:/Users/bsposci/workspace_ccstheia/crcp_calculate_checksum_LP_MSPM33C321A_nortos_ticlang" -I"C:/Users/bsposci/workspace_ccstheia/crcp_calculate_checksum_LP_MSPM33C321A_nortos_ticlang/Debug" -I"C:/ti/mspm33_sdk_1_00_00_00_internal/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm33_sdk_1_00_00_00_internal/source" -D__MSPM33C321A__ -gdwarf-3 -fcoverage-mapping -fprofile-instr-generate -MMD -MP -MF"lvgl/src/hal/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


