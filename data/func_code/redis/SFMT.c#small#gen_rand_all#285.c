static inline void gen_rand_all(sfmt_t *ctx) {
    int i;
    w128_t *r1, *r2;

    r1 = &ctx->sfmt[N - 2];
    r2 = &ctx->sfmt[N - 1];
    for (i = 0; i < N - POS1; i++) {
	do_recursion(&ctx->sfmt[i], &ctx->sfmt[i], &ctx->sfmt[i + POS1], r1,
	  r2);
	r1 = r2;
	r2 = &ctx->sfmt[i];
    }
    for (; i < N; i++) {
	do_recursion(&ctx->sfmt[i], &ctx->sfmt[i], &ctx->sfmt[i + POS1 - N], r1,
	  r2);
	r1 = r2;
	r2 = &ctx->sfmt[i];
    }
}
