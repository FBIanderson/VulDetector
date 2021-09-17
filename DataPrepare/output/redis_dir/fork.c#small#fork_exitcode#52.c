int fork_exitcode(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    UNUSED(argv);
    UNUSED(argc);
    RedisModule_ReplyWithLongLong(ctx, exitted_with_code);
    return REDISMODULE_OK;
}
