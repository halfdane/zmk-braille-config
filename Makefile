
ZMK_DIR := $(CURDIR)/zmk
ZMK_APP := $(ZMK_DIR)/app
SHIELD_NAME := braille
RAW_BOARD_MOUNTPOINT := /media/tvollert/NICENANO
BOOTLOADER_NAME := Adafruit nRF UF2
BUILD := build

ifeq ($(wildcard zephyr/scripts/requirements.txt),) 
	REQUIREMENTS_TXT = requirements.txt
else 
	REQUIREMENTS_TXT = zephyr/scripts/requirements.txt
endif

.DEFAULT: all

.PHONY: compile_app copy_zmk clean

all: compile_app copy_zmk

init: .west
.west:
	@echo "===> Initializing west"
	@west init -l config

update: init
	$(VENV)/west update
	$(VENV)/west zephyr-export

setup: venv init update

verify-zmk:
	@ls $(ZMK_APP) >/dev/null 2>&1 || ( echo "Expected zmk code at $(ZMK_APP), but didn't find anything" && exit 1 )	

compile_app: verify-zmk venv
	@echo "===> Compiling app"
	@$(VENV)/west build -p -s $(ZMK_APP) -b "nice_nano" -- -DSHIELD="braille" -DZMK_CONFIG="$(CURDIR)/config"

clean:
	@echo "===> Deleting build directory $(BUILD)"
	rm -rf $(BUILD)

deep_clean: clean clean-venv
	rm -rf zmk
	rm -rf zephyr
	rm -rf .west
	rm -rf modules


mount_board:
	@echo "Please reset the board into bootloader mode"
	@while [ -z "$$(udisksctl status | grep '$(BOOTLOADER_NAME)' | awk '{print $$NF}')" ]; do sleep 0.5; done
	@echo "===> Trying to mount the board"
	@udisksctl mount -b /dev/$$(udisksctl status | grep '$(BOOTLOADER_NAME)' | awk '{print $$NF}')

copy_zmk: verify-zmk mount_board
	@echo "===> Copying UF2 file to $(RAW_BOARD_MOUNTPOINT)"
	cp $(BUILD)/zephyr/zmk.uf2 $(RAW_BOARD_MOUNTPOINT)/

follow:
	tio --baudrate 115200 /dev/ttyACM0



include Makefile.venv