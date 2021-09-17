int RedisModule_OnUnload(RedisModuleCtx *ctx) {
    RedisModule_FreeString(ctx, log_key_name);
    return REDISMODULE_OK;
}
