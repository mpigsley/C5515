################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
aic3204_loop_stereo_in1.obj: ../aic3204_loop_stereo_in1.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -vcpu:3.3 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="E:/Apps/Texas Instruments/ccsv5/ccs_base/emulation/boards/usbstk5515_v1/include" --define=c5515 --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="aic3204_loop_stereo_in1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_test.obj: ../aic3204_test.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -vcpu:3.3 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="E:/Apps/Texas Instruments/ccsv5/ccs_base/emulation/boards/usbstk5515_v1/include" --define=c5515 --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="aic3204_test.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

aic3204_tone_headphone.obj: ../aic3204_tone_headphone.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -vcpu:3.3 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="E:/Apps/Texas Instruments/ccsv5/ccs_base/emulation/boards/usbstk5515_v1/include" --define=c5515 --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="aic3204_tone_headphone.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -vcpu:3.3 --memory_model=large -g --include_path="E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="E:/Apps/Texas Instruments/ccsv5/ccs_base/emulation/boards/usbstk5515_v1/include" --define=c5515 --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


