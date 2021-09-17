static void dictReleaseIterator(dictIterator *iter) {
    free(iter);
}
