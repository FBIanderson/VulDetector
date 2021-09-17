static void test_invalid_timeout_errors(struct config config) {
    redisContext *c;

    test("Set error when an invalid timeout usec value is given to redisConnectWithTimeout: ");

    config.tcp.timeout.tv_sec = 0;
    config.tcp.timeout.tv_usec = 10000001;

    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);

    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
    redisFree(c);

    test("Set error when an invalid timeout sec value is given to redisConnectWithTimeout: ");

    config.tcp.timeout.tv_sec = (((LONG_MAX) - 999) / 1000) + 1;
    config.tcp.timeout.tv_usec = 0;

    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);

    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
    redisFree(c);
}
