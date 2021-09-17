void FreeEvent(RedisModuleCtx *ctx, EventElement *event) {
    if (event->last_val_string)
        RedisModule_FreeString(ctx, event->last_val_string);
    RedisModule_Free(event);
}
