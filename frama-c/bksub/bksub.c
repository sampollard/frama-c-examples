/* Assignment:
 *   1. Make some reasonable specification that can be proven with -wp
 *   OR
 *   2. Write a test case using frama-c's nondeterministic input generator to
 *      try to find situations where lu_bksb doesn't work.
 */
static void lu_bksb(
		double *a,		/* LU Decomposition of original a matrix */
		int n,			/* dim of the square matrix a */
		int *indx,		/* records the row pivoting */
		double *b)
{
	int i, ii = -1, ip, j;
	double sum;

	for (i = 0; i < n; i ++) {
		ip = indx[i];
		sum = b[ip];
		b[ip] = b[i];
		if (ii != -1) {
			for (j= ii; j <= i - 1; j++)
				sum -= a[i*n+j]*b[j];
		}
		else {
			if (sum) ii = i;
		}
		b[i] = sum;
	}
	for (i = n-1; i >= 0; i --) {
		sum = b[i];
		for (j= i + 1; j < n; j++)
			sum -= a[i*n+j]*b[j];
		b[i] = sum/a[i*n+i];
	}
}

int main(int argc, char *argv[])
{
	/* LU decomposition of the matrix
      A = [1, 2, 3] = L * U
          [4, 5, 6]
          [7, 8, 9]
	   L = [1, 0, 0]  U = [1,  2,  3]
	       [4, 1, 0]      [0, -3, -6]
	       [7, 2, 1]      [0,  0,  0]
      Note that A is noninvertible here (3rd diagonal of U = 0)
	*/
	int n = 3;
	double A[9] =
	    {1.,  2.,  3.,
         4., -3., -6.,
         7.,  2.,  0.};
	int indx[3] = {0, 1, 2}; // assume no row pivoting was done
	double b[3] = {1., 1., 1.};
	lu_bksb(A, n, indx, b);
	return 0;
}
