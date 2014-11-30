################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
aic3204.obj: ../aic3204.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="aic3204.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

bit_crusher.obj: ../bit_crusher.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="bit_crusher.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

dma.obj: ../dma.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="dma.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fir2.obj: ../fir2.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="fir2.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fir_filter.obj: ../fir_filter.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="fir_filter.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2s.obj: ../i2s.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="i2s.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tskcfg.cmd: ../tsk.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf'
	"E:/Apps/Texas Instruments/bios_5_42_01_09/xdctools/tconf" -b -Dconfig.importPath="E:/Apps/Texas Instruments/bios_5_42_01_09/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tskcfg.s??: | tskcfg.cmd
tskcfg_c.c: | tskcfg.cmd
tskcfg.h: | tskcfg.cmd
tskcfg.h??: | tskcfg.cmd
tsk.cdb: | tskcfg.cmd

tskcfg.obj: ./tskcfg.s?? $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="tskcfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tskcfg_c.obj: ./tskcfg_c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="tskcfg_c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

userInterface.obj: ../userInterface.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="G:/General Files/Code Composer Workspace/bios_bit_crusher/Debug" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/include" --include_path="E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/include/c5500" --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="userInterface.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


