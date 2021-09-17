int AuthAsyncCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);

    pthread_t tid;
    RedisModuleBlockedClient *bc = RedisModule_BlockClient(ctx, HelloACL_Reply, HelloACL_Timeout, HelloACL_FreeData, TIMEOUT_TIME);
    

    void **targs = RedisModule_Alloc(sizeof(void*)*2);
    targs[0] = bc;
    targs[1] = RedisModule_CreateStringFromString(NULL, argv[1]);

    if (pthread_create(&tid, NULL, HelloACL_ThreadMain, targs) != 0) {
        RedisModule_AbortBlock(bc);
        return RedisModule_ReplyWithError(ctx, "-ERR Can't start thread");
    }

    return REDISMODULE_OK;
}
