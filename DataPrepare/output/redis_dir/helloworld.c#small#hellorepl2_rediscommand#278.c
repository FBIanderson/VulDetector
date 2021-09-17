int HelloRepl2_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);

    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);

    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_LIST)
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);

    size_t listlen = RedisModule_ValueLength(key);
    long long sum = 0;

    /* Rotate and increment. */
    while(listlen--) {
        RedisModuleString *ele = RedisModule_ListPop(key,REDISMODULE_LIST_TAIL);
        long long val;
        if (RedisModule_StringToLongLong(ele,&val) != REDISMODULE_OK) val = 0;
        val++;
        sum += val;
        RedisModuleString *newele = RedisModule_CreateStringFromLongLong(ctx,val);
        RedisModule_ListPush(key,REDISMODULE_LIST_HEAD,newele);
    }
    RedisModule_ReplyWithLongLong(ctx,sum);
    RedisModule_ReplicateVerbatim(ctx);
    return REDISMODULE_OK;
}
