/* Run with
 * frama-c -wp -wp-rte -wp-prover alt-ergo,z3,cvc4 -wp-status-all -wp-timeout 10  simple-list.c
 * In frama-c you cannot convert from array -> pointer, but you can convert pointer -> array (explicitly)
 */
#include <stdio.h>
typedef enum status {EMPTY, CLEAR, RESET, VALID};

enum status empty[] = {EMPTY, EMPTY, EMPTY, EMPTY};
enum status reset[] = {RESET, RESET, RESET, RESET};


/*@
type invariant isStatus(enum status s) =
  s == EMPTY || s == CLEAR || s == RESET || s == VALID ;

predicate check_value(enum status *p, enum status *value) =
    p[0]==value[0] && p[1]==value[1] && p[2]==value[2] && p[3]==value[3];
*/


/*@
    requires \valid(k+ (0..3));
    ensures k_RESET: \forall int i; 0<=i<=3 && k[i]==RESET;
    ensures k_RESET_num: \forall int i; 0<=i<=3 && k[i]==2;
    ensures error_k_RESET: \forall int i; 0<=i<=3 && k[i]==EMPTY;
    ensures check_value: check_value(&k[0], &reset[0]);
    ensures error_check_value: check_value(&k[0], &empty[0]);
*/
void set_k(enum status k[]) {
	
	/* Somehow, frama-c now reinterprets k to have type (enum status *) */
    for (int i=0; i<4; i++){
        k[i] = RESET;
        //@assert k[i]==RESET;
        printf("%u\n",k[i]);
    }
    //@check k[2]==RESET;
}
/*@
    assigns \nothing;
*/
int main(){
    enum status k[] = {EMPTY, EMPTY, EMPTY, EMPTY};
    set_k(k);
}

