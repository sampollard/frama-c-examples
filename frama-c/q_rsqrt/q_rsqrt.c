/* Inverse Square Root specification using Frama-C
 * Author: Samuel Pollard (spolla@sandia.gov)
 * Last modified: March 31, 2022
 */
#include <stdio.h>
#include <math.h>

typedef int i32;

/* Assignment: complete this specification.
 * Specifically:
 * 1. Add other ensures clauses so that it is as precise and complete as possible.
 *    Are there any "exceptional" cases that are not described by \is_finite?
 *    Can we say anything about what the output looks like? One disambiguation
 *    is: returning NaN or +/- infinity is not considered valid behavior for
 *    this (unlike sqrt, which is defined for such values).
 * 2. Calculate the widest possible range such that the "ensures" clause holds.
 *    Some strategies you may want to use: pen and paper analysis, gappa, or
 *    frama-c using its "-eva" mode (extended value analysis a.k.a. abstract
 *    interpretation)
 * 3. Describe the error, or the difference between 1/sqrt(x) in floating-point
 *    versus real numbers, and write and prove this as an ACSL specification.
 * Start by running "make fc-r"
 */

/*@ requires 1.0 <= number && number <= 1000.0;
  @ ensures \is_finite(\result);
 */
float rsqrt(float number)
{
	return 1.0 / sqrt(number);
}

/* Bonus assignment; complete this specification.
 * I'm not sure to what extent this can be fully specified. Essentially what is
 * going on here is one (or two) steps of newton's iteration paired with a
 * really good initial guess (using the "magic" constant 0x5f3759df) This is
 * the best explanation I've found: http://h14s.p5r.org/2012/09/0x5f3759df.html
 * My recommended steps:
 * - First, see what you want the @ensures clause to look like, even
 *   if it can't be proved. What does the error actually look like? Assume, as
 *   above, that we can be passed in _any_ input which can result in valid
 *   output.
 * - Add an ACSL assertion for both magic step and the typecasting
 *   to describe what happens to the underlying real-valued y
 */

/*@ requires 1.0 <= number && number <= 1000.0;
  @ ensures \is_finite(\result);
 */

float q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	union { float f; i32 i; } u; // Reinterpret the bits of number as an integer
	x2 = number * 0.5F;
	u.f = number;
	u.i = 0x5f3759df - ( u.i >> 1 );         // Magic constant initial guess
	y = u.f;                                 // Cast back to float
	y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
//	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

	return y;
}

int main()
{
	float x = 42.0;
	printf("qrsqrt(%.10e) = %.10e\n", x, q_rsqrt(x));
	printf("rsqrt(%.10e) = %.10e\n", x, rsqrt(x));
	return 0;
}
