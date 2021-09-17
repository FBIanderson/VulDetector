int propagateTest2Command(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    /* Replicate two commands to test MULTI/EXEC wrapping. */
    RedisModule_Replicate(ctx,"INCR","c","counter-1");
    RedisModule_Replicate(ctx,"INCR","c","counter-2");
    RedisModule_ReplyWithSimpleString(ctx,"OK");
    return REDISMODULE_OK;
}
