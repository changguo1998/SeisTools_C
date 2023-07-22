//
// Created by chang on 2023/7/22.
//
#include <stdio.h>
#include "../include/basic/datetime.h"

int main(void){
    Time t;
    Date d;
    d = date_init(2024, 12, 31);
    t = time_hms(0, 0, 100.6);
    printf("%04ld-%02ld-%02ld day of year: %ld\n", d.year, d.month, d.day, date_day_of_year(d));
    printf("%02ld:%02ld:%02ld.%03ld\n", t.hour, t.minute, t.second, t.millisecond);
    return 0;
}