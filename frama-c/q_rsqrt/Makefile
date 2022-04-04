
q_rsqrt: q_rsqrt.c
	$(CC) -o $@ $^ -lm

#DEBUG = -wp-debug 3 -wp-verbose 3
fc-qr:
	frama-c -wp -wp-rte -wp-prover alt-ergo,gappa $(DEBUG) -wp-fct q_rsqrt q_rsqrt.c
fc-r:
	frama-c -wp -wp-rte -wp-prover alt-ergo,gappa $(DEBUG) -wp-fct rsqrt q_rsqrt.c

.PHONY: clean
clean:
	$(RM) q_rsqrt
