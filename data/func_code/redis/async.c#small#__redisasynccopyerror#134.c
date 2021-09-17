static void __redisAsyncCopyError(redisAsyncContext *ac) {
    if (!ac)
        return;

    redisContext *c = &(ac->c);
    ac->err = c->err;
    ac->errstr = c->errstr;
}
