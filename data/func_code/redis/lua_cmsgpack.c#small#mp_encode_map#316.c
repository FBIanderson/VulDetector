void mp_encode_map(lua_State *L, mp_buf *buf, int64_t n) {
    unsigned char b[5];
    int enclen;

    if (n <= 15) {
        b[0] = 0x80 | (n & 0xf);    /* fix map */
        enclen = 1;
    } else if (n <= 65535) {
        b[0] = 0xde;                /* map 16 */
        b[1] = (n & 0xff00) >> 8;
        b[2] = n & 0xff;
        enclen = 3;
    } else {
        b[0] = 0xdf;                /* map 32 */
        b[1] = (n & 0xff000000) >> 24;
        b[2] = (n & 0xff0000) >> 16;
        b[3] = (n & 0xff00) >> 8;
        b[4] = n & 0xff;
        enclen = 5;
    }
    mp_buf_append(L,buf,b,enclen);
}
