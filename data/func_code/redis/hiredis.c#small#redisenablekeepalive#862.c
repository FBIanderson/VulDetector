int redisEnableKeepAlive(redisContext *c) {
    if (redisKeepAlive(c, REDIS_KEEPALIVE_INTERVAL) != REDIS_OK)
        return REDIS_ERR;
    return REDIS_OK;
}
