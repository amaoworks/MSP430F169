################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/Learn/CCS/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="D:/Learn/CCS/ccsv8/ccs_base/msp430/include" --include_path="E:/Learn/Workspace/motor" --include_path="D:/Learn/CCS/ccsv8/tools/compiler/ti-cgt-msp430_18.1.3.LTS/include" --advice:power=all --define=__MSP430F169__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


