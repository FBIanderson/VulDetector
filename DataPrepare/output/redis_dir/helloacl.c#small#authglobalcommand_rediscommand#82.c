int AuthGlobalCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (global_auth_client_id) {
        return RedisModule_ReplyWithError(ctx, "Global user currently used");    
    }

    RedisModule_AuthenticateClientWithUser(ctx, global, HelloACL_UserChanged, NULL, &global_auth_client_id);

    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}
