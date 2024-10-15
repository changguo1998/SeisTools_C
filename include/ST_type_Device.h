#ifndef _ST_TYPE_DEVICE_H_
#define _ST_TYPE_DEVICE_H_

#include <CBL.h>
#include "ST_basic.h"

struct Device {
    struct String network, station, channel, device;
    Float longitude, latitude; // degree
    Float elevation; // meter
    Float azimuth; // degree
    Float distance; // km
};

#endif // _ST_TYPE_DEVICE_H_
