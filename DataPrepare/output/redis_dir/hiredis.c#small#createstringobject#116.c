static void *createStringObject(const redisReadTask *task, char *str, size_t len) {
    redisReply *r, *parent;
    char *buf;

    r = createReplyObject(task->type);
    if (r == NULL)
        return NULL;

    assert(task->type == REDIS_REPLY_ERROR  ||
           task->type == REDIS_REPLY_STATUS ||
           task->type == REDIS_REPLY_STRING ||
           task->type == REDIS_REPLY_VERB);

    /* Copy string value */
    if (task->type == REDIS_REPLY_VERB) {
        buf = malloc(len-4+1); /* Skip 4 bytes of verbatim type header. */
        if (buf == NULL) {
            freeReplyObject(r);
            return NULL;
        }
        memcpy(r->vtype,str,3);
        r->vtype[3] = '\0';
        memcpy(buf,str+4,len-4);
        buf[len-4] = '\0';
        r->len = len-4;
    } else {
        buf = malloc(len+1);
        if (buf == NULL) {
            freeReplyObject(r);
            return NULL;
        }
        memcpy(buf,str,len);
        buf[len] = '\0';
        r->len = len;
    }
    r->str = buf;

    if (task->parent) {
        parent = task->parent->obj;
        assert(parent->type == REDIS_REPLY_ARRAY ||
               parent->type == REDIS_REPLY_MAP ||
               parent->type == REDIS_REPLY_SET);
        parent->element[task->idx] = r;
    }
    return r;
}
