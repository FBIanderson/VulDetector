int propagateTest3Command(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModuleCallReply *reply;

    /* This test mixes multiple propagation systems. */
    reply = RedisModule_Call(ctx, "INCR", "c!", "using-call");
    RedisModule_FreeCallReply(reply);

    RedisModule_Replicate(ctx,"INCR","c","counter-1");
    RedisModule_Replicate(ctx,"INCR","c","counter-2");

    reply = RedisModule_Call(ctx, "INCR", "c!", "after-call");
    RedisModule_FreeCallReply(reply);

    RedisModule_ReplyWithSimpleString(ctx,"OK");
    return REDISMODULE_OK;
}
