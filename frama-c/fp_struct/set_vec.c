typedef struct {
  int m, n;
  double a[32];
} Vector_N;

typedef union {
  double ijk[3];
  struct { double i, j, k; } v;
} Vector_3;

/*@
  logic integer Max(integer a, integer b) =
    a > b ? a : b;
	
  logic integer length_Vector_N(Vector_N v) =
    Max(v.m, v.n);
*/

/*@
  requires v3_read: \valid_read(v3);
  requires v_valid: \valid(v);
  requires separated_v_v3: \separated(v3, v);
  requires I_positive: 0 <= i;
  requires I_small: i+3 <= length_Vector_N(*v);
  assigns v->a[i..i+2];
  ensures set_i: v->a[i+0] == v3->v.i;
  ensures set_j: v->a[i+1] == v3->v.j;
  ensures set_k: v->a[i+2] == v3->v.k;
*/
void set_3(Vector_N* v, const Vector_3* v3, const int i) {
  v->a[i+0] = v3->v.i;
  v->a[i+1] = v3->v.j;
  v->a[i+2] = v3->v.k;
}

