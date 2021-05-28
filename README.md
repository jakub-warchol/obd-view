# obd-view
The mobile (Android/iOS) application for reading and visualizing data received from OBD controller. It was created in cooperation with [Sebastian Waluś](https://github.com/R1PeR) whose was responsible for hardware site.
The application was created in Qt. The frontend was designed in _QML_. The communication site is serviced by _C++_.

It is my diploma project.

**NOTE:** you can build and use this application, but you lose the notification support.

## Table of Contents
1. [Description](#description)
2. [Requirements](#requirements)
3. [Downloads](#downloads)
4. [Views](#views)

## Description  <a name="description"></a>
This application allows user to follow a car rate, including current velocity, coordination and any other diagnostics data. In the car there is communication module implemented, which receives data from an _ELM327_ device and sends it to the _ThingSpeak_. The car is distinguished by _IMEI_ module number, which is a part of the hardware driver.

On the _ThingSpeak_ cloud special algorithm extracts and analyses received data chunk. When some of mistakes are detected, the end user will be notified in this application.

## Requirements <a name="requirements"></a>
Qt >= 5.12

## Downloads <a name="downloads"></a>
This project constains one submodule to use _OpenSSL_ on Android platform. 
After cloning project you should call below commands to pull submodule:
```bash
$ git submodule update --init --recursive
```

Special thanks to KDAB for creating that [project](https://github.com/KDAB/android_openssl)!

# Views <a name="views"></a>
* Current velocity and rpm:
 
![](https://user-images.githubusercontent.com/48067722/119954637-7a731600-bf9f-11eb-991a-fffe7a837a66.png)

* Coordination with drawed route since appplication open:

![](https://user-images.githubusercontent.com/48067722/119955274-32a0be80-bfa0-11eb-8cf5-ef9765597736.png)

* _ECU_ errors

![](https://user-images.githubusercontent.com/48067722/119955580-7693c380-bfa0-11eb-8c65-1e09f4ce3ba6.png)
