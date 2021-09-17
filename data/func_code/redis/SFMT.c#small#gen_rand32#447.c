uint32_t gen_rand32(sfmt_t *ctx) {
    uint32_t r;
    uint32_t *psfmt32 = &ctx->sfmt[0].u[0];

    assert(ctx->initialized);
    if (ctx->idx >= N32) {
	gen_rand_all(ctx);
	ctx->idx = 0;
    }
    r = psfmt32[ctx->idx++];
    return r;
}
