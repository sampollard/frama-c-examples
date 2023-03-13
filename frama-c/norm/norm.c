#include <math.h>

typedef struct {
    double x;
    double y;
} Vec;

/*@
    requires \valid_read(v);
    requires \is_finite(v->x);
    requires \is_finite(v->y);
// This next line is not sufficient to get past RTE assertions:
    //requires \is_finite(v->x * v->x + v->y * v->y);
// You need to write it like this instead:
    requires
        \let x2 = (double)(v->x * v->x);
        \let y2 = (double)(v->y * v->y);
        \let xy2 = (double)(x2 + y2);
        \is_finite(x2) && \is_finite(y2) && \is_finite(xy2);
// This is because each operation (`+` and `*`) is defined over reals, with
// arguments implicitly cast from double to real, so
// `\is_finite(v->x * v->x + v->y * v->y)` is interpreted as
// `\is_finite((real)v->x * (real)v->x + (real)v->y * (real)v->y)`
// and this expression can be finite even when the original expression is not.
    assigns errno;
    ensures \is_finite(\result);
    ensures errno == \old(errno);
*/
double norm(Vec *v) {
    return sqrt(v->x * v->x + v->y * v->y);
}
