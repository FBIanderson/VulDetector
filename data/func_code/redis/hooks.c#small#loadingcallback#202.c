void loadingCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(data);

    char *keyname = NULL;
    switch (sub) {
        case REDISMODULE_SUBEVENT_LOADING_RDB_START: keyname = "loading-rdb-start"; break;
        case REDISMODULE_SUBEVENT_LOADING_AOF_START: keyname = "loading-aof-start"; break;
        case REDISMODULE_SUBEVENT_LOADING_REPL_START: keyname = "loading-repl-start"; break;
        case REDISMODULE_SUBEVENT_LOADING_ENDED: keyname = "loading-end"; break;
        case REDISMODULE_SUBEVENT_LOADING_FAILED: keyname = "loading-failed"; break;
    }
    LogNumericEvent(ctx, keyname, 0);
}
