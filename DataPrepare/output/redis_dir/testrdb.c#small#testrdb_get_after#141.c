int testrdb_get_after(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    if (argc != 1){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    if (after_str)
        RedisModule_ReplyWithString(ctx, after_str);
    else
        RedisModule_ReplyWithStringBuffer(ctx, "", 0);
    return REDISMODULE_OK;
}
