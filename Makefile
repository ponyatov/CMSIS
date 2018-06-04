F0_CFLAGS   = -march=armv6-m -mcpu=cortex-m0     -mthumb -D STM32F051x8
L0_CFLAGS   = -march=armv6-m -mcpu=cortex-m0plus -mthumb -D STM32L073xx

MCU_CFLAGS = $(F0_CFLAGS)
#MCU_CFLAGS = $(L0_CFLAGS)

MCU_LDSCRIPT = STM32F051R8_FLASH
#MCU_LDSCRIPT = STM32L073VZTx_FLASH

TARGET = arm-none-eabi

CC		= $(TARGET)-gcc
GDB		= $(TARGET)-gdb
OBJDUMP	= $(TARGET)-objdump
AR		= $(TARGET)-ar

CFLAGS	+= -Os -g -ffunction-sections -fdata-sections
CFLAGS	+= -I$(CURDIR)/include/STM32 -I$(CURDIR)/src
LDFLAGS	+= -Wl,--gc-sections -Wl,-T,lib/$(MCU_LDSCRIPT).ld -L$(CURDIR)/lib

LIB += lib/libSTM32F0.a

OBJ	+= tmp/startup_stm32f051x8.o tmp/system_stm32f0xx.o
OBJ	+= tmp/startup_stm32l073xx.o tmp/system_stm32l0xx.o
OBJ	+= tmp/stm32f0xx_hal.o
OBJ	+= tmp/stm32f0xx_hal_cortex.o
OBJ	+= tmp/stm32f0xx_hal_flash.o
OBJ	+= tmp/stm32f0xx_hal_flash_ex.o
OBJ += tmp/stm32f0xx_hal_rcc.o
OBJ += tmp/stm32f0xx_hal_gpio.o

S	+= src/STM32/startup_stm32f051x8.s	src/STM32/startup_stm32l073xx.s
C	+= src/STM32/system_stm32f0xx.c		src/STM32/system_stm32l0xx.c

H	+= include/STM32/system_stm32f0xx.h	include/STM32/system_stm32l0xx.h
H	+= include/STM32/stm32f0xx.h		include/STM32/stm32l0xx.h

H	+= include/STM32/stm32f051x8.h		include/STM32/stm32l073xx.h

H	+= include/STM32/core_cm0.h			include/STM32/core_cm0plus.h
H	+= include/STM32/cmsis_gcc.h
H	+= include/STM32/core_cmInstr.h include/STM32/core_cmFunc.h

H	+= src/stm32f0xx_hal_conf.h
H	+= include/STM32/stm32f0xx_hal.h
C	+= src/STM32/stm32f0xx_hal.c
H	+= include/STM32/stm32f0xx_hal_def.h
H	+= include/STM32/stm32f0xx_hal_cortex.h
C	+= src/STM32/stm32f0xx_hal_cortex.c
H	+= include/STM32/stm32f0xx_hal_flash.h
H	+= include/STM32/stm32f0xx_hal_flash_ex.h
C	+= src/STM32/stm32f0xx_hal_flash.c
C	+= src/STM32/stm32f0xx_hal_flash_ex.c

H	+= include/STM32/stm32f0xx_hal_rcc.h
H	+= include/STM32/stm32f0xx_hal_rcc_ex.h
C	+= src/STM32/stm32f0xx_hal_rcc.c

H	+= include/STM32/stm32f0xx_hal_gpio.h
H	+= include/STM32/stm32f0xx_hal_gpio_ex.h
C	+= src/STM32/stm32f0xx_hal_gpio.c

LDS	+= lib/STM32L073VZTx_FLASH.ld lib/STM32F051R8_FLASH.ld

SRC += $(S) $(C) $(H) $(LDS)

all: f0disco_demo.elf

deb: f0disco_demo.elf
	st-util&
	ddd ddd --debugger "$(GDB) -x lib/$(MCU_LDSCRIPT).gdb $<"

