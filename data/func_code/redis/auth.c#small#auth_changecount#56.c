int Auth_ChangeCount(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    long long result = client_change_delta;
    client_change_delta = 0;
    return RedisModule_ReplyWithLongLong(ctx, result);
}
