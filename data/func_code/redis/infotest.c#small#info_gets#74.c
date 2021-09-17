int info_gets(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    return info_get(ctx, argv, argc, 's');
}
