struct HelloTypeObject *createHelloTypeObject(void) {
    struct HelloTypeObject *o;
    o = RedisModule_Alloc(sizeof(*o));
    o->head = NULL;
    o->len = 0;
    return o;
}
