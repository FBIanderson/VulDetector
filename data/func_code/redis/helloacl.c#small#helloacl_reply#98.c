int HelloACL_Reply(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    size_t length;

    RedisModuleString *user_string = RedisModule_GetBlockedClientPrivateData(ctx);
    const char *name = RedisModule_StringPtrLen(user_string, &length);

    if (RedisModule_AuthenticateClientWithACLUser(ctx, name, length, NULL, NULL, NULL) == 
            REDISMODULE_ERR) {
        return RedisModule_ReplyWithError(ctx, "Invalid Username or password");    
    }
    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}
