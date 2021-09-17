int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"testhook",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    /* replication related hooks */
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ReplicationRoleChanged, roleChangeCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ReplicaChange, replicationChangeCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_MasterLinkChange, rasterLinkChangeCallback);

    /* persistence related hooks */
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_Persistence, persistenceCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_Loading, loadingCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_LoadingProgress, loadingProgressCallback);

    /* other hooks */
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ClientChange, clientChangeCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_FlushDB, flushdbCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_Shutdown, shutdownCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_CronLoop, cronLoopCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ModuleChange, moduleChangeCallback);

    event_log = RedisModule_CreateDict(ctx);

    if (RedisModule_CreateCommand(ctx,"hooks.event_count", cmdEventCount,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    if (RedisModule_CreateCommand(ctx,"hooks.event_last", cmdEventLast,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    if (RedisModule_CreateCommand(ctx,"hooks.clear", cmdEventsClear,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}
