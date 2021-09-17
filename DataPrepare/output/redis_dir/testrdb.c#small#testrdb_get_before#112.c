int testrdb_get_before(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    if (argc != 1){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    if (before_str)
        RedisModule_ReplyWithString(ctx, before_str);
    else
        RedisModule_ReplyWithStringBuffer(ctx, "", 0);
    return REDISMODULE_OK;
}
