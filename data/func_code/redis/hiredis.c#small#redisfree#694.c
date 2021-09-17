void redisFree(redisContext *c) {
    if (c == NULL)
        return;
    redisNetClose(c);

    sdsfree(c->obuf);
    redisReaderFree(c->reader);
    free(c->tcp.host);
    free(c->tcp.source_addr);
    free(c->unix_sock.path);
    free(c->timeout);
    free(c->saddr);
    if (c->funcs->free_privdata) {
        c->funcs->free_privdata(c->privdata);
    }
    memset(c, 0xff, sizeof(*c));
    free(c);
}
