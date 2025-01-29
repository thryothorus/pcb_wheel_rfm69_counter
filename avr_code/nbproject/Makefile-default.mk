#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/avr_code.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/avr_code.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=uart.c rfm69.c states.c i2c.c m95128.c spi.c st25dv.c interrupts.c max31329.c power_mgmt.c adc.c ndef.c main.c defines.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/uart.o ${OBJECTDIR}/rfm69.o ${OBJECTDIR}/states.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/m95128.o ${OBJECTDIR}/spi.o ${OBJECTDIR}/st25dv.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/max31329.o ${OBJECTDIR}/power_mgmt.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/ndef.o ${OBJECTDIR}/main.o ${OBJECTDIR}/defines.o
POSSIBLE_DEPFILES=${OBJECTDIR}/uart.o.d ${OBJECTDIR}/rfm69.o.d ${OBJECTDIR}/states.o.d ${OBJECTDIR}/i2c.o.d ${OBJECTDIR}/m95128.o.d ${OBJECTDIR}/spi.o.d ${OBJECTDIR}/st25dv.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/max31329.o.d ${OBJECTDIR}/power_mgmt.o.d ${OBJECTDIR}/adc.o.d ${OBJECTDIR}/ndef.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/defines.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/uart.o ${OBJECTDIR}/rfm69.o ${OBJECTDIR}/states.o ${OBJECTDIR}/i2c.o ${OBJECTDIR}/m95128.o ${OBJECTDIR}/spi.o ${OBJECTDIR}/st25dv.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/max31329.o ${OBJECTDIR}/power_mgmt.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/ndef.o ${OBJECTDIR}/main.o ${OBJECTDIR}/defines.o

