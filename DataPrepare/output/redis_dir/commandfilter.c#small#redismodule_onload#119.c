int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"commandfilter",1,REDISMODULE_APIVER_1)
            == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (argc != 2) {
        RedisModule_Log(ctx, "warning", "Log key name not specified");
        return REDISMODULE_ERR;
    }

    long long noself = 0;
    log_key_name = RedisModule_CreateStringFromString(ctx, argv[0]);
    RedisModule_StringToLongLong(argv[1], &noself);

    if (RedisModule_CreateCommand(ctx,log_command_name,
                CommandFilter_LogCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,ping_command_name,
                CommandFilter_PingCommand,"deny-oom",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,unregister_command_name,
                CommandFilter_UnregisterCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if ((filter = RedisModule_RegisterCommandFilter(ctx, CommandFilter_CommandFilter, 
                    noself ? REDISMODULE_CMDFILTER_NOSELF : 0))
            == NULL) return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
