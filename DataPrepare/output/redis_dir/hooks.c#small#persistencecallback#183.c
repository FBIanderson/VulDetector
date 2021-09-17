void persistenceCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(data);

    char *keyname = NULL;
    switch (sub) {
        case REDISMODULE_SUBEVENT_PERSISTENCE_RDB_START: keyname = "persistence-rdb-start"; break;
        case REDISMODULE_SUBEVENT_PERSISTENCE_AOF_START: keyname = "persistence-aof-start"; break;
        case REDISMODULE_SUBEVENT_PERSISTENCE_SYNC_RDB_START: keyname = "persistence-syncrdb-start"; break;
        case REDISMODULE_SUBEVENT_PERSISTENCE_ENDED: keyname = "persistence-end"; break;
        case REDISMODULE_SUBEVENT_PERSISTENCE_FAILED: keyname = "persistence-failed"; break;
    }
    /* modifying the keyspace from the fork child is not an option, using log instead */
    RedisModule_Log(ctx, "warning", "module-event-%s", keyname);
    if (sub == REDISMODULE_SUBEVENT_PERSISTENCE_SYNC_RDB_START)
        LogNumericEvent(ctx, keyname, 0);
}
