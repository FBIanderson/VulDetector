static void *callbackValDup(void *privdata, const void *src) {
    ((void) privdata);
    redisCallback *dup = malloc(sizeof(*dup));
    memcpy(dup,src,sizeof(*dup));
    return dup;
}
