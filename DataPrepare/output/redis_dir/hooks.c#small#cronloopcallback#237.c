void cronLoopCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);
    REDISMODULE_NOT_USED(sub);

    RedisModuleCronLoop *ei = data;
    LogNumericEvent(ctx, "cron-loop", ei->hz);
}
