static void *createDoubleObject(const redisReadTask *task, double value, char *str, size_t len) {
    redisReply *r, *parent;

    r = createReplyObject(REDIS_REPLY_DOUBLE);
    if (r == NULL)
        return NULL;

    r->dval = value;
    r->str = malloc(len+1);
    if (r->str == NULL) {
        freeReplyObject(r);
        return NULL;
    }

    /* The double reply also has the original protocol string representing a
     * double as a null terminated string. This way the caller does not need
     * to format back for string conversion, especially since Redis does efforts
     * to make the string more human readable avoiding the calssical double
     * decimal string conversion artifacts. */
    memcpy(r->str, str, len);
    r->str[len] = '\0';

    if (task->parent) {
        parent = task->parent->obj;
        assert(parent->type == REDIS_REPLY_ARRAY ||
               parent->type == REDIS_REPLY_MAP ||
               parent->type == REDIS_REPLY_SET);
        parent->element[task->idx] = r;
    }
    return r;
}
