redisAsyncContext *redisAsyncConnect(const char *ip, int port) {
    redisOptions options = {0};
    REDIS_OPTIONS_SET_TCP(&options, ip, port);
    return redisAsyncConnectWithOptions(&options);
}
