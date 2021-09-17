int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"datatype",1,REDISMODULE_APIVER_1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    RedisModule_SetModuleOptions(ctx, REDISMODULE_OPTIONS_HANDLE_IO_ERRORS);

    RedisModuleTypeMethods datatype_methods = {
        .version = REDISMODULE_TYPE_METHOD_VERSION,
        .rdb_load = datatype_load,
        .rdb_save = datatype_save,
        .free = datatype_free,
    };

    datatype = RedisModule_CreateDataType(ctx, "test___dt", 1, &datatype_methods);
    if (datatype == NULL)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"datatype.set", datatype_set,"deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"datatype.get", datatype_get,"",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"datatype.restore", datatype_restore,"deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"datatype.dump", datatype_dump,"",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"datatype.swap", datatype_swap,"",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
