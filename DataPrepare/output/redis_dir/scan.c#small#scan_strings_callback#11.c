void scan_strings_callback(RedisModuleCtx *ctx, RedisModuleString* keyname, RedisModuleKey* key, void *privdata) {
    scan_strings_pd* pd = privdata;
    int was_opened = 0;
    if (!key) {
        key = RedisModule_OpenKey(ctx, keyname, REDISMODULE_READ);
        was_opened = 1;
    }

    if (RedisModule_KeyType(key) == REDISMODULE_KEYTYPE_STRING) {
        size_t len;
        char * data = RedisModule_StringDMA(key, &len, REDISMODULE_READ);
        RedisModule_ReplyWithArray(ctx, 2);
        RedisModule_ReplyWithString(ctx, keyname);
        RedisModule_ReplyWithStringBuffer(ctx, data, len);
        pd->nkeys++;
    }
    if (was_opened)
        RedisModule_CloseKey(key);
}
