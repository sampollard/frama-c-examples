FCT:=norm
WP:=-wp -wp-rte -wp-no-warn-memory-model -wp-fct $(FCT)

norm:
	frama-c $(WP) norm.c

nan_real:
	frama-c -wp -wp-rte -wp-model +real nan.c

nan_float:
	frama-c -wp -wp-rte nan.c

square:
	frama-c -wp -wp-rte -wp-prover alt-ergo,gappa square.c

clean:
	rm -rf *.o
