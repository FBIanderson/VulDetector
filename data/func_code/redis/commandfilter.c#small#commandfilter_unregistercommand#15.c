int CommandFilter_UnregisterCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    (void) argc;
    (void) argv;

    RedisModule_ReplyWithLongLong(ctx,
            RedisModule_UnregisterCommandFilter(ctx, filter));

    return REDISMODULE_OK;
}
