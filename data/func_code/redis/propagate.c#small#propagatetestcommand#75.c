int propagateTestCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModuleTimerID timer_id =
        RedisModule_CreateTimer(ctx,100,timerHandler,NULL);
    REDISMODULE_NOT_USED(timer_id);

    pthread_t tid;
    if (pthread_create(&tid,NULL,threadMain,NULL) != 0)
        return RedisModule_ReplyWithError(ctx,"-ERR Can't start thread");
    REDISMODULE_NOT_USED(tid);

    RedisModule_ReplyWithSimpleString(ctx,"OK");
    return REDISMODULE_OK;
}
