static redisContext *redisContextInit(const redisOptions *options) {
    redisContext *c;

    c = calloc(1, sizeof(*c));
    if (c == NULL)
        return NULL;

    c->funcs = &redisContextDefaultFuncs;
    c->obuf = sdsempty();
    c->reader = redisReaderCreate();
    c->fd = REDIS_INVALID_FD;

    if (c->obuf == NULL || c->reader == NULL) {
        redisFree(c);
        return NULL;
    }
    (void)options; /* options are used in other functions */
    return c;
}
