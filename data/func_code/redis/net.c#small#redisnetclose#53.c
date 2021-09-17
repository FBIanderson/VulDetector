void redisNetClose(redisContext *c) {
    if (c && c->fd != REDIS_INVALID_FD) {
        close(c->fd);
        c->fd = REDIS_INVALID_FD;
    }
}
