void rasterLinkChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(data);

    char *keyname = (sub == REDISMODULE_SUBEVENT_MASTER_LINK_UP) ?
        "masterlink-up" : "masterlink-down";
    LogNumericEvent(ctx, keyname, 0);
}
