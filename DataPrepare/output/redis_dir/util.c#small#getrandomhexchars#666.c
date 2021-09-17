void getRandomHexChars(char *p, size_t len) {
    char *charset = "0123456789abcdef";
    size_t j;

    getRandomBytes((unsigned char*)p,len);
    for (j = 0; j < len; j++) p[j] = charset[p[j] & 0x0F];
}
