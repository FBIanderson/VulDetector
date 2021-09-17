int RedisModule_OnUnload(RedisModuleCtx *ctx) {
    clearEvents(ctx);
    RedisModule_FreeDict(ctx, event_log);
    event_log = NULL;
    return REDISMODULE_OK;
}
