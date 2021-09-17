int test_getlfu(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc<2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    RedisModuleKey *key = open_key_or_reply(ctx, argv[1], REDISMODULE_READ|REDISMODULE_OPEN_KEY_NOTOUCH);
    mstime_t lfu;
    RedisModule_GetLFU(key, &lfu);
    RedisModule_ReplyWithLongLong(ctx, lfu);
    RedisModule_CloseKey(key);
    return REDISMODULE_OK;
}
