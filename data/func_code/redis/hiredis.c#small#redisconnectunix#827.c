redisContext *redisConnectUnix(const char *path) {
    redisOptions options = {0};
    REDIS_OPTIONS_SET_UNIX(&options, path);
    return redisConnectWithOptions(&options);
}
