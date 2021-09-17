void *testrdb_type_load(RedisModuleIO *rdb, int encver) {
    int count = RedisModule_LoadSigned(rdb);
    RedisModuleString *str = RedisModule_LoadString(rdb);
    float f = RedisModule_LoadFloat(rdb);
    long double ld = RedisModule_LoadLongDouble(rdb);
    if (RedisModule_IsIOError(rdb)) {
        RedisModuleCtx *ctx = RedisModule_GetContextFromIO(rdb);
        if (str)
            RedisModule_FreeString(ctx, str);
        return NULL;
    }
    /* Using the values only after checking for io errors. */
    assert(count==1);
    assert(encver==1);
    assert(f==1.5f);
    assert(ld==0.333333333333333333L);
    return str;
}
