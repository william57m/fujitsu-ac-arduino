//
//  main.c
//  Fuji AC IR Code
//
//  Created by William Mura on 2020-05-28.
//  Copyright © 2020 William Mura. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_SEQUENCE            243

#define BIT_MASTER_MODE_1_START  147
#define BIT_MASTER_MODE_1_END    150

#define BIT_FAN_MODE_1_START     163
#define BIT_FAN_MODE_1_END       168

#define BIT_MODE_2_START         227
#define BIT_MODE_2_END           234

#define BIT_TEMPERATURE_1_START  139
#define BIT_TEMPERATURE_1_END    146

#define BIT_TEMPERATURE_2_START  235
#define BIT_TEMPERATURE_2_END    242

#define BIT_FLAG_ON              131

#define TEMPERATURE_1_VALUE_START 2
#define TEMPERATURE_2_VALUE_START 10


const int BIT_SPACE_VALUE = 420;
const int BIT_LOW_VALUE = 396;
const int BIT_HIGH_VALUE = 1212;

const int HIGH_BITS[] = {7, 11, 19, 21, 29, 31, 59, 75, 87, 89, 91, 93, 95, 97, 105, 123, 125};
const int HIGH_BITS_SIZE = 17;


/**
 * Convert a given decimal to binary
 * @param decimal the value to convert to binary
 * @return array representing the binary
 */
int* decimalToBinary(int decimal) {
    static int binary[4];
    for(int j=0; j<4; j++) binary[j] = 0;
    for(int i=0; decimal>0; i++) {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
    }
    return binary;
}

/**
 * Init IR sequence with marks and spaces
 * @param sequence the full IR sequence
 * @param flagOn set the bit to turn on the AC
 */
void initSequence(int *sequence, int flagOn) {
    // Init spaces and low bits
    for (int i=0; i<SIZE_SEQUENCE; i++) {
        if (i%2) {
            sequence[i] = BIT_LOW_VALUE;
        } else {
            sequence[i] = BIT_SPACE_VALUE;
        }
    }
    
    // Init fixed bits
    sequence[0] = 3200;
    sequence[1] = 1600;
    
    // Init high bits
    for (int i=0; i<HIGH_BITS_SIZE; i++) {
        int index = HIGH_BITS[i];
        sequence[index] = BIT_HIGH_VALUE;
    }
    
    // Flag on
    if (flagOn) {
        sequence[BIT_FLAG_ON] = BIT_HIGH_VALUE;
    }
}

/**
 * Set the first set of bits for the master mode
 * @param sequence the full IR sequence
 * @param mode (0=auto, 1=cool, 2=dry, 3=fan)
 */
void setMasterMode(int *sequence, int mode) {
    int i;
    int start = 0;
    int *valueBinary = decimalToBinary(mode);

    for (i=BIT_MASTER_MODE_1_START; i<=BIT_MASTER_MODE_1_END; i++) {
        if (i%2) {
            sequence[i] = *(valueBinary + start) ? BIT_HIGH_VALUE : BIT_LOW_VALUE;
            start++;
        }
    }
}

/**
 * Set the first set of bits for the fan mode
 * @param sequence the full IR sequence
 * @param mode (0=auto, 1=high, 2=med, 3=low, 4=quiet)
 */
void setFanMode(int *sequence, int mode) {
    int i;
    int start = 0;
    int *valueBinary = decimalToBinary(mode);

    for (i=BIT_FAN_MODE_1_START; i<=BIT_FAN_MODE_1_END; i++) {
        if (i%2) {
            sequence[i] = *(valueBinary + start) ? BIT_HIGH_VALUE : BIT_LOW_VALUE;
            start++;
        }
    }
}

/**
 * Set the second set of bits for the master and fan mode
 * @param sequence the full IR sequence
 * @param masterMode (0=auto, 1=cool, 2=dry, 3=fan)
 * @param fanMode (0=auto, 1=high, 2=med, 3=low, 4=quiet)
 * @param flagOn (0=regular command, 1=turn on the AC)
 */
void setMode(int *sequence, int masterMode, int fanMode, int flagOn) {
    int i;
    int start = 0;
    int mixedMode = masterMode + fanMode + flagOn;
    int valueDecimal = 0 - mixedMode;
    valueDecimal = valueDecimal < 0 ? 16 + valueDecimal : valueDecimal;
    printf("value: %d", valueDecimal);
    int *valueBinary = decimalToBinary(valueDecimal);

    for (i=BIT_MODE_2_START; i<=BIT_MODE_2_END; i++) {
        if (i%2) {
            sequence[i] = *(valueBinary + start) ? BIT_HIGH_VALUE : BIT_LOW_VALUE;
            start++;
        }
    }
}

/**
 * Set the bits for the temperature
 * @param sequence the full IR sequence
 * @param temp  the temperature in celsius between 18 and 30
 * @param tempOffset offset for the temp value
 */
void setTemperature(int *sequence, int temp, int tempOffset) {
    int i;
    int indexTemp = temp - 18;

    // First set of bit
    int start = 0;
    int valueDecimal = TEMPERATURE_1_VALUE_START + indexTemp;
    int *valueBinary = decimalToBinary(valueDecimal);

    for (i=BIT_TEMPERATURE_1_START; i<=BIT_TEMPERATURE_1_END; i++) {
        if (i%2) {
            sequence[i] = *(valueBinary + start) ? BIT_HIGH_VALUE : BIT_LOW_VALUE;
            start++;
        }
    }

    // Second set of bit
    start = 0;
    valueDecimal = TEMPERATURE_2_VALUE_START - indexTemp + tempOffset;
    valueDecimal = valueDecimal < 0 ? 16 + valueDecimal : valueDecimal;
    valueBinary = decimalToBinary(valueDecimal);

    for (i=BIT_TEMPERATURE_2_START; i<=BIT_TEMPERATURE_2_END; i++) {
        if (i%2) {
            sequence[i] = *(valueBinary + start) ? BIT_HIGH_VALUE : BIT_LOW_VALUE;
            start++;
        }
    }
}

/**
 * Generate IR sequence for the given parameters
 * @param temp  the temperature in celsius between 18 and 30
 * @param masterMode (0=auto, 1=cool, 2=dry, 3=fan)
 * @param fanMode (0=auto, 1=high, 2=med, 3=low, 4=quiet)
 * @param flagOn (0=regular command, 1=turn on the AC)
 * @return array containing the IR sequence of the command
 */
int* generateCommand(int temp, int masterMode, int fanMode, int flagOn) {
    static int sequence[243];
    const int tempOffset = (masterMode == 0 && fanMode == 0 && !flagOn) ? 1 : 0;

    initSequence(sequence, flagOn);
    setTemperature(sequence, temp, tempOffset);
    setMasterMode(sequence, masterMode);
    setFanMode(sequence, fanMode);
    setMode(sequence, masterMode, fanMode, flagOn);

    return sequence;
}
