static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
    int completed = 0;
    redisContext *c = &(ac->c);
    if (redisCheckConnectDone(c, &completed) == REDIS_ERR) {
        /* Error! */
        redisCheckSocketError(c);
        if (ac->onConnect) ac->onConnect(ac, REDIS_ERR);
        __redisAsyncDisconnect(ac);
        return REDIS_ERR;
    } else if (completed == 1) {
        /* connected! */
        if (ac->onConnect) ac->onConnect(ac, REDIS_OK);
        c->flags |= REDIS_CONNECTED;
        return REDIS_OK;
    } else {
        return REDIS_OK;
    }
}
