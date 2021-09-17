int test_setlru(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc<3) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    RedisModuleKey *key = open_key_or_reply(ctx, argv[1], REDISMODULE_READ|REDISMODULE_OPEN_KEY_NOTOUCH);
    mstime_t lru;
    if (RedisModule_StringToLongLong(argv[2], &lru) != REDISMODULE_OK) {
        RedisModule_ReplyWithError(ctx, "invalid idle time");
        return REDISMODULE_OK;
    }
    int was_set = RedisModule_SetLRU(key, lru)==REDISMODULE_OK;
    RedisModule_ReplyWithLongLong(ctx, was_set);
    RedisModule_CloseKey(key);
    return REDISMODULE_OK;
}
