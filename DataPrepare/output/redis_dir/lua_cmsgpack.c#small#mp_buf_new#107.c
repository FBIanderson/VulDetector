mp_buf *mp_buf_new(lua_State *L) {
    mp_buf *buf = NULL;

    /* Old size = 0; new size = sizeof(*buf) */
    buf = (mp_buf*)mp_realloc(L, NULL, 0, sizeof(*buf));

    buf->b = NULL;
    buf->len = buf->free = 0;
    return buf;
}
