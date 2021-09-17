int RevokeCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (global_auth_client_id) {
        RedisModule_DeauthenticateAndCloseClient(ctx, global_auth_client_id);
        return RedisModule_ReplyWithSimpleString(ctx, "OK");
    } else {
        return RedisModule_ReplyWithError(ctx, "Global user currently not used");    
    }
}
