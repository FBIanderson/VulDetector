int HelloHCopy_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 4) return RedisModule_WrongArity(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_HASH &&
        type != REDISMODULE_KEYTYPE_EMPTY)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* Get the old field value. */
    RedisModuleString *oldval;
    RedisModule_HashGet(key,REDISMODULE_HASH_NONE,argv[2],&oldval,NULL);
    if (oldval) {
        RedisModule_HashSet(key,REDISMODULE_HASH_NONE,argv[3],oldval,NULL);
    }
    RedisModule_ReplyWithLongLong(ctx,oldval != NULL);
    return REDISMODULE_OK;
}
