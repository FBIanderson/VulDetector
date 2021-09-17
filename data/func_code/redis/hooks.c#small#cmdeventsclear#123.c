int cmdEventsClear(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argc);
    REDISMODULE_NOT_USED(argv);
    clearEvents(ctx);
    return REDISMODULE_OK;
}
