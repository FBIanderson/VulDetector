void roleChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(data);

    RedisModuleReplicationInfo *ri = data;
    char *keyname = (sub == REDISMODULE_EVENT_REPLROLECHANGED_NOW_MASTER) ?
        "role-master" : "role-replica";
    LogStringEvent(ctx, keyname, ri->masterhost);
}
