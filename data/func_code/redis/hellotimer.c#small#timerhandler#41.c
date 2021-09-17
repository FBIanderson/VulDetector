void timerHandler(RedisModuleCtx *ctx, void *data) {
    REDISMODULE_NOT_USED(ctx);
    printf("Fired %s!\n", data);
    RedisModule_Free(data);
}
