################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./userInterface.obj" \
"./tskcfg_c.obj" \
"./tskcfg.obj" \
"./main.obj" \
"./i2s.obj" \
"./fir_filter.obj" \
"./fir2.obj" \
"./dma.obj" \
"./audio.obj" \
"./aic3204.obj" \
"../include/usbstk5515bsl.lib" \
-l"usbstk5515bsl.lib" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include include/subdir_vars.mk
-include subdir_rules.mk
-include include/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: bios_proj3.out

# Tool invocations
bios_proj3.out: $(OBJS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -g --define=c5515 --display_error_number --diag_warning=225 --ptrdiff_size=16 -z -m"bios_proj3.map" --stack_size=0x200 --heap_size=0x400 -i"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/lib" -i"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/lib" -i"E:/Apps/Texas Instruments/ccsv5/tools/compiler/c5500_4.4.1/include" -i"E:/Apps/Texas Instruments/ccsv5/ccs_base/emulation/boards/usbstk5515_v1/lib" -i"E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/rtdx/lib/c5500" -i"E:/Apps/Texas Instruments/bios_5_42_01_09/packages/ti/bios/lib" --reread_libs --display_error_number --warn_sections --xml_link_info="bios_proj3_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "bios_proj3.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_HDRS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(GEN_CMDS__QUOTED) "bios_proj3.out"
	-$(RM) "aic3204.pp" "audio.pp" "dma.pp" "fir_filter.pp" "i2s.pp" "main.pp" "tskcfg_c.pp" "userInterface.pp" 
	-$(RM) "tskcfg.pp" 
	-$(RM) "aic3204.obj" "audio.obj" "dma.obj" "fir2.obj" "fir_filter.obj" "i2s.obj" "main.obj" "tskcfg.obj" "tskcfg_c.obj" "userInterface.obj" 
	-$(RM) "fir2.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

