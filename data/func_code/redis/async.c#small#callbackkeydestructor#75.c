static void callbackKeyDestructor(void *privdata, void *key) {
    ((void) privdata);
    sdsfree((sds)key);
}
