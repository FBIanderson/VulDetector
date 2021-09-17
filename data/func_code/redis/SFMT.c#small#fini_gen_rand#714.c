void fini_gen_rand(sfmt_t *ctx) {
    assert(ctx != NULL);

    ctx->initialized = 0;
    free(ctx);
}
