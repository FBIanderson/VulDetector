void LogNumericEvent(RedisModuleCtx *ctx, const char* keyname, long data) {
    REDISMODULE_NOT_USED(ctx);
    EventElement *event = RedisModule_DictGetC(event_log, (void*)keyname, strlen(keyname), NULL);
    if (!event) {
        event = RedisModule_Alloc(sizeof(EventElement));
        memset(event, 0, sizeof(EventElement));
        RedisModule_DictSetC(event_log, (void*)keyname, strlen(keyname), event);
    }
    event->last_val_int = data;
    event->count++;
}
