int HelloRepl1_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModule_AutoMemory(ctx);

    /* This will be replicated *after* the two INCR statements, since
     * the Call() replication has precedence, so the actual replication
     * stream will be:
     *
     * MULTI
     * INCR foo
     * INCR bar
     * ECHO c foo
     * EXEC
     */
    RedisModule_Replicate(ctx,"ECHO","c","foo");

    /* Using the "!" modifier we replicate the command if it
     * modified the dataset in some way. */
    RedisModule_Call(ctx,"INCR","c!","foo");
    RedisModule_Call(ctx,"INCR","c!","bar");

    RedisModule_ReplyWithLongLong(ctx,0);

    return REDISMODULE_OK;
}
