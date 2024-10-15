#ifndef _ST_BASIC_H_
#define _ST_BASIC_H_

#define ST_CALL(obj, func, ...) ((obj).methods->func(&(obj), __VA_ARGS__))

#endif // _ST_BASIC_H_
