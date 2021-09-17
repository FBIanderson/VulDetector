int HelloLexRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 6) return RedisModule_WrongArity(ctx);

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_ZSET) {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    if (RedisModule_ZsetFirstInLexRange(key,argv[2],argv[3]) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"invalid range");
    }

    int arraylen = 0;
    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_ReplyWithString(ctx,ele);
        RedisModule_FreeString(ctx,ele);
        RedisModule_ZsetRangeNext(key);
        arraylen++;
    }
    RedisModule_ZsetRangeStop(key);
    RedisModule_ReplySetArrayLength(ctx,arraylen);
    RedisModule_CloseKey(key);
    return REDISMODULE_OK;
}
