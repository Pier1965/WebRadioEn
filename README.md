# MonCafeRadio
Esp32 web/FM radio
---------------

This is a esp32 based web radio.
All the hardware requirements, schematics and pinout, can be fount in the Docs subfolders.
All the drawings for a suitable 3D printed case, in openscad format, can be found
in the Docs/drawings directory.

Settings
--------
The following files could/should be altered in order to personalize the compilation
process. This latter can been performed relying on VS code and the Platformio plugin:
- platformio.ini (set the esp32 model);
- include/gpio.h (for different pinout configuration);
- include/define.h (change OLED dimensions and pinout, enable use of NEXTION touch);
- nclude/ir_butt.h (setting the IR remote control);
- include/preproDefine.h (to set debug option);
- include/GlobalVar.h (to set a different ntp server);
- include/GlobalObject.h line 16 (to set the local time zone).

First run
---------
With the working mode switch (clock/radio) in clock position,
at the first start the radio will act as an Access Point with
the name "WebRadioAP". Connect to it and go to the address
192.168.1.4 where SSID and password of the home wifi can be set.
SSID and password can be changed anytime in clock mode pushing
the volumeUp button.

List of radios managing
-----------------------
At the first start a few stations will be available. The list of stations
can be altered by accessing the address of the radio,
readable on the OLED screen by means of a browser.
Stations can be:
- added;
- deleted singularly and in group;
- reordered moving each station in a new position in list;
- swapped in position;
- searched via key word search querying https://www.radio-browser.info/
- the list created can be exported in json format;
- a list can be inported in json format.
