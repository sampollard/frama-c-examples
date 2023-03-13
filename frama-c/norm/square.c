#include <math.h>

// Frama-C cannot prove that x is finite
/*@
    requires 0. <= x <= 1000.0;
    ensures 0. <= \result <= 1e6;
    assigns errno;
    ensures errno == \old(errno);
*/
double square1(double x) {
	return x*x;
}

// This does not prove for some reason
/*@
    requires \is_finite(x);
    requires 0. <= x <= 1000.0;
    ensures 0. <= \result <= 1e6;
    assigns errno;
    ensures errno == \old(errno);
*/
double square2(double x) {
	return x*x;
}

// This proves just fine
/*@
    requires \is_finite(x);
    requires 0. <= x <= 1000.0;
    ensures 0. <= \result <= 1000000.0;
    assigns \nothing;
*/
double square3(double x) {
	return x*x;
}

/*@
    requires \is_finite(x) && \is_finite(y);
    requires 0. <= x <= 1000. && 0. <= y <= 1000.;
    ensures \is_finite(\result);
    // the actual max norm is 44.72135955
    ensures 0. <= \result;
    assigns \nothing;
*/
double norm(double x, double y) {
    return square3(x) + square3(y);
}
