#ifndef _ST_TYPE_TRACE_H_
#define _ST_TYPE_TRACE_H_

#include <stdio.h>
#include <CBL.h>

struct Trace {
    Float dt;

    struct DateTime    reftime;
    struct FloatVector pick, data;

    struct _TraceMethods* methods;
};

struct _TraceMethods {
    // # io

    void (*read_fp)(struct Trace* this, FILE* fp);

    void (*read_file)(struct Trace* this, struct String filename);

    void (*read_sac)(struct Trace* this, FILE* fp);

    void (*write_fp)(struct Trace* this, FILE* fp);

    void (*write_file)(struct Trace* this, struct String filename);

    // #

    void (*cut_)(struct Trace* this, struct DateTime start, struct DateTime stop);

    void (*merge_)(struct Trace* this, struct Trace* src, Int nsrc);
};

extern struct _TraceMethods _ST_TRACE_METHODS;

static inline void Trace_new_(struct Trace* this) {
    FloatVector_new_(&(this->pick));
    FloatVector_new_(&(this->data));
    this->methods = &_ST_TRACE_METHODS;
}

#endif // _ST_TYPE_TRACE_H_
