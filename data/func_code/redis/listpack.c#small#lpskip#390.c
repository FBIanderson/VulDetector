unsigned char *lpSkip(unsigned char *p) {
    unsigned long entrylen = lpCurrentEncodedSize(p);
    entrylen += lpEncodeBacklen(NULL,entrylen);
    p += entrylen;
    return p;
}
