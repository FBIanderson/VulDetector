int redisCheckConnectDone(redisContext *c, int *completed) {
    int rc = connect(c->fd, (const struct sockaddr *)c->saddr, c->addrlen);
    if (rc == 0) {
        *completed = 1;
        return REDIS_OK;
    }
    switch (errno) {
    case EISCONN:
        *completed = 1;
        return REDIS_OK;
    case EALREADY:
    case EINPROGRESS:
    case EWOULDBLOCK:
        *completed = 0;
        return REDIS_OK;
    default:
        return REDIS_ERR;
    }
}
