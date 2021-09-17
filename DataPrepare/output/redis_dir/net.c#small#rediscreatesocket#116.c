static int redisCreateSocket(redisContext *c, int type) {
    redisFD s;
    if ((s = socket(type, SOCK_STREAM, 0)) == REDIS_INVALID_FD) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,NULL);
        return REDIS_ERR;
    }
    c->fd = s;
    if (type == AF_INET) {
        if (redisSetReuseAddr(c) == REDIS_ERR) {
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}
