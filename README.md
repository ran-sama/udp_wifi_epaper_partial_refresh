# udp_wifi_epaper_partial_refresh
Parse and display weather data in 9 individual lines by means of a delimiter and single UDP packets.

(though you can display anything you want without recompiling)

![alt text](https://raw.githubusercontent.com/ran-sama/udp_wifi_epaper_partial_refresh/master/images/epaper_bitmap.jpg)
![alt text](https://raw.githubusercontent.com/ran-sama/udp_wifi_epaper_partial_refresh/master/images/epaper_preview.jpg)

## Dependencies
```
GxEPD2-1.1.4 or newer: https://github.com/ZinggJM/GxEPD2
Adafruit-GFX-Library-1.3.6 or newer: https://github.com/adafruit/Adafruit-GFX-Library
```

## Wiring
```
ESP32
04 = Busy
16 = Reset
17 = DC
05 = ChipSelect
18 = Clock
23 = DIN
GND = Ground
VCC = +3.3 V
```
## Added error handling
```
1) No wifi connection can be restablished after 30 sec:
-> reboot
2) Wifi connection is lost:
-> reboot
3) Running longer than 30 minutes:
-> full refresh and reboot
```

## Notes
This is meant to be run on the GDEP015OC1 e-Paper display.
If you use other displays make sure to edit the code before.

## License
Licensed under the WTFPL license.
