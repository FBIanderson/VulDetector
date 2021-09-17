int failTest(RedisModuleCtx *ctx, const char *msg) {
    RedisModule_ReplyWithError(ctx, msg);
    return REDISMODULE_ERR;
}
