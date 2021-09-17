void clientChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);

    RedisModuleClientInfo *ci = data;
    char *keyname = (sub == REDISMODULE_SUBEVENT_CLIENT_CHANGE_CONNECTED) ?
        "client-connected" : "client-disconnected";
    LogNumericEvent(ctx, keyname, ci->id);
}
