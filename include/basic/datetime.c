//
// Created by chang on 2023/7/22.
//

#include "datetime.h"

Int DAYS_OF_MONTH_USUAL[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30,
                               31, 30, 31},
        DAYS_OF_MONTH_LEAP[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30,
                                  31, 30, 31};

Date date_init(Int year, Int month, Int day){
    Date _t;
    _t.year = year;
    _t.month = month;
    _t.day = day;
    return _t;
}

bool date_is_leap_year(UInt year){
    bool flag;
    if(year % 100){
        if(year % 4)
            return false;
        else
            return true;
    }else{
        if(year % 400)
            return false;
        else
            return true;
    }
}

Int date_day_of_year(Date date){
    int i;
    Int day_count, month, day;
    bool flag;
    if(date.year < 0){
        errno = ETIME;
        perror("(date_day_of_year) year less than 0");
    }
    flag = date_is_leap_year(date.year);
    day_count = 0;
    month = date.month - 1;
    day = date.day - 1;
    for(i = 0; i < month; i++) day_count += flag ? DAYS_OF_MONTH_LEAP[i] : DAYS_OF_MONTH_USUAL[i];
    day_count += day + 1;
    return day_count;
}

void date_regularize(Date *date){
    Int n_day, year, month, day;
    year = date->year;
    month = date->month - 1;
    day = date->day - 1;
    while(month < 0){
        year -= 1;
        month += 12;
    }
    while(month > 11){
        year += 1;
        month -= 12;
    }
    while(day < 0){
        month -= 1;
        if(month < 0){
            month += 12;
            year -= 1;
        }
        n_day = date_is_leap_year(year) ? DAYS_OF_MONTH_LEAP[month] : DAYS_OF_MONTH_USUAL[month];
        day += n_day;
    }
    n_day = date_is_leap_year(year) ? DAYS_OF_MONTH_LEAP[month] : DAYS_OF_MONTH_USUAL[month];
    while(day >= n_day){
        day -= n_day;
        month += 1;
        if(month > 11){
            year += 1;
            month -= 12;
        }
        n_day = date_is_leap_year(year) ? DAYS_OF_MONTH_LEAP[month] : DAYS_OF_MONTH_USUAL[month];
    }
    date->year = year;
    date->month = month + 1;
    date->day = day + 1;
}

int time_precision_level(Time *t){
    if(t->nanosecond) return 6;
    if(t->microsecond) return 5;
    if(t->millisecond) return 4;
    if(t->second) return 3;
    if(t->minute) return 2;
    if(t->hour) return 1;
    return 0;
}

Time time_regularize(Time *t){
    Time buff;
    long long int count, res;
    int level = 6;
    level = time_precision_level(t);
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
    printf("(_time_regularize) h: %ld, m: %ld, s: %ld, ms: %ld, mus: %ld, ns: %ld\n", t->hour, t->minute, t->second,
           t->millisecond, t->microsecond, t->nanosecond);
    printf("(_time_regularize) level: %d\n", level);
#endif
    count = t->hour;
    if(level > 1){
        count *= 60;
        count += t->minute;
    }
    if(level > 2){
        count *= 60;
        count += t->second;
    }
    if(level > 3){
        count *= 1000;
        count += t->millisecond;
    }
    if(level > 4){
        count *= 1000;
        count += t->microsecond;
    }
    if(level > 5){
        count *= 1000;
        count += t->microsecond;
    }
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
    printf("(_time_regularize) count: %d\n", count);
#endif
    res = (long long)fabsl((long double)count);
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
    printf("(_time_regularize) res: %ld\n", res);
#endif
    memset(&buff, 0, sizeof(Time));
    if(count >= 0)
        switch(level){
            case 6:
                buff.nanosecond = (Int)(res % 1000);
                res /= 1000;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 5:
                buff.microsecond = (Int)(res % 1000);
                res /= 1000;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 4:
                buff.millisecond = (Int)(res % 1000);
                res /= 1000;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 3:
                buff.second = (Int)(res % 60);
                res /= 60;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 2:
                buff.minute = (Int)(res % 60);
                res /= 60;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 1:
                buff.hour = (Int)res;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            default:
                break;
        }
    else
        switch(level){
            case 6:
                buff.nanosecond = (Int)(-(res % 1000));
                res /= 1000;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 5:
                buff.microsecond = (Int)(-(res % 1000));
                res /= 1000;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 4:
                buff.millisecond = (Int)(-(res % 1000));
                res /= 1000;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 3:
                buff.second = (Int)(-(res % 60));
                res /= 60;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 2:
                buff.minute = (Int)(-(res % 60));
                res /= 60;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            case 1:
                buff.hour = (Int)(-res);
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
                printf("(_time_regularize) res: %ld\n", res);
#endif
            default:
                break;
        }
    memcpy(t, &buff, sizeof(Time));
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
    printf("(_time_regularize) h: %ld, m: %ld, s: %ld, ms: %ld, mus: %ld, ns: %ld\n", t->hour, t->minute, t->second,
           t->millisecond, t->microsecond, t->nanosecond);
#endif
    return buff;
}

