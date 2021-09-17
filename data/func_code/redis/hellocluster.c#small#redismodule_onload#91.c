int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"hellocluster",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellocluster.pingall",
        PingallCommand_RedisCommand,"readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellocluster.list",
        ListCommand_RedisCommand,"readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    /* Disable Redis Cluster sharding and redirections. This way every node
     * will be able to access every possible key, regardless of the hash slot.
     * This way the PING message handler will be able to increment a specific
     * variable. Normally you do that in order for the distributed system
     * you create as a module to have total freedom in the keyspace
     * manipulation. */
    RedisModule_SetClusterFlags(ctx,REDISMODULE_CLUSTER_FLAG_NO_REDIRECTION);

    /* Register our handlers for different message types. */
    RedisModule_RegisterClusterMessageReceiver(ctx,MSGTYPE_PING,PingReceiver);
    RedisModule_RegisterClusterMessageReceiver(ctx,MSGTYPE_PONG,PongReceiver);
    return REDISMODULE_OK;
}
