sds sdsdup(const sds s) {
    return sdsnewlen(s, sdslen(s));
}
