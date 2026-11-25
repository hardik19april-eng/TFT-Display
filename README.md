# MEGA OS

A tiny Windows-style desktop that runs on an Arduino Mega 2560 and a 2.4" TFT touchscreen.

I wanted to see how far I could push a microcontroller toward feeling like a real computer, so I built a little GUI with a desktop, a Start button, and a taskbar. It obviously isn't Windows and doesn't run Windows. It just borrows the look and the way you move around: tap Start, pick an app, tap Home to get back.

## What you need

- Arduino Mega 2560
- 2.4" TFT touchscreen shield (mine is the SPFD5408 type)
- USB cable
- A computer with the Arduino IDE
- A microSD card (optional, only needed for the stuff I haven't finished yet)

## What it does right now

- Shows a colourful desktop with a taskbar when you power it on
- Start button that opens a menu of apps
- A basic File Explorer screen (it's only the interface for now, no real SD browsing yet)
- A Settings screen with some info about the Arduino
- An About screen for MEGA OS
- Touch navigation between all the screens
- A Home button that takes you back to the desktop from anywhere

## How it works

When the board gets power, it sets up the display and draws the desktop. Tapping Start opens the menu, and tapping an app opens its screen. Home sends you back. All of it is Arduino C++ drawing shapes and text to the screen and checking where you touched.

## Libraries

You can install all three from the Arduino IDE's Library Manager:

- `MCUFRIEND_kbv`
- `Adafruit_GFX`
- `TouchScreen`

## Running it yourself

1. Install the Arduino IDE.
2. Install the three libraries above.
3. Plug the TFT shield onto the Mega.
4. Open the MEGA OS sketch.
5. Under Tools, choose **Arduino Mega or Mega 2560** as the board and pick the right COM port.
6. Upload, then wait a moment for the desktop to show up.

One thing to watch for: TFT shields aren't all the same. If your touches land in the wrong spot or the screen stays blank, you'll probably need to adjust the touch calibration or the display controller settings for your specific shield.

## Still on my list

- Touchscreen calculator
- A few simple games
- Wallpapers loaded from the SD card
- A File Explorer that actually reads the SD card
- A digital clock
- Custom themes and desktop icons
- Sound effects (this needs extra hardware)
- A lock screen with a password

## What I'm learning

This project has been a good way to get comfortable with:

- Programming the Mega
- Driving a TFT display
- Calibrating touch coordinates (more annoying than I expected)
- Designing a GUI and handling menus and taps
- Working within the limits of a small embedded board

## Built with

- Arduino Mega 2560 and an SPFD5408 TFT touchscreen
- C++ in the Arduino IDE
- Adafruit GFX and MCUFRIEND_kbv

## The goal

Eventually I'd like MEGA OS to feel like a simple, working mini computer you can actually use. For now it shows that a microcontroller and a small touchscreen are enough to build a decent graphical interface, no traditional OS required.

<img width="516" height="412" alt="Screenshot 2026-10-26 163710" src="https://github.com/user-attachments/assets/34c2d5e1-9c58-4962-b179-94c35480b51f" />
<img width="685" height="466" alt="Screenshot 2026-10-26 163729" src="https://github.com/user-attachments/assets/89e0118b-cbc1-4e64-b303-45125fb7df8b" />
<img width="532" height="297" alt="Screenshot 2026-10-26 163840" src="https://github.com/user-attachments/assets/6125c6ee-8fad-4aaa-a9a3-1061706e23fc" />
<img width="1383" height="947" alt="Screenshot 2026-10-26 164221" src="https://github.com/user-attachments/assets/b93a99e7-5f9b-43d7-8bfd-dd403d5783b3" />
