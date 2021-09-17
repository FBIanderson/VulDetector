redisAsyncContext *redisAsyncConnectWithOptions(const redisOptions *options) {
    redisOptions myOptions = *options;
    redisContext *c;
    redisAsyncContext *ac;

    myOptions.options |= REDIS_OPT_NONBLOCK;
    c = redisConnectWithOptions(&myOptions);
    if (c == NULL) {
        return NULL;
    }
    ac = redisAsyncInitialize(c);
    if (ac == NULL) {
        redisFree(c);
        return NULL;
    }
    __redisAsyncCopyError(ac);
    return ac;
}
