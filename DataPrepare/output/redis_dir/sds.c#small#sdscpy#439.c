sds sdscpy(sds s, const char *t) {
    return sdscpylen(s, t, strlen(t));
}
