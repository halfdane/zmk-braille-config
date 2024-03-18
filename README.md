# Braille Keyboard
A 10 keys ortholinear mini-keyboard that connects via bluetooth.
Pressing the central six keys in braille patterns will send the corresponding keypresses to the host.

Find an example case in the directory [`case`](case)

## Features
- All german letters, numbers and symbols of grade 1
- Connects to up to five bluetooth hosts which can be changed on the fly
- [Haptic feedback](#haptic-feedback)
- Supports the complete german "Vollschrift" (i.e. grade 1): [patterns](de.md)
- Reset into bootloader mode for firmware updates
- Case can be 3D-printed
- rev2 (default) uses direct pin - so diodes aren't necessary for the matrix

## Missing Features
- No math mode
- No other languages
- Settings and Navigation etc. are confusing and undocumented

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
- build an MVC with
    - [x] xiao ble (instead of half broken nice!nano)
    - [x] 3d print a case (instead of using massive amounts of hot glue)
    - [x] a proper rumble motor (instead of soldering metal to the axis of a small motor)
    - [x] direct pin instead of a matrix (no diodes)
    - [x] batteries (instead of using a power bank because the loading circuit was fried years ago)
- try to combine the braille tables of liblouis with CLDR keyboard descriptions to automatically generate languages
- [x] activating the rumble motor is currently blocking the main thread - make it concurrent
- create a '1.0' version ("slimline")
    - smd components on a tiny pcb
    - repairable case (esp. openable)