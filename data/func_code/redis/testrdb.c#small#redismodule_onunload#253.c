int RedisModule_OnUnload(RedisModuleCtx *ctx) {
    if (before_str)
        RedisModule_FreeString(ctx, before_str);
    if (after_str)
        RedisModule_FreeString(ctx, after_str);
    return REDISMODULE_OK;
}
