#include <math.h>

// Specification from Sylvie Boldo. This fails to
// prove automatically with Frama-C + Gappa
// https://www.lri.fr/~sboldo/progs/Sterbenz.c.html
/* requires  y/2. <= x <= 2.*y;
   ensures   \result == x-y;
  */

/*@
    requires \is_finite(x);
    requires \is_finite(y);
    requires y/2. <= x <= 2.*y;
    assigns \nothing;
    ensures \is_finite(\result);
    ensures \result == (double) x - y;
*/

double sterbenz(double x, double y) {
    return x - y;
}
