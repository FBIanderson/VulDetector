int HelloTypeBRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 5) return RedisModule_WrongArity(ctx);
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_EMPTY &&
        RedisModule_ModuleTypeGetType(key) != HelloType)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* Parse the timeout before even trying to serve the client synchronously,
     * so that we always fail ASAP on syntax errors. */
    long long timeout;
    if (RedisModule_StringToLongLong(argv[4],&timeout) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,
            "ERR invalid timeout parameter");
    }

    /* Can we serve the reply synchronously? */
    if (type != REDISMODULE_KEYTYPE_EMPTY) {
        return HelloTypeRange_RedisCommand(ctx,argv,argc-1);
    }

    /* Otherwise let's block on the key. */
    void *privdata = RedisModule_Alloc(100);
    RedisModule_BlockClientOnKeys(ctx,HelloBlock_Reply,HelloBlock_Timeout,HelloBlock_FreeData,timeout,argv+1,1,privdata);
    return REDISMODULE_OK;
}
