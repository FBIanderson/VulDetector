void shutdownCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(data);
    REDISMODULE_NOT_USED(sub);

    RedisModule_Log(ctx, "warning", "module-event-%s", "shutdown");
}
