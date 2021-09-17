int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"hellodict",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellodict.set",
        cmd_SET,"write deny-oom",1,1,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellodict.get",
        cmd_GET,"readonly",1,1,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellodict.keyrange",
        cmd_KEYRANGE,"readonly",1,1,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    /* Create our global dictionray. Here we'll set our keys and values. */
    Keyspace = RedisModule_CreateDict(NULL);

    return REDISMODULE_OK;
}
