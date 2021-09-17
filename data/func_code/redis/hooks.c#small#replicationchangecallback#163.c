void replicationChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(data);

    char *keyname = (sub == REDISMODULE_SUBEVENT_REPLICA_CHANGE_ONLINE) ?
        "replica-online" : "replica-offline";
    LogNumericEvent(ctx, keyname, 0);
}
