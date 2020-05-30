# Fujitsu AC Remote for Arduino

Allow to control a Fujitsu ASU12CQ with infrared.

## Architecture

[RaspberryPi] ---> RF433 ---> [Arduino] ---> IR ---> [AC]


## Files

- `fujitsu-ac-arduino.ino` is the main file containaing the main loop for the Arduino. It listens RF433 code and generate IR sequence to be sent to the AC.
- `commands.h` contains the simple IR commands (Turn off, toggle swing, toggle airclean, set the wing position)
- `command-generator.ino` provides a function `generateCommand` which allow to generate complex IR sequence containing all the settings for the AC (Master mode, fan mode, temperature)

## Usage

To control the AC over RF433, you need to send an integer code.

Here is the code for the simple operation
- 15001: Turn off
- 15002: Toogle airclean
- 15003: Toogle swing
- 15004: Set wing position

For the control of the master mode, fan mode, the temperature and to turn it on here is the template of the code to send.

#### RF Code template
{2}temperature{1}mastermode{1}fanmode{1}toggleon

#### Temperature:
- 18 to 30 (degree celsius)

#### Master mode
- 0: auto
- 1: cool
- 2: dry
- 3: fan

#### Fan mode
- 0: auto
- 1: high
- 2: med
- 3: low
- 4: quiet

#### Toggle on
- 0: send command when AC is already on
- 1: send command when AC is off

#### Example

To turn on the AC on 22 degree on auto mode and fan quiet here is the code to send: `22041` (22 for 22 degree, 0 for master on auto mode, 4 for fan on quiet mode and 1 to turn on the AC)
