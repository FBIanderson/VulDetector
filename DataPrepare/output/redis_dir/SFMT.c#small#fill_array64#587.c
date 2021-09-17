void fill_array64(sfmt_t *ctx, uint64_t *array, int size) {
    assert(ctx->initialized);
    assert(ctx->idx == N32);
    assert(size % 2 == 0);
    assert(size >= N64);

    gen_rand_array(ctx, (w128_t *)array, size / 2);
    ctx->idx = N32;

#if defined(BIG_ENDIAN64) && !defined(ONLY64)
    swap((w128_t *)array, size /2);
#endif
}
