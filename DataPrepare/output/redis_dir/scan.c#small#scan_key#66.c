int scan_key(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 2) {
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }
    scan_key_pd pd = {
        .ctx = ctx,
        .nreplies = 0,
    };

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_READ);
    if (!key) {
        RedisModule_ReplyWithError(ctx, "not found");
        return REDISMODULE_OK;
    }

    RedisModule_ReplyWithArray(ctx, REDISMODULE_POSTPONED_ARRAY_LEN);

    RedisModuleScanCursor* cursor = RedisModule_ScanCursorCreate();
    while(RedisModule_ScanKey(key, cursor, scan_key_callback, &pd));
    RedisModule_ScanCursorDestroy(cursor);

    RedisModule_ReplySetArrayLength(ctx, pd.nreplies);
    RedisModule_CloseKey(key);
    return REDISMODULE_OK;
}
