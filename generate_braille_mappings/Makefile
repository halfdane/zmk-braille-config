ZMK_APP := $(CURDIR)/zmk/app
SHIELD_NAME := braille
RAW_BOARD_MOUNTPOINT := /media/$(USER)/NICENANO
BOOTLOADER_NAME := Adafruit nRF UF2
BUILD := build

.DEFAULT: all

.PHONY: all 

all: venv
	$(VENV)/python3 read.py
	
clean: clean-venv
	@echo "===> Deleting build directory $(BUILD)"
	rm -rf $(BUILD)

include Makefile.venv