# Source Files
SOURCEFILES=uart.c rfm69.c states.c i2c.c m95128.c spi.c st25dv.c interrupts.c max31329.c power_mgmt.c adc.c ndef.c main.c defines.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega328pb"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/avr_code.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega328PB
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/6d953eb08730830c29583887e0311c3a3744f6ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o  -o ${OBJECTDIR}/uart.o uart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/rfm69.o: rfm69.c  .generated_files/flags/default/2b04d7b5140a59298188b5f74990c092a4a3178e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/rfm69.o.d 
	@${RM} ${OBJECTDIR}/rfm69.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/rfm69.o.d" -MT "${OBJECTDIR}/rfm69.o.d" -MT ${OBJECTDIR}/rfm69.o  -o ${OBJECTDIR}/rfm69.o rfm69.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/states.o: states.c  .generated_files/flags/default/85ef27698a16f8dbaa95e2f550bb9dbec047e7a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/states.o.d 
	@${RM} ${OBJECTDIR}/states.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/states.o.d" -MT "${OBJECTDIR}/states.o.d" -MT ${OBJECTDIR}/states.o  -o ${OBJECTDIR}/states.o states.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/i2c.o: i2c.c  .generated_files/flags/default/5d818c96cd4ed1e5aa84bd65378612fa3c8719cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${RM} ${OBJECTDIR}/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/i2c.o.d" -MT "${OBJECTDIR}/i2c.o.d" -MT ${OBJECTDIR}/i2c.o  -o ${OBJECTDIR}/i2c.o i2c.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/m95128.o: m95128.c  .generated_files/flags/default/aa3983fdf481825a2d256588b7a3c021e931c6b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/m95128.o.d 
	@${RM} ${OBJECTDIR}/m95128.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/m95128.o.d" -MT "${OBJECTDIR}/m95128.o.d" -MT ${OBJECTDIR}/m95128.o  -o ${OBJECTDIR}/m95128.o m95128.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/spi.o: spi.c  .generated_files/flags/default/f503b0baf348934e512fc807a41741b2cac43aa7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi.o.d 
	@${RM} ${OBJECTDIR}/spi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/spi.o.d" -MT "${OBJECTDIR}/spi.o.d" -MT ${OBJECTDIR}/spi.o  -o ${OBJECTDIR}/spi.o spi.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/st25dv.o: st25dv.c  .generated_files/flags/default/7934eed80f29f2405f97b92de1bae6a6c36a679b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/st25dv.o.d 
	@${RM} ${OBJECTDIR}/st25dv.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/st25dv.o.d" -MT "${OBJECTDIR}/st25dv.o.d" -MT ${OBJECTDIR}/st25dv.o  -o ${OBJECTDIR}/st25dv.o st25dv.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/interrupts.o: interrupts.c  .generated_files/flags/default/5377237f5a02dc5b708c20478cbf4fcc8fd13474 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/interrupts.o.d" -MT "${OBJECTDIR}/interrupts.o.d" -MT ${OBJECTDIR}/interrupts.o  -o ${OBJECTDIR}/interrupts.o interrupts.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/max31329.o: max31329.c  .generated_files/flags/default/869b6e2362ba0e02bcf96cb618c5742866db800d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/max31329.o.d 
	@${RM} ${OBJECTDIR}/max31329.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/max31329.o.d" -MT "${OBJECTDIR}/max31329.o.d" -MT ${OBJECTDIR}/max31329.o  -o ${OBJECTDIR}/max31329.o max31329.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/power_mgmt.o: power_mgmt.c  .generated_files/flags/default/c47296ab30a1b51f73798e7e6ea8b2f3df739782 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/power_mgmt.o.d 
	@${RM} ${OBJECTDIR}/power_mgmt.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/power_mgmt.o.d" -MT "${OBJECTDIR}/power_mgmt.o.d" -MT ${OBJECTDIR}/power_mgmt.o  -o ${OBJECTDIR}/power_mgmt.o power_mgmt.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/9bd62e73b2ca088d50e4fde2916120f0d9f4a145 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/adc.o.d" -MT "${OBJECTDIR}/adc.o.d" -MT ${OBJECTDIR}/adc.o  -o ${OBJECTDIR}/adc.o adc.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/ndef.o: ndef.c  .generated_files/flags/default/6218f7828f7f6c3b2cf0d222d75a332b53769111 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ndef.o.d 
	@${RM} ${OBJECTDIR}/ndef.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/ndef.o.d" -MT "${OBJECTDIR}/ndef.o.d" -MT ${OBJECTDIR}/ndef.o  -o ${OBJECTDIR}/ndef.o ndef.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/97ef2eba5631977dd0051f2cb26ad26adebde0ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o  -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/defines.o: defines.c  .generated_files/flags/default/f1d409d8769607bf30e7a803b35da4b781cb824 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/defines.o.d 
	@${RM} ${OBJECTDIR}/defines.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/defines.o.d" -MT "${OBJECTDIR}/defines.o.d" -MT ${OBJECTDIR}/defines.o  -o ${OBJECTDIR}/defines.o defines.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/70124900b376e0f2b64974c67225ec9813a6f146 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/uart.o.d" -MT "${OBJECTDIR}/uart.o.d" -MT ${OBJECTDIR}/uart.o  -o ${OBJECTDIR}/uart.o uart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/rfm69.o: rfm69.c  .generated_files/flags/default/8ab9009e5d4fe0365c4292ebb95c72557b2681a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/rfm69.o.d 
	@${RM} ${OBJECTDIR}/rfm69.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/rfm69.o.d" -MT "${OBJECTDIR}/rfm69.o.d" -MT ${OBJECTDIR}/rfm69.o  -o ${OBJECTDIR}/rfm69.o rfm69.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/states.o: states.c  .generated_files/flags/default/e4af7ab35e0272ad00bebd28ef0e9c8ce93f508d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/states.o.d 
	@${RM} ${OBJECTDIR}/states.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/states.o.d" -MT "${OBJECTDIR}/states.o.d" -MT ${OBJECTDIR}/states.o  -o ${OBJECTDIR}/states.o states.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/i2c.o: i2c.c  .generated_files/flags/default/af0ca0dea4f972cfc619b71f7fa4add200a64720 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c.o.d 
	@${RM} ${OBJECTDIR}/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/i2c.o.d" -MT "${OBJECTDIR}/i2c.o.d" -MT ${OBJECTDIR}/i2c.o  -o ${OBJECTDIR}/i2c.o i2c.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/m95128.o: m95128.c  .generated_files/flags/default/68f6dd3212895fdd4381b690bd8ac7df744c4a8b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/m95128.o.d 
	@${RM} ${OBJECTDIR}/m95128.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/m95128.o.d" -MT "${OBJECTDIR}/m95128.o.d" -MT ${OBJECTDIR}/m95128.o  -o ${OBJECTDIR}/m95128.o m95128.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/spi.o: spi.c  .generated_files/flags/default/cfd86ac76e47bc98eb08131adf966714b7cee476 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi.o.d 
	@${RM} ${OBJECTDIR}/spi.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/spi.o.d" -MT "${OBJECTDIR}/spi.o.d" -MT ${OBJECTDIR}/spi.o  -o ${OBJECTDIR}/spi.o spi.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/st25dv.o: st25dv.c  .generated_files/flags/default/9d2d9295ac6327e786226b2ff0a5222b0b8bced3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/st25dv.o.d 
	@${RM} ${OBJECTDIR}/st25dv.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/st25dv.o.d" -MT "${OBJECTDIR}/st25dv.o.d" -MT ${OBJECTDIR}/st25dv.o  -o ${OBJECTDIR}/st25dv.o st25dv.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/interrupts.o: interrupts.c  .generated_files/flags/default/87d7563e54700a74f12a41484718e5daed85f111 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/interrupts.o.d" -MT "${OBJECTDIR}/interrupts.o.d" -MT ${OBJECTDIR}/interrupts.o  -o ${OBJECTDIR}/interrupts.o interrupts.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/max31329.o: max31329.c  .generated_files/flags/default/e74969be3e1d09732fd8832be03d84af0bb392ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/max31329.o.d 
	@${RM} ${OBJECTDIR}/max31329.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/max31329.o.d" -MT "${OBJECTDIR}/max31329.o.d" -MT ${OBJECTDIR}/max31329.o  -o ${OBJECTDIR}/max31329.o max31329.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/power_mgmt.o: power_mgmt.c  .generated_files/flags/default/83a7cd9c55768611a75cc6a19d79cb4a96a36e7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/power_mgmt.o.d 
	@${RM} ${OBJECTDIR}/power_mgmt.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/power_mgmt.o.d" -MT "${OBJECTDIR}/power_mgmt.o.d" -MT ${OBJECTDIR}/power_mgmt.o  -o ${OBJECTDIR}/power_mgmt.o power_mgmt.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/adc.o: adc.c  .generated_files/flags/default/7a5bebcb697ed27ebc4e37c3fe6e1b077ffd758e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${RM} ${OBJECTDIR}/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/adc.o.d" -MT "${OBJECTDIR}/adc.o.d" -MT ${OBJECTDIR}/adc.o  -o ${OBJECTDIR}/adc.o adc.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/ndef.o: ndef.c  .generated_files/flags/default/6b4a836459f9efcbee291c20b053a722b4ee1d51 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ndef.o.d 
	@${RM} ${OBJECTDIR}/ndef.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/ndef.o.d" -MT "${OBJECTDIR}/ndef.o.d" -MT ${OBJECTDIR}/ndef.o  -o ${OBJECTDIR}/ndef.o ndef.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/ce30b016f919bd5068c1926609b0990dd6c95215 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/main.o.d" -MT "${OBJECTDIR}/main.o.d" -MT ${OBJECTDIR}/main.o  -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/defines.o: defines.c  .generated_files/flags/default/fbf3e8d04a69bbd24b54d5cee7326db97246cad9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/defines.o.d 
	@${RM} ${OBJECTDIR}/defines.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega328pb ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/defines.o.d" -MT "${OBJECTDIR}/defines.o.d" -MT ${OBJECTDIR}/defines.o  -o ${OBJECTDIR}/defines.o defines.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/avr_code.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega328pb ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/avr_code.${IMAGE_TYPE}.map"    -o ${DISTDIR}/avr_code.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/avr_code.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega328pb ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}/avr_code.${IMAGE_TYPE}.map"    -o ${DISTDIR}/avr_code.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "${DISTDIR}/avr_code.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/avr_code.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
