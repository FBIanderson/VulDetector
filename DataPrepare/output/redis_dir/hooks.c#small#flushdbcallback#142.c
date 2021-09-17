void flushdbCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);

    RedisModuleFlushInfo *fi = data;
    char *keyname = (sub == REDISMODULE_SUBEVENT_FLUSHDB_START) ?
        "flush-start" : "flush-end";
    LogNumericEvent(ctx, keyname, fi->dbnum);
}
