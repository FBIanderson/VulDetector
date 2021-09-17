uint64_t dictGetHash(dict *d, const void *key) {
    return dictHashKey(d, key);
}
