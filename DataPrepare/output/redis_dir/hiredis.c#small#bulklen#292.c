static size_t bulklen(size_t len) {
    return 1+countDigits(len)+2+len+2;
}
