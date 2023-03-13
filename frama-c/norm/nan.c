/*
There are two ways to verify this:

1. `frama-c -wp -wp-rte nan.c` will detect the divide-by-zero error and complain in main. The `set_x` function is fine though.

2. `frama-c -wp -wp-rte -wp-model +real nan.c` does not care about divide-by-zero, set_x is still fine.

Observations:
- In set_x we don't have to prove `\is_finite(v)`, in either model, because we are just assigning it.

*/

float x;

/*@
    assigns x;
    ensures x == v;
*/
void set_x(float v) {
    x = v;
}

/*@
    requires \is_finite(v);
    assigns x;
    ensures x == v + 1.0;
*/
void set_x_incr(float v) {
    x = v + 1;
}

/*@
    assigns x;
*/
int main() {
    float v = 0.0 / 0.0;
    set_x(v);
    return 0;
}
