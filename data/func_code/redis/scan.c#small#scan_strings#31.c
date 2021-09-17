int scan_strings(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    scan_strings_pd pd = {
        .nkeys = 0,
    };

    RedisModule_ReplyWithArray(ctx, REDISMODULE_POSTPONED_ARRAY_LEN);

    RedisModuleScanCursor* cursor = RedisModule_ScanCursorCreate();
    while(RedisModule_Scan(ctx, cursor, scan_strings_callback, &pd));
    RedisModule_ScanCursorDestroy(cursor);

    RedisModule_ReplySetArrayLength(ctx, pd.nkeys);
    return REDISMODULE_OK;
}
