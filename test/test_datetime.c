//
// Created by chang on 2023/7/22.
//
#include <stdio.h>
#include "../include/basic/datetime.h"

int main(void){
    Time t;
    Date d;
    Int i;
    DateTime dt;
    dt = datetime_now();
    printf("now: %04ld-%02ld-%02ld %02ld:%02ld:%02ld\n", dt.date.year, dt.date.month, dt.date.day, dt.time.hour,
           dt.time.minute, dt.time.second);
    dt.time.minute -= 60 + 24*60;
    printf("now: %04ld-%02ld-%02ld %02ld:%02ld:%02ld\n", dt.date.year, dt.date.month, dt.date.day, dt.time.hour,
           dt.time.minute, dt.time.second);
    datetime_regularize(&dt);
    printf("now: %04ld-%02ld-%02ld %02ld:%02ld:%02ld\n", dt.date.year, dt.date.month, dt.date.day, dt.time.hour,
           dt.time.minute, dt.time.second);
    d = dt.date;
    t = time_hms(0, 0, 100.6);
    printf("%04ld/%02ld/%02ld day of year: %ld\n", d.year, d.month, d.day, date_day_of_year(d));
    printf("%02ld:%02ld:%02ld.%03ld\n", t.hour, t.minute, t.second, t.millisecond);
    i = date_day_of_year(d);
    d.year = 2024;
    d.month = -10;
    d.day = 29;
    printf("%04ld/%02ld/%02ld\n", d.year, d.month, d.day);
    date_regularize(&d);
    printf("%04ld/%02ld/%02ld\n", d.year, d.month, d.day);
    d.year = 2025;
    d.month = -10;
    d.day = 29;
    printf("%04ld/%02ld/%02ld\n", d.year, d.month, d.day);
    date_regularize(&d);
    printf("%04ld/%02ld/%02ld\n", d.year, d.month, d.day);
    return 0;
}