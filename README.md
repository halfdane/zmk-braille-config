# Braille Keyboard
A 10 keys ortholinear mini-keyboard that connects via bluetooth.
Pressing the central six keys in braille patterns will send the corresponding keypresses to the host.

## Features
- All german letters, numbers and symbols of grade 1
- Connects to up to five bluetooth hosts which can be changed on the fly
- [Haptic feedback](#haptic-feedback) for bluetooth functions
- Supports the complete german "Vollschrift" (i.e. grade 1): [patterns](de.md)
- Reset into bootloader mode for firmware updates

## Missing Features
- No math mode
- No other languages
- Settings etc. are confusing


## Haptic Feedback
Uses the https://github.com/halfdane/zmk-behavior-haptic-feedback module to make a vibration motor go brr.

## Local development
Automatic setup expects you to run linux. 
On MacOS, it might just work with some changes, but you're on your own there.

`make west_setup` # this takes a while

Run `make` or `make all` to compile the firmware and copy it to your NICENANO.
`make clean` just removes the build dir, while `make deep_clean` removes all dependencies so you have to run `make west_setup` again.

`make follow` invokes the `tio` command to watch log messages fly by. It's lovely 🤗

## Roadmap
