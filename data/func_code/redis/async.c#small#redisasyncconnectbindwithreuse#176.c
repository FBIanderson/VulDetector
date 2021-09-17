redisAsyncContext *redisAsyncConnectBindWithReuse(const char *ip, int port,
                                                  const char *source_addr) {
    redisOptions options = {0};
    REDIS_OPTIONS_SET_TCP(&options, ip, port);
    options.options |= REDIS_OPT_REUSEADDR;
    options.endpoint.tcp.source_addr = source_addr;
    return redisAsyncConnectWithOptions(&options);
}
