void sdstoupper(sds s) {
    size_t len = sdslen(s), j;

    for (j = 0; j < len; j++) s[j] = toupper(s[j]);
}
