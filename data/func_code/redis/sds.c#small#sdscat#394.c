sds sdscat(sds s, const char *t) {
    return sdscatlen(s, t, strlen(t));
}
