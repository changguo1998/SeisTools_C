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