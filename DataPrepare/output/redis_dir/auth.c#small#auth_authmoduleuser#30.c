int Auth_AuthModuleUser(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    uint64_t client_id;
    RedisModule_AuthenticateClientWithUser(ctx, global, UserChangedCallback, NULL, &client_id);

    return RedisModule_ReplyWithLongLong(ctx, (uint64_t) client_id);
}
