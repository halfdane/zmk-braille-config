ZMK_APP := $(CURDIR)/zmk/app
SHIELD_NAME := braille
RAW_BOARD_MOUNTPOINT := /media/$(USER)/NICENANO
BOOTLOADER_NAME := Adafruit nRF UF2
BUILD := build

# check if zephyr has already been cloned - use their requirements.txt.
# if not, use our own as fallback - it's just to install `west`
ifeq ($(wildcard zephyr/scripts/requirements.txt),) 
	REQUIREMENTS_TXT = requirements.txt
else 
	REQUIREMENTS_TXT = zephyr/scripts/requirements.txt
endif

.DEFAULT: all

.PHONY: all update setup verify-zmk compile_app copy_zmk clean deep_clean mount_board follow

all: compile_app copy_zmk

west_init: .west
.west: venv
	@echo "===> Initializing west"
	@$(VENV)/west init -l config

west_update: west_init venv
	$(VENV)/west update
	$(VENV)/west zephyr-export

west_setup: venv west_init west_update

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
	rm -rf zmk-behavior-haptic-feedback


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