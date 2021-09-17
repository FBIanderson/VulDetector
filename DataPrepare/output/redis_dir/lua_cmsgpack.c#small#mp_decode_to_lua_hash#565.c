void mp_decode_to_lua_hash(lua_State *L, mp_cur *c, size_t len) {
    assert(len <= UINT_MAX);
    lua_newtable(L);
    while(len--) {
        mp_decode_to_lua_type(L,c); /* key */
        if (c->err) return;
        mp_decode_to_lua_type(L,c); /* value */
        if (c->err) return;
        lua_settable(L,-3);
    }
}
