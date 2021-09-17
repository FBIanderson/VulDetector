void HelloTypeReleaseObject(struct HelloTypeObject *o) {
    struct HelloTypeNode *cur, *next;
    cur = o->head;
    while(cur) {
        next = cur->next;
        RedisModule_Free(cur);
        cur = next;
    }
    RedisModule_Free(o);
}
