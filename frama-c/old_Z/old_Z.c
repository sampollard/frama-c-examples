/* frama-c -wp -wp-rte -wp-prover alt-ergo,z3,cvc4 -wp-timeout 20 -wp-fct temp old_Z.c */
/* Problem: As-is, complains about:
 *    [kernel] Parsing old_Z.c (with preprocessing)
 *     [kernel:annot-error] old_Z.c:28: Warning:
 *       term \old(ft_t) + 1 has type ℤ, but int is expected. Ignoring logic specification of function temp
 *     [kernel] User Error: warning annot-error treated as fatal error.
 *     [kernel] User Error: stopping on file "old_Z.c" that has errors. Add '-kernel-msg-key pp'
 *       for preprocessing command.
 *     [kernel] Frama-C aborted: invalid user input.
 *
 * Possible solutions:
 * (1) Use predicate sync_ft(integer old_ft) =
 * (2) ensures sync_ft((int)(\old(ft_t)+1), CALL_SET_RED);
 */
//@ghost int oracle_t;
//@ghost int ft_t;

/*@
predicate sync_ft(int old_ft) = // Solution 1.
    ft_t == old_ft + 1
    ;
*/

/*@
    requires ft_t==0;
    assigns ft_t;
    // ensures sync: sync_ft(\old(ft_t));
    ensures sync_plus_1: sync_ft(\old(ft_t) + (int) 1); // Solution (2)
    // ensures sync_1: sync_ft(1);
    ensures ft_t: ft_t == \old(ft_t) +1;
*/
void temp() {};
