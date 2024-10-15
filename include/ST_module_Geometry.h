#ifndef _ST_MODULE_GEOMETRY_H_
#define _ST_MODULE_GEOMETRY_H_

#include <CBL.h>

#include "ST_basic.h"

struct _ST_Geometry_reference_ellipsoid {
    Float R, r;
};

Float Geo_distance(Float lat1, Float lon1, Float lat2, Float lon2);

Float Geo_azimuth(Float lat1, Float lon1, Float lat2, Float lon2);

Float Geo_distance_ref(Float lat1, Float lon1, Float lat2, Float lon2, struct _ST_Geometry_reference_ellipsoid ref);

Float Geo_azimuth_ref(Float lat1, Float lon1, Float lat2, Float lon2, struct _ST_Geometry_reference_ellipsoid ref);


#endif // _ST_MODULE_GEOMETRY_H_
