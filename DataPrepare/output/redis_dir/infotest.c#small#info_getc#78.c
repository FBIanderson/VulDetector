int info_getc(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    return info_get(ctx, argv, argc, 'c');
}
