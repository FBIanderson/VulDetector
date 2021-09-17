int info_getu(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    return info_get(ctx, argv, argc, 'u');
}
