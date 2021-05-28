#ifndef GPS_DATA_H
#define GPS_DATA_H

extern "C" {
    /*!
     * \brief The gpsFrame_t struct - stores coordination data
     */
    struct gpsFrame_t {
        double latitude;
        double longitude;
    };
}

#endif // GPS_DATA_H
