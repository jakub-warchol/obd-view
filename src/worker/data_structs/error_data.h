#ifndef ERROR_DATA_H
#define ERROR_DATA_H

#include <cstdint>

extern "C" {
    /*!
     * \brief The errorFrame_t struct - stores diagnostic error
     */
    struct errorFrame_t {
        uint8_t m_type;
        uint16_t m_code;
    };
}

#endif // ERROR_DATA_H
