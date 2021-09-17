static void dictRelease(dict *ht) {
    _dictClear(ht);
    free(ht);
}
