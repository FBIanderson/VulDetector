int Auth_AuthRealUser(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);

    size_t length;
    uint64_t client_id;

    RedisModuleString *user_string = argv[1];
    const char *name = RedisModule_StringPtrLen(user_string, &length);

    if (RedisModule_AuthenticateClientWithACLUser(ctx, name, length, 
            UserChangedCallback, NULL, &client_id) == REDISMODULE_ERR) {
        return RedisModule_ReplyWithError(ctx, "Invalid user");   
    }

    return RedisModule_ReplyWithLongLong(ctx, (uint64_t) client_id);
}
