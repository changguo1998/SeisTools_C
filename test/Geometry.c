#include <stdio.h>
#include <stdlib.h>
#include "SeisTools.h"
#include "ST_module_Geometry.h"

int main() {
    Float lat1 = 0.0, lon1 = 0.0, lat2 = 1.0, lon2 = 0.0, dist, az;
    dist = Geo_distance(lat1, lon1, lat2, lon2);
    az = Geo_azimuth(lat1, lon1, lat2, lon2);
    printf("dist: %.3f\n", dist);
    printf("az: %.3f\n", az);
    return 0;
}
