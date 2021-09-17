redisReader *redisReaderCreateWithFunctions(redisReplyObjectFunctions *fn) {
    redisReader *r;

    r = calloc(1,sizeof(redisReader));
    if (r == NULL)
        return NULL;

    r->fn = fn;
    r->buf = sdsempty();
    r->maxbuf = REDIS_READER_MAX_BUF;
    if (r->buf == NULL) {
        free(r);
        return NULL;
    }

    r->ridx = -1;
    return r;
}
