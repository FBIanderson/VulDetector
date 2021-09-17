int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"propagate-test",1,REDISMODULE_APIVER_1)
            == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"propagate-test",
                propagateTestCommand,
                "",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"propagate-test-2",
                propagateTest2Command,
                "",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"propagate-test-3",
                propagateTest3Command,
                "",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
