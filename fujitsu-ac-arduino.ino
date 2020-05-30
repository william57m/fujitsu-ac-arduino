#include <IRremote.h>
#include "RCSwitch.h"
#include "commands.h"

IRsend irsend;
decode_results results;
RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableReceive(0);
}

void sendCode(unsigned int *code, size_t sizeCode) {
  irsend.sendRaw(code, sizeCode, 38);
}

void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();

    if (value == 15001) {
      // Turn off
      sendCode(COMMAND_TURN_OFF, 99);
    } else if (value == 15002) {
      // Toggle airclean
      sendCode(COMMAND_TOGGLE_AIRCLEAN, 99);
    } else if (value == 15003) {
      // Toggle swing
      sendCode(COMMAND_TOGGLE_SWING, 99);
    } else if (value == 15004) {
      // Set wing
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
    mySwitch.resetAvailable();
  }
}
