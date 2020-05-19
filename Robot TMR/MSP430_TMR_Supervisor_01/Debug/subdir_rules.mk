################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC12.obj: D:/CCS_Workspace/MSP430/F149/ADC12.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp -g -O0 --define=__MSP430F149__ --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430/F149" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430_TMR_Supervisor_01" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="ADC12.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

BCM.obj: D:/CCS_Workspace/MSP430/F149/BCM.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp -g -O0 --define=__MSP430F149__ --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430/F149" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430_TMR_Supervisor_01" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="BCM.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMR0_A3.obj: D:/CCS_Workspace/MSP430/F149/TMR0_A3.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp -g -O0 --define=__MSP430F149__ --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430/F149" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430_TMR_Supervisor_01" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="TMR0_A3.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TMR0_B7.obj: D:/CCS_Workspace/MSP430/F149/TMR0_B7.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp -g -O0 --define=__MSP430F149__ --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430/F149" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430_TMR_Supervisor_01" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="TMR0_B7.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

WDT.obj: D:/CCS_Workspace/MSP430/F149/WDT.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp -g -O0 --define=__MSP430F149__ --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430/F149" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430_TMR_Supervisor_01" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="WDT.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/bin/cl430" -vmsp -g -O0 --define=__MSP430F149__ --include_path="C:/TexasInstruments/CCS10/ccs/ccs_base/msp430/include" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430/F149" --include_path="c:/Users/pivov/_dev/NMS/Robot TMR/MSP430_TMR_Supervisor_01" --include_path="C:/TexasInstruments/CCS10/ccs/tools/compiler/ti-cgt-msp430_20.2.0.LTS/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


