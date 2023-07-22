//
// Created by chang on 2023/7/22.
//

#ifndef SEISTOOLS_C_DATETIME_H
#define SEISTOOLS_C_DATETIME_H


#include "basic_types.h"

//#define SEISTOOLS_C_DATETIME_H_DEBUG

//Int DAYS_OF_MONTH_USUAL[12], DAYS_OF_MONTH_JULIAN[12];

typedef struct{
    Int year, month, day;
} Date;

Date date_init(Int year, Int month, Int day);

Int date_day_of_year(Date date);

typedef struct{
    Int hour, minute, second, millisecond, microsecond, nanosecond;
} Time;

Time time_regularize(Time *t);

Time time_hms_mmn(Int hour, Int minute, Int second, Int millisecond, Int microsecond, Int nanosecond);

Time time_hms(Int hour, Int minute, Float second);

Time time_time_diff(Time t1, Time t2);

Time time_datetime_diff(Date d1, Time t1, Date d2, Time t2);

Float time_time2second(Time t);


typedef struct{
    Date date;
    Time time;
    int timezone;
} LocalDateTime;


#endif //SEISTOOLS_C_DATETIME_H
