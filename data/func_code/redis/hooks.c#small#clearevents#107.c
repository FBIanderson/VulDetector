void clearEvents(RedisModuleCtx *ctx)
{
    RedisModuleString *key;
    EventElement *event;
    RedisModuleDictIter *iter = RedisModule_DictIteratorStart(event_log, "^", NULL);
    while((key = RedisModule_DictNext(ctx, iter, (void**)&event)) != NULL) {
        event->count = 0;
        event->last_val_int = 0;
        if (event->last_val_string) RedisModule_FreeString(ctx, event->last_val_string);
        event->last_val_string = NULL;
        RedisModule_DictDel(event_log, key, NULL);
        RedisModule_Free(event);
    }
    RedisModule_DictIteratorStop(iter);
}
