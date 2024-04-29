# Ergo36

![Ergo36](https://i.imgur.com/bYZPD0g.jpeg)

## Project Description
Ergo36 is a customizable split keyboard designed for ease of assembly, handwiring flexibility, and seamless integration with the QMK firmware, providing users with a smooth and personalized typing experience.

## Instructions

* Place the contents of "firmware" folder into `qmk_firmware/keyboards` after changing the folder name to `ergo36`
* 2 ways to flash your own keymap
    1. **By Using Make**:<br>
    Make example for this keyboard (after setting up your build environment):
        ```bash
            make ergo36:default
        ```

        Flashing example for this keyboard:

        ```bash
            make ergo36:default:flash
        ```

        Flashing Colemak Layout:

        ```bash
            make ergo36:colemak:flash
        ```

    2. **QMK Toolbox**:
        * Use this cammand to compile the keyboard:

        ```bash
            qmk compile -kb ergo36 -km colemak
        ```

        * and then flash the `ergo36_colemak.hex` file with the help of QMK Toolbox.


*A short description of the keyboard/project*

* Keyboard Maintainer: [Ankit Bhankharia](https://github.com/cupcake08)
* Hardware: 
    - Pro Micro (any similar board) x 2
    - 1N4148 x 36 diodes
    - TRRS Jacks (PCB version recommended) x 2
    - M2 8mm standoffs x 2
    - M2 6mm screws x 4
    - Wires


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Keycode in layout**: Press the key mapped to `QK_BOOT` if its available.

