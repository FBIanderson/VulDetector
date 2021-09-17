int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"hellotype",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    RedisModuleTypeMethods tm = {
        .version = REDISMODULE_TYPE_METHOD_VERSION,
        .rdb_load = HelloTypeRdbLoad,
        .rdb_save = HelloTypeRdbSave,
        .aof_rewrite = HelloTypeAofRewrite,
        .mem_usage = HelloTypeMemUsage,
        .free = HelloTypeFree,
        .digest = HelloTypeDigest
    };

    HelloType = RedisModule_CreateDataType(ctx,"hellotype",0,&tm);
    if (HelloType == NULL) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellotype.insert",
        HelloTypeInsert_RedisCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellotype.range",
        HelloTypeRange_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellotype.len",
        HelloTypeLen_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellotype.brange",
        HelloTypeBRange_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
