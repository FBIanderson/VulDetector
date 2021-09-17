void sdsupdatelen(sds s) {
    int reallen = strlen(s);
    sdssetlen(s, reallen);
}
