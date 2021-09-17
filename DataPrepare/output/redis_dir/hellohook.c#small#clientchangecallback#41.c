void clientChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(ctx);
    REDISMODULE_NOT_USED(e);

    RedisModuleClientInfo *ci = data;
    printf("Client %s event for client #%llu %s:%d\n",
        (sub == REDISMODULE_SUBEVENT_CLIENT_CHANGE_CONNECTED) ?
            "connection" : "disconnection",
        ci->id,ci->addr,ci->port);
}
