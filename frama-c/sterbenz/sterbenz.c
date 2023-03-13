#include <math.h>

/*@
    requires \is_finite(x);
    requires \is_finite(y);
    requires y/2 <= x <= 2*y;
    assigns \nothing;
    ensures \is_finite(\result);
    ensures \result == (double) x - y;
*/
double sterbenz(double x, double y) {
    return x - y;
}
