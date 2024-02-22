# Braille Keyboard

## Haptic Feedback
Uses the https://github.com/halfdane/zmk-behavior-haptic-feedback module to make a vibration motor go brr.gst

## Local development
Automatic setup expects you to run linux. 
On MacOS, it might just work with some changes, but you're on your own there.

`make west_setup` # this takes a while

Run `make` or `make all` to compile the firmware and copy it to your NICENANO.
`make clean` just removes the build dir, while `make deep_clean` removes all dependencies so you have to run `make west_setup` again.

`make follow` invokes the `tio` command to watch log messages fly by. It's lovely 🤗
