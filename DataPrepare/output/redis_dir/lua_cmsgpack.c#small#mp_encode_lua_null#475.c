void mp_encode_lua_null(lua_State *L, mp_buf *buf) {
    unsigned char b[1];

    b[0] = 0xc0;
    mp_buf_append(L,buf,b,1);
}
