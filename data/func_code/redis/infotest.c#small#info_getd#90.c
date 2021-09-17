int info_getd(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    return info_get(ctx, argv, argc, 'd');
}
