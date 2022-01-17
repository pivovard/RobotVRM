################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC12.obj: C:/Users/pivov/_dev/_work/MSP430/F149/ADC12.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="C:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/Users/pivov/_dev/_work/RobotVRM" --include_path="c:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --advice:power=all --define=__MSP430F149__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

BCM.obj: C:/Users/pivov/_dev/_work/MSP430/F149/BCM.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="C:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/Users/pivov/_dev/_work/RobotVRM" --include_path="c:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --advice:power=all --define=__MSP430F149__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMR0_A3.obj: C:/Users/pivov/_dev/_work/MSP430/F149/TMR0_A3.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="C:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/Users/pivov/_dev/_work/RobotVRM" --include_path="c:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --advice:power=all --define=__MSP430F149__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMR0_B7.obj: C:/Users/pivov/_dev/_work/MSP430/F149/TMR0_B7.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="C:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/Users/pivov/_dev/_work/RobotVRM" --include_path="c:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --advice:power=all --define=__MSP430F149__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="C:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/Users/pivov/_dev/_work/RobotVRM" --include_path="c:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --advice:power=all --define=__MSP430F149__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

WDT.obj: C:/Users/pivov/_dev/_work/MSP430/F149/WDT.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp --use_hw_mpy=16 --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="C:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/Users/pivov/_dev/_work/RobotVRM" --include_path="c:/Users/pivov/_dev/_work/MSP430/F149" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --advice:power=all --define=__MSP430F149__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


