void redisReaderFree(redisReader *r) {
    if (r == NULL)
        return;
    if (r->reply != NULL && r->fn && r->fn->freeObject)
        r->fn->freeObject(r->reply);
    sdsfree(r->buf);
    free(r);
}
