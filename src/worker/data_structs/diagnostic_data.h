#ifndef DIAGNOSTIC_DATA_H
#define DIAGNOSTIC_DATA_H

#include <stdint.h>

extern "C" {
    /*!
     * \brief The dataFrame_t struct - stores received diagnostic data
     */
    struct dataFrame_t {
        uint8_t bank0;
        uint8_t bank1;
        uint16_t rpm;
        uint16_t speed;
        uint16_t intakePressure;
        uint16_t fuelPressure;
        uint8_t fuelInjectTiming;
        uint8_t intakeTemp;
        uint8_t oilTemp;
        uint8_t fuelLevel;
        uint8_t throttlePosition;
        uint8_t voltage;
    };
}
#endif // DIAGNOSTIC_DATA_H
