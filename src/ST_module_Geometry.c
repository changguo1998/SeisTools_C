#include <math.h>
#include "CBL.h"
#include "ST_module_Geometry.h"

#define PI 3.14159265358979323846
#define PI2 6.28318530717958647692

FloatVectorN(3)

static inline Float deg2rad(Float deg) { return deg * PI / 180.0; }
static inline Float rad2deg(Float rad) { return rad * 180.0 / PI; }
static inline Float cosdeg(Float angle) { return cos(deg2rad(angle)); }
static inline Float sindeg(Float angle) { return sin(deg2rad(angle)); }

static inline Float dot(struct FloatVector_3 a, struct FloatVector_3 b) {
    return CBL_CALL(a, get, 0) * CBL_CALL(b, get, 0) +
        CBL_CALL(a, get, 1) * CBL_CALL(b, get, 1) +
        CBL_CALL(a, get, 2) * CBL_CALL(b, get, 2);
}

static struct FloatVector_3 cross(struct FloatVector_3 a, struct FloatVector_3 b) {
    CBL_DECLARE_VARS(FloatVector_3, 1, result);
    result.data[0] = CBL_CALL(a, get, 1) * CBL_CALL(b, get, 2) - CBL_CALL(a, get, 2) * CBL_CALL(b, get, 1);
    result.data[1] = CBL_CALL(a, get, 2) * CBL_CALL(b, get, 0) - CBL_CALL(a, get, 0) * CBL_CALL(b, get, 2);
    result.data[2] = CBL_CALL(a, get, 0) * CBL_CALL(b, get, 1) - CBL_CALL(a, get, 1) * CBL_CALL(b, get, 0);
    return result;
}

static void normalize(struct FloatVector_3* v) {
    Float n, n2;
    n2 = v->data[0] * v->data[0] + v->data[1] * v->data[1] + v->data[2] * v->data[2];
    n = sqrt(n2);
    v->data[0] /= n;
    v->data[1] /= n;
    v->data[2] /= n;
}

Float Geo_distance(Float lat1, Float lon1, Float lat2, Float lon2) {
    CBL_DECLARE_VARS(FloatVector_3, 2, r1, r2);
    CBL_CALL(r1, set_all_, cosdeg(lon1) * cosdeg(lat1), sindeg(lon1)*cosdeg(lat1), sindeg(lat1));
    CBL_CALL(r2, set_all_, cosdeg(lon2) * cosdeg(lat2), sindeg(lon2)*cosdeg(lat2), sindeg(lat2));
    return 6371.0 * acos(dot(r1, r2));
}

Float az_none_negative(Float a) {
    while(a < 0) a += 360.0;
    while(a > 360) a -= 360.0;
    return a;
}

Float Geo_azimuth(Float lat1, Float lon1, Float lat2, Float lon2) {
    Float x, y;
    CBL_DECLARE_VARS(FloatVector_3, 7, r1, r2, north1, east1, north_e, v12, vrot);
    CBL_CALL(r1, set_all_, cosdeg(lon1) * cosdeg(lat1), sindeg(lon1)*cosdeg(lat1), sindeg(lat1));
    CBL_CALL(r2, set_all_, cosdeg(lon2) * cosdeg(lat2), sindeg(lon2)*cosdeg(lat2), sindeg(lat2));
    CBL_CALL(north_e, set_all_, 0.0, 0.0, 1.0);

    east1 = cross(north_e, r1);
    normalize(&east1);
    north1 = cross(r1, east1);
    normalize(&north1);

    vrot = cross(r1, r2);
    normalize(&vrot);

    v12 = cross(vrot, r1);
    normalize(&v12);
    x = dot(v12, east1);
    y = dot(v12, north1);
    return az_none_negative(rad2deg(atan2(x, y)));
}
