# VendingMC

An embedded vending machine controller built on the **ATmega32** microcontroller (AVR), written in C with a layered driver architecture and a **Proteus** circuit simulation for testing without physical hardware.

## Overview

A customer inserts a balance via a 4x4 keypad, selects an item, and the machine dispenses it by driving a DC motor while an LCD shows status, change, and feedback. A hidden admin code exposes usage statistics (total customers served, total cash collected, and units sold per item).

## Features

- **Balance entry & item selection** via a 4x4 matrix keypad
- **16x2 LCD** feedback at every step (prompts, change due, errors)
- **Automatic change calculation** and insufficient-balance handling
- **Item dispensing** via DC motor control (currently wired for 2 items: Chips and Cola)
- **Admin mode** (entered via a secret balance code) showing total users, total cash collected, and per-item sales counts
- **LED feedback**: a success blink on purchase, a warning blink on insufficient balance, and an admin-mode indicator
- **Custom LCD character** (a smiley) shown after a successful purchase
- **Proteus simulation** of the full circuit for testing before flashing real hardware

## Hardware

- ATmega32 microcontroller (8 MHz)
- 16x2 character LCD (parallel interface)
- 4x4 matrix keypad
- 2x DC motors (dispensing mechanism), plus driver stage (e.g. transistor/relay — not included in this repo)
- Status LEDs

### Pin connections

| Peripheral | Signal | Pin |
|---|---|---|
| LCD | Data bus | PORTA |
| LCD | RS | PORTB.0 |
| LCD | RW | PORTB.1 |
| LCD | E | PORTB.2 |
| Keypad | Rows (R1–R4) | PORTD.0 – PORTD.3 |
| Keypad | Columns (C1–C4) | PORTD.4 – PORTD.7 |
| Motor — Item 1 (Chips) | Drive pin | PORTC.0 |
| Motor — Item 2 (Cola) | Drive pin | PORTC.2 |
| LED — Purchase success | Blink | PORTB.3 |
| LED — Admin mode active | Indicator | PORTB.4 |
| LED — Insufficient balance | Blink | PORTB.5 |

## Repository structure

```
VendingMC/
├── VMC/            AVR C source (Atmel Studio project)
│   ├── DIO_*        Digital I/O driver (GPIO HAL)
│   ├── LCD_*        Character LCD driver
│   ├── KPD_*        4x4 keypad driver
│   ├── DC_MOTOR_*   Motor control driver
│   ├── STD_TYPES.h  Standard type definitions
│   ├── BIT_MATH.h   Bit manipulation macros
│   └── main.c       Vending machine application logic
└── Protues/        Proteus (ISIS) circuit simulation project files
```

Each driver follows the same layered pattern: an `_interface.h` (public API), `_private.h` (register/internal definitions), `_configer.h` (user-editable configuration, e.g. pin assignments), and a `_program.c` (implementation).

## How it works

1. On each new customer, the LCD prompts `Enter Balance`. Digits are entered via the keypad and confirmed with `=` (or cleared/restarted with `c`).
2. If the entered balance matches a hardcoded admin code, the machine enters **admin mode**: it displays total customers served and total cash collected, then a breakdown of units sold per item, before returning to the main flow.
3. Otherwise, the LCD prompts `Select Item` and the customer presses a number key (1–2 are wired to real items in this build; the keypad supports up to 8).
4. If the balance covers the item's price, the corresponding motor runs briefly to dispense it, the LCD shows a "Come Again" message with change due and a smiley, and the success LED blinks.
5. If the balance is insufficient, the LCD shows an error and the warning LED blinks.
6. The machine resets and waits for the next customer.

Item prices are set in `main.c` (`prices[]` array) — currently Chips = 10 and Cola = 15 (in the currency unit the balance is entered in).

## Notes

- The admin access code and item prices are hardcoded in `VMC/main.c` — adjust them there for a different setup.
- The keypad driver supports 8 item keys, but only 2 motors/prices are currently configured.

## Author

[eiad20](https://github.com/eiad20)
