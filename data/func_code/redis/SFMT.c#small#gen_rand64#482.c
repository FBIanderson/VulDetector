uint64_t gen_rand64(sfmt_t *ctx) {
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    uint32_t r1, r2;
    uint32_t *psfmt32 = &ctx->sfmt[0].u[0];
#else
    uint64_t r;
    uint64_t *psfmt64 = (uint64_t *)&ctx->sfmt[0].u[0];
#endif

    assert(ctx->initialized);
    assert(ctx->idx % 2 == 0);

    if (ctx->idx >= N32) {
	gen_rand_all(ctx);
	ctx->idx = 0;
    }
#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    r1 = psfmt32[ctx->idx];
    r2 = psfmt32[ctx->idx + 1];
    ctx->idx += 2;
    return ((uint64_t)r2 << 32) | r1;
#else
    r = psfmt64[ctx->idx / 2];
    ctx->idx += 2;
    return r;
#endif
}
