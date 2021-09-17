void redisAsyncSetTimeout(redisAsyncContext *ac, struct timeval tv) {
    if (!ac->c.timeout) {
        ac->c.timeout = calloc(1, sizeof(tv));
    }

    if (tv.tv_sec == ac->c.timeout->tv_sec &&
        tv.tv_usec == ac->c.timeout->tv_usec) {
        return;
    }

    *ac->c.timeout = tv;
}
