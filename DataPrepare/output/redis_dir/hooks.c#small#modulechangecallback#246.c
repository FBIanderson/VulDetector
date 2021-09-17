void moduleChangeCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);

    RedisModuleModuleChange *ei = data;
    char *keyname = (sub == REDISMODULE_SUBEVENT_MODULE_LOADED) ?
        "module-loaded" : "module-unloaded";
    LogStringEvent(ctx, keyname, ei->module_name);
}
