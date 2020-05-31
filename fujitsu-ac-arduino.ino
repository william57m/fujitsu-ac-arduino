#include <IRremote.h>
#include "RCSwitch.h"
#include "commands.h"

// RF codes
#define CODE_TURN_OFF        15001;
#define CODE_TOGGLE_AIRCLEAN 15002;
#define CODE_TOGGLE_SWING    15003;
#define CODE_SET_WING        15004;

// Init IR
IRsend irsend;

// Init RF
RCSwitch rfSwitch = RCSwitch();

void setup() {
  rfSwitch.enableReceive(0);
}

void sendCode(unsigned int *code, size_t sizeCode) {
  irsend.sendRaw(code, sizeCode, 38);
}

void loop() {
  if (rfSwitch.available()) {
    int value = rfSwitch.getReceivedValue();

    if (value == CODE_TURN_OFF) {
      sendCode(COMMAND_TURN_OFF, 99);
    } else if (value == CODE_TOGGLE_AIRCLEAN) {
      sendCode(COMMAND_TOGGLE_AIRCLEAN, 99);
    } else if (value == CODE_TOGGLE_SWING) {
      sendCode(COMMAND_TOGGLE_SWING, 99);
    } else if (value == CODE_SET_WING) {
      sendCode(COMMAND_SET_WING, 99);
    } else if (value >= 18000) {
      String command = String(value);
      int temp = command.substring(0, 2).toInt();
      int masterMode = command.substring(2, 3).toInt();
      int fanMode = command.substring(3, 4).toInt();
      int flagOn = command.substring(4, 5).toInt();
      int *sequence = generateCommand(temp, masterMode, fanMode, flagOn);
      sendCode(sequence, 243);
    }

    delay(500);
    rfSwitch.resetAvailable();
  }
}
