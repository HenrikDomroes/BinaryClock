# BinaryClock
simple binary clock (no seconds) using Arduino nano and RTC DS3231

Used a simple image frame as a housing. Clock is powered via microUSB directly into the arduino nano every.
To build, simply connect RTC, Arcuino and LEDs with resistors and buttons according to schematic.
Run setRTC.ino once to initialize RTC once, set Weekday and date etc. (optional)
Run BinaryClock.ino to flash arduino accordingly. Clock should be working afterwards.
Hours and minutes can be set individually via Buttons, RTC remembers time even when clock is powered off temporarily.

I used diffused light LEDs, but every LED will do.
3D parts were printed with Anycubic PLA 1,75mm on an Anycubic i3 Mega S. Layer height = 0.2mm
Thin white PLA was used do diffract light even more. Black PLA was used for the housing and numbers.
