sfmt_t *init_gen_rand(uint32_t seed) {
    void *p;
    sfmt_t *ctx;
    int i;
    uint32_t *psfmt32;

    if (posix_memalign(&p, sizeof(w128_t), sizeof(sfmt_t)) != 0) {
	return NULL;
    }
    ctx = (sfmt_t *)p;
    psfmt32 = &ctx->sfmt[0].u[0];

    psfmt32[idxof(0)] = seed;
    for (i = 1; i < N32; i++) {
	psfmt32[idxof(i)] = 1812433253UL * (psfmt32[idxof(i - 1)]
					    ^ (psfmt32[idxof(i - 1)] >> 30))
	    + i;
    }
    ctx->idx = N32;
    period_certification(ctx);
    ctx->initialized = 1;

    return ctx;
}