f0disco_demo.elf: src/f0disco_demo.c $(H) $(LIB) lib/$(MCU_LDSCRIPT).ld Makefile
	$(CC) $(CFLAGS) $(MCU_CFLAGS) -o $@ \
		$(LDFLAGS) -Wl,-Map=$@.map \
			$< -lSTM32F0
	$(OBJDUMP) -x $@ > $@.objdump

lib: $(LIB)
lib/libSTM32F0.a:
	$(AR) crs $@ tmp/*stm32f0*.o	

$(LIB): $(OBJ)

$(OBJ): $(SRC)

src: $(SRC)

clean:
	rm -f lib/*.o lib/*.a

F0CUBE	= STM32/STM32Cube_FW_F0_V1.9.0
L0CUBE	= STM32/STM32Cube_FW_L0_V1.10.0
F0CMSIS = $(F0CUBE)/Drivers/CMSIS/Device/ST/STM32F0xx
L0CMSIS = $(L0CUBE)/Drivers/CMSIS/Device/ST/STM32L0xx
F0TMPL  = $(F0CMSIS)/Source/Templates
L0TMPL  = $(L0CMSIS)/Source/Templates
F0INCL	= $(F0CMSIS)/Include
L0INCL	= $(L0CMSIS)/Include
CMINCL	= $(L0CUBE)/Drivers/CMSIS/Include
F0PRJ	= $(F0CUBE)/Projects/STM32F070RB-Nucleo/Templates_LL
L0PRJ	= $(L0CUBE)/Projects/STM32L073Z_EVAL/Templates_LL

F0HAL	= $(F0CUBE)/Drivers/STM32F0xx_HAL_Driver

#DISCO	= STM32/STM32F0-Discovery_FW_V1.0.0/Project/Demonstration/TrueSTUDIO/STM32F0-Discovery_Demo

lib/%.ld: $(L0PRJ)/SW4STM32/STM32L073Z_EVAL/%.ld
	cp $< $@
lib/STM32F051R8_FLASH.ld:
	cp $(F0PRJ)/SW4STM32/STM32F070RB-Nucleo/STM32F070RBTx_FLASH.ld $@

src/STM32/%.s: $(F0TMPL)/gcc/%.s
	cp $< $@
src/STM32/%.s: $(L0TMPL)/gcc/%.s
	cp $< $@

src/STM32/%.c: $(F0TMPL)/%.c
	cp $< $@
src/STM32/%.c: $(L0TMPL)/%.c
	cp $< $@
src/STM32/%.c: $(F0HAL)/Src/%.c
	cp $< $@
	
include/STM32/%.h: $(F0INCL)/%.h
	cp $< $@
include/STM32/%.h: $(L0INCL)/%.h
	cp $< $@
include/STM32/%.h: $(CMINCL)/%.h
	cp $< $@
include/STM32/%.h: $(F0HAL)/Inc/%.h
	cp $< $@


tmp/system_stm32f0xx.o: src/STM32/system_stm32f0xx.c Makefile
	$(CC) $(CFLAGS) $(F0_CFLAGS) -c -o $@ $<
tmp/system_stm32l0xx.o: src/STM32/system_stm32l0xx.c Makefile
	$(CC) $(CFLAGS) $(L0_CFLAGS) -c -o $@ $<
	
tmp/startup_stm32f051x8.o: src/STM32/startup_stm32f051x8.s Makefile
	$(CC) $(CFLAGS) $(F0_CFLAGS) -c -o $@ $<
tmp/startup_stm32l073xx.o: src/STM32/startup_stm32l073xx.s Makefile
	$(CC) $(CFLAGS) $(L0_CFLAGS) -c -o $@ $<
	
tmp/%.o: src/STM32/%.c Makefile 
	$(CC) $(CFLAGS) $(F0_CFLAGS) -c -o $@ $<
tmp/%.o: src/STM32/%.s Makefile
	$(CC) $(CFLAGS) $(F0_CFLAGS) -c -o $@ $<

doxy:
	doxygen doxy.gen >/dev/null 
#	2>doxy.log
#	cat doxy.log | egrep -v "STM32F0_DISCOVERY_LOW_LEVEL_LED" 
