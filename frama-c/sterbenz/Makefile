FCT:=sterbenz
WP:=-wp -wp-rte -wp-no-warn-memory-model -wp-fct $(FCT) -wp-prover alt-ergo,gappa

wp:
	frama-c $(WP) sterbenz.c

clean:
	rm -rf *.o

