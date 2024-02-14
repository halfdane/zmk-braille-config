
ZMK_DIR := $(CURDIR)/../zmk
ZMK_APP := $(ZMK_DIR)/app
SHIELD_NAME := braille
RAW_BOARD_MOUNTPOINT := /media/tvollert/NICENANO
export PATH := $(ZMK_DIR)/venv/bin:$(PATH)
WEST_PARAMS := ""

.DEFAULT: all

.PHONY: compile_app copy_zmk clean

all: compile_app copy_zmk

verify-zmk:
	@ls $(ZMK_APP) >/dev/null 2>&1 || ( echo "Expected zmk code at $(ZMK_APP), but didn't find anything" && exit 1 )	

compile_app: verify-zmk
	@echo "===> Compiling app $(WEST_PARAMS)"
	@cd $(ZMK_APP) && west build $(WEST_PARAMS) -DZMK_EXTRA_MODULES="$(CURDIR)/"

clean:
	@echo "===> This can only be run in combination with the 'compile_app' target"
	@$(eval WEST_PARAMS := --pristine)

copy_zmk: verify-zmk
	@echo "Waiting for the board at $(RAW_BOARD_MOUNTPOINT)"
	@until [ -d $(RAW_BOARD_MOUNTPOINT) ]; do sleep 0.5; done
	@echo "===> Copying UF2 file to $(RAW_BOARD_MOUNTPOINT)"
	cp $(ZMK_APP)/build/zephyr/zmk.uf2 $(RAW_BOARD_MOUNTPOINT)/

follow:
	tio --baudrate 115200 /dev/ttyACM0
