void *threadMain(void *arg) {
    REDISMODULE_NOT_USED(arg);
    RedisModuleCtx *ctx = RedisModule_GetThreadSafeContext(NULL);
    RedisModule_SelectDb(ctx,9); /* Tests ran in database number 9. */
    for (int i = 0; i < 10; i++) {
        RedisModule_ThreadSafeContextLock(ctx);
        RedisModule_Replicate(ctx,"INCR","c","a-from-thread");
        RedisModule_Replicate(ctx,"INCR","c","b-from-thread");
        RedisModule_ThreadSafeContextUnlock(ctx);
    }
    RedisModule_FreeThreadSafeContext(ctx);
    return NULL;
}
