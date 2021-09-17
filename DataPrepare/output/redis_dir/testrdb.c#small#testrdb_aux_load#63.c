int testrdb_aux_load(RedisModuleIO *rdb, int encver, int when) {
    assert(encver == 1);
    if (conf_aux_count==1) assert(when == REDISMODULE_AUX_AFTER_RDB);
    if (conf_aux_count==0) assert(0);
    RedisModuleCtx *ctx = RedisModule_GetContextFromIO(rdb);
    if (when == REDISMODULE_AUX_BEFORE_RDB) {
        if (before_str)
            RedisModule_FreeString(ctx, before_str);
        before_str = NULL;
        int count = RedisModule_LoadSigned(rdb);
        if (RedisModule_IsIOError(rdb))
            return REDISMODULE_ERR;
        if (count)
            before_str = RedisModule_LoadString(rdb);
    } else {
        if (after_str)
            RedisModule_FreeString(ctx, after_str);
        after_str = NULL;
        int count = RedisModule_LoadSigned(rdb);
        if (RedisModule_IsIOError(rdb))
            return REDISMODULE_ERR;
        if (count)
            after_str = RedisModule_LoadString(rdb);
    }
    if (RedisModule_IsIOError(rdb))
        return REDISMODULE_ERR;
    return REDISMODULE_OK;
}
