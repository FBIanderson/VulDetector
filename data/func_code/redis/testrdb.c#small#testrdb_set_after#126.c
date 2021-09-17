int testrdb_set_after(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    if (after_str)
        RedisModule_FreeString(ctx, after_str);
    after_str = argv[1];
    RedisModule_RetainString(ctx, argv[1]);
    RedisModule_ReplyWithLongLong(ctx, 1);
    return REDISMODULE_OK;
}
