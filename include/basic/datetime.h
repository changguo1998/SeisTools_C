/*
 * MIT License
 *
 * Copyright (c) 2023 Chang Guo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef SEISTOOLS_C_DATETIME_H
#define SEISTOOLS_C_DATETIME_H


#include "basic_types.h"

//#define SEISTOOLS_C_DATETIME_H_DEBUG

typedef struct seistools_date_t{
    Int year, month, day;
} Date;

Date date_init(Int year, Int month, Int day);

bool date_is_leap_year(UInt year);

Int date_day_of_year(Date date);

void date_regularize(Date *date);

typedef struct seistools_time_t{
    Int hour, minute, second, millisecond, microsecond, nanosecond;
} Time;

Time time_regularize(Time *t);

Time time_hms_mmn(Int hour, Int minute, Int second, Int millisecond, Int microsecond, Int nanosecond);

Time time_hms(Int hour, Int minute, Float second);

Time time_time_diff(Time t1, Time t2);

Time time_datetime_diff(Date d1, Time t1, Date d2, Time t2);

Float time_time2second(Time t);


typedef struct seistools_datetime_t{
    Date date;
    Time time;
    int timezone;
} DateTime;

DateTime datetime_now(void);

void datetime_regularize(DateTime *dt);

#endif //SEISTOOLS_C_DATETIME_H
