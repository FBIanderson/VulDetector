redisFD redisFreeKeepFd(redisContext *c) {
    redisFD fd = c->fd;
    c->fd = REDIS_INVALID_FD;
    redisFree(c);
    return fd;
}
