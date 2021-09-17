int HelloMoreExpire_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    if (argc != 3) return RedisModule_WrongArity(ctx);

    mstime_t addms, expire;

    if (RedisModule_StringToLongLong(argv[2],&addms) != REDISMODULE_OK)
        return RedisModule_ReplyWithError(ctx,"ERR invalid expire time");

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    expire = RedisModule_GetExpire(key);
    if (expire != REDISMODULE_NO_EXPIRE) {
        expire += addms;
        RedisModule_SetExpire(key,expire);
    }
    return RedisModule_ReplyWithSimpleString(ctx,"OK");
}
