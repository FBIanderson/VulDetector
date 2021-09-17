void fill_array32(sfmt_t *ctx, uint32_t *array, int size) {
    assert(ctx->initialized);
    assert(ctx->idx == N32);
    assert(size % 4 == 0);
    assert(size >= N32);

    gen_rand_array(ctx, (w128_t *)array, size / 4);
    ctx->idx = N32;
}
