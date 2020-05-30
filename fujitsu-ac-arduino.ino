#include <IRremote.h>
#include "RCSwitch.h"
#include "commands.h"

IRsend irsend;
decode_results results;
RCSwitch mySwitch = RCSwitch();

void setup()
{
  // Start logger
  Serial.begin(115200);

  // Enable RF433
  mySwitch.enableReceive(0);

  // Log
  Serial.println("Boot ok");
}

void sendCode(unsigned int *code, size_t sizeCode) {
  irsend.sendRaw(code, sizeCode, 38);
}

void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.print("Unknown encoding");
    } else if (value == 15001) {
      // Turn off
      const int *COMMAND_TURN_OFF = ARRAY_CONCAT(int, common, 83, turn_off_part, 16);
      sendCode(COMMAND_TURN_OFF, 99);
    } else if (value == 15002) {
      // Toggle airclean
      const int *COMMAND_TOGGLE_AIRCLEAN = ARRAY_CONCAT(int, common, 83, toggle_airclean_part, 16);
      sendCode(COMMAND_TOGGLE_AIRCLEAN, 99);
    } else if (value == 15003) {
      // Toggle swing
      const int *COMMAND_TOGGLE_SWING = ARRAY_CONCAT(int, common, 83, toggle_swing_part, 16);
      sendCode(COMMAND_TOGGLE_SWING, 99);
    } else if (value == 15004) {
      // Set wing
      const int *COMMAND_SET_WING = ARRAY_CONCAT(int, common, 83, set_wing_part, 16);
      sendCode(COMMAND_SET_WING, 99);
    } else if (value >= 18000) {
      Serial.print("Received: ");
      Serial.println(value);
      // Format code: {2}temp{1}masterMode{1}fanMode{1}flagOn
      String command = String(value);
      int temp = command.substring(0, 2).toInt();
      int masterMode = command.substring(2, 3).toInt();
      int fanMode = command.substring(3, 4).toInt();
      int flagOn = command.substring(4, 5).toInt();
      int *sequence = generateCommand(temp, masterMode, fanMode, flagOn);
      sendCode(sequence, 243);
    }

    mySwitch.resetAvailable();
  }
}