Time time_hms_mmn(Int hour, Int minute, Int second, Int millisecond, Int microsecond, Int nanosecond){
    Time _t;
    _t.hour = hour;
    _t.minute = minute;
    _t.second = second;
    _t.millisecond = millisecond;
    _t.microsecond = microsecond;
    _t.nanosecond = nanosecond;
    time_regularize(&_t);
    return _t;
}

Time time_hms(Int hour, Int minute, Float second){
    Time _t;
    int ilevel;
    double _ti;
    Float b;
    b = second;
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
    printf("(time_hms) hour: %ld, minute: %ld, second: %f\n", hour, minute, second);
#endif
    for(ilevel = 3; ilevel < 6; ilevel++){
#ifdef SEISTOOLS_C_DATETIME_H_DEBUG
        printf("(time_hms) ilevel = %d, b = %f\n", ilevel, b);
#endif
        if(modf(b, &_ti))
            b *= 1000.0;
        else
            break;
    }
    _t.hour = hour;
    _t.minute = minute;
    _t.second = 0;
    _t.millisecond = 0;
    _t.microsecond = 0;
    _t.nanosecond = 0;
    switch(ilevel){
        case 3:
            _t.second = (Int)b;
            break;
        case 4:
            _t.millisecond = (Int)b;
            break;
        case 5:
            _t.microsecond = (Int)b;
            break;
        default:
            _t.nanosecond = (Int)b;
    }
    time_regularize(&_t);
    return _t;
}

Time time_time_diff(Time t1, Time t2){
    Time buff;
    buff.hour = t1.hour - t2.hour;
    buff.minute = t1.minute - t2.minute;
    buff.second = t1.second - t2.second;
    buff.millisecond = t1.millisecond - t2.millisecond;
    buff.microsecond = t1.microsecond - t2.microsecond;
    buff.nanosecond = t1.nanosecond - t2.nanosecond;
    time_regularize(&buff);
    return buff;
}

Float time_time2second(Time t){
    return t.hour * 3600.0 + t.minute * 60.0 + t.second + (Float)t.millisecond * 1e-3 + (Float)t.microsecond * 1e-6 +
           (Float)t.nanosecond * 1e-9;
}

DateTime datetime_now(void){
    struct tm *_t;
    time_t _tmr;
    DateTime dt;
    _tmr = time(NULL);
    _t = localtime(&_tmr);
    dt.date.year = _t->tm_year + 1900;
    dt.date.month = _t->tm_mon + 1;
    dt.date.day = _t->tm_mday;
    dt.time.hour = _t->tm_hour;
    dt.time.minute = _t->tm_min;
    dt.time.second = _t->tm_sec;
    dt.time.millisecond = 0;
    dt.time.microsecond = 0;
    dt.time.nanosecond = 0;
    dt.timezone = 0;
    return dt;
}

void datetime_regularize(DateTime *dt){
    Int i;
    time_regularize(&(dt->time));
    if(dt->time.hour < 0){
        i = -((dt->time).hour) / 24 + 1;
        dt->time.hour += i * 24;
        dt->date.day -= i;
        time_regularize(&(dt->time));
    }
    if(dt->time.hour >= 24){
        i = (dt->time.hour) / 24;
        dt->time.hour -= i * 24;
        dt->date.day += i;
        time_regularize(&(dt->time));
    }
    date_regularize(&(dt->date));
}
