void *sdsAllocPtr(sds s) {
    return (void*) (s-sdsHdrSize(s[-1]));
}
