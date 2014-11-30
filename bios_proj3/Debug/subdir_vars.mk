################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
TCF_SRCS += \
../tsk.tcf 

ASM_SRCS += \
../fir2.asm 

S??_SRCS += \
./tskcfg.s?? 

C_SRCS += \
../aic3204.c \
../audio.c \
../dma.c \
../fir_filter.c \
../i2s.c \
../main.c \
./tskcfg_c.c \
../userInterface.c 

OBJS += \
./aic3204.obj \
./audio.obj \
./dma.obj \
./fir2.obj \
./fir_filter.obj \
./i2s.obj \
./main.obj \
./tskcfg.obj \
./tskcfg_c.obj \
./userInterface.obj 

GEN_MISC_FILES += \
./tsk.cdb 

ASM_DEPS += \
./fir2.pp 

GEN_HDRS += \
./tskcfg.h \
./tskcfg.h?? 

S??_DEPS += \
./tskcfg.pp 

C_DEPS += \
./aic3204.pp \
./audio.pp \
./dma.pp \
./fir_filter.pp \
./i2s.pp \
./main.pp \
./tskcfg_c.pp \
./userInterface.pp 

GEN_CMDS += \
./tskcfg.cmd 

GEN_FILES += \
./tskcfg.cmd \
./tskcfg.s?? \
./tskcfg_c.c 

GEN_HDRS__QUOTED += \
"tskcfg.h" \
"tskcfg.h??" 

GEN_MISC_FILES__QUOTED += \
"tsk.cdb" 

GEN_FILES__QUOTED += \
"tskcfg.cmd" \
"tskcfg.s??" \
"tskcfg_c.c" 

C_DEPS__QUOTED += \
"aic3204.pp" \
"audio.pp" \
"dma.pp" \
"fir_filter.pp" \
"i2s.pp" \
"main.pp" \
"tskcfg_c.pp" \
"userInterface.pp" 

S??_DEPS__QUOTED += \
"tskcfg.pp" 

OBJS__QUOTED += \
"aic3204.obj" \
"audio.obj" \
"dma.obj" \
"fir2.obj" \
"fir_filter.obj" \
"i2s.obj" \
"main.obj" \
"tskcfg.obj" \
"tskcfg_c.obj" \
"userInterface.obj" 

ASM_DEPS__QUOTED += \
"fir2.pp" 

C_SRCS__QUOTED += \
"../aic3204.c" \
"../audio.c" \
"../dma.c" \
"../fir_filter.c" \
"../i2s.c" \
"../main.c" \
"./tskcfg_c.c" \
"../userInterface.c" 

ASM_SRCS__QUOTED += \
"../fir2.asm" 

GEN_CMDS__FLAG += \
-l"./tskcfg.cmd" 

S??_SRCS__QUOTED += \
"./tskcfg.s??" 

S??_OBJS__QUOTED += \
"tskcfg.obj" 


