int redisContextSetTimeout(redisContext *c, const struct timeval tv) {
    const void *to_ptr = &tv;
    size_t to_sz = sizeof(tv);
#ifdef _WIN32
    DWORD timeout_msec = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    to_ptr = &timeout_msec;
    to_sz = sizeof(timeout_msec);
#endif
    if (setsockopt(c->fd,SOL_SOCKET,SO_RCVTIMEO,to_ptr,to_sz) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_RCVTIMEO)");
        return REDIS_ERR;
    }
    if (setsockopt(c->fd,SOL_SOCKET,SO_SNDTIMEO,to_ptr,to_sz) == -1) {
        __redisSetErrorFromErrno(c,REDIS_ERR_IO,"setsockopt(SO_SNDTIMEO)");
        return REDIS_ERR;
    }
    return REDIS_OK;
}
