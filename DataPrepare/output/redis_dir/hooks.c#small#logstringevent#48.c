void LogStringEvent(RedisModuleCtx *ctx, const char* keyname, const char* data) {
    EventElement *event = RedisModule_DictGetC(event_log, (void*)keyname, strlen(keyname), NULL);
    if (!event) {
        event = RedisModule_Alloc(sizeof(EventElement));
        memset(event, 0, sizeof(EventElement));
        RedisModule_DictSetC(event_log, (void*)keyname, strlen(keyname), event);
    }
    if (event->last_val_string) RedisModule_FreeString(ctx, event->last_val_string);
    event->last_val_string = RedisModule_CreateString(ctx, data, strlen(data));
    event->count++;
}
