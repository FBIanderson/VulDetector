sds sdscatsds(sds s, const sds t) {
    return sdscatlen(s, t, sdslen(t));
}
