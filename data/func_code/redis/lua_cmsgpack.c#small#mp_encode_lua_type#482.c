void mp_encode_lua_type(lua_State *L, mp_buf *buf, int level) {
    int t = lua_type(L,-1);

    /* Limit the encoding of nested tables to a specified maximum depth, so that
     * we survive when called against circular references in tables. */
    if (t == LUA_TTABLE && level == LUACMSGPACK_MAX_NESTING) t = LUA_TNIL;
    switch(t) {
    case LUA_TSTRING: mp_encode_lua_string(L,buf); break;
    case LUA_TBOOLEAN: mp_encode_lua_bool(L,buf); break;
    case LUA_TNUMBER:
    #if LUA_VERSION_NUM < 503
        mp_encode_lua_number(L,buf); break;
    #else
        if (lua_isinteger(L, -1)) {
            mp_encode_lua_integer(L, buf);
        } else {
            mp_encode_lua_number(L, buf);
        }
        break;
    #endif
    case LUA_TTABLE: mp_encode_lua_table(L,buf,level); break;
    default: mp_encode_lua_null(L,buf); break;
    }
    lua_pop(L,1);
}
