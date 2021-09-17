int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    double score_start, score_end;
    if (argc != 4) return RedisModule_WrongArity(ctx);

    if (RedisModule_StringToDouble(argv[2],&score_start) != REDISMODULE_OK ||
        RedisModule_StringToDouble(argv[3],&score_end) != REDISMODULE_OK)
    {
        return RedisModule_ReplyWithError(ctx,"ERR invalid range");
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_ZSET) {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    double scoresum_a = 0;
    double scoresum_b = 0;

    RedisModule_ZsetFirstInScoreRange(key,score_start,score_end,0,0);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum_a += score;
        RedisModule_ZsetRangeNext(key);
    }
    RedisModule_ZsetRangeStop(key);

    RedisModule_ZsetLastInScoreRange(key,score_start,score_end,0,0);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum_b += score;
        RedisModule_ZsetRangePrev(key);
    }

    RedisModule_ZsetRangeStop(key);

    RedisModule_CloseKey(key);

    RedisModule_ReplyWithArray(ctx,2);
    RedisModule_ReplyWithDouble(ctx,scoresum_a);
    RedisModule_ReplyWithDouble(ctx,scoresum_b);
    return REDISMODULE_OK;
}
