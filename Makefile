
ZMK_DIR := $(CURDIR)/../zmk
ZMK_APP := $(ZMK_DIR)/app
SHIELD_NAME := braille
RAW_BOARD_MOUNTPOINT := /media/tvollert/NICENANO
export PATH := $(ZMK_DIR)/venv/bin:$(PATH)
WEST_PARAMS := ""
BOOTLOADER_NAME := Adafruit nRF UF2

.DEFAULT: all

.PHONY: compile_app copy_zmk clean

all: compile_app copy_zmk

verify-zmk:
	@ls $(ZMK_APP) >/dev/null 2>&1 || ( echo "Expected zmk code at $(ZMK_APP), but didn't find anything" && exit 1 )	

compile_app: verify-zmk
	@echo "===> Compiling app $(WEST_PARAMS)"
	@cd $(ZMK_APP) && west build $(WEST_PARAMS) -p  -b nice_nano -DSHIELD=braille -DZMK_EXTRA_MODULES="$(CURDIR)/"

clean:
	@echo "===> Deleting build directory"
	rm -rf $(ZMK_APP)/build

mount_board:
	@echo "Please reset the board into bootloader mode"
	@while [ -z "$$(udisksctl status | grep '$(BOOTLOADER_NAME)' | awk '{print $$NF}')" ]; do sleep 0.5; done
	@echo "===> Trying to mount the board"
	@udisksctl mount -b /dev/$$(udisksctl status | grep '$(BOOTLOADER_NAME)' | awk '{print $$NF}')

copy_zmk: verify-zmk mount_board
	@echo "===> Copying UF2 file to $(RAW_BOARD_MOUNTPOINT)"
	cp $(ZMK_APP)/build/zephyr/zmk.uf2 $(RAW_BOARD_MOUNTPOINT)/

follow:
	tio --baudrate 115200 /dev/ttyACM0
