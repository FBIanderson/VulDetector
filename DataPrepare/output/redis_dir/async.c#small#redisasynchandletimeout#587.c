void redisAsyncHandleTimeout(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    redisCallback cb;

    if ((c->flags & REDIS_CONNECTED) && ac->replies.head == NULL) {
        /* Nothing to do - just an idle timeout */
        return;
    }

    if (!c->err) {
        __redisSetError(c, REDIS_ERR_TIMEOUT, "Timeout");
    }

    if (!(c->flags & REDIS_CONNECTED) && ac->onConnect) {
        ac->onConnect(ac, REDIS_ERR);
    }

    while (__redisShiftCallback(&ac->replies, &cb) == REDIS_OK) {
        __redisRunCallback(ac, &cb, NULL);
    }

    /**
     * TODO: Don't automatically sever the connection,
     * rather, allow to ignore <x> responses before the queue is clear
     */
    __redisAsyncDisconnect(ac);
}
