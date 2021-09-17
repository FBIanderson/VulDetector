int mp_unpack_limit(lua_State *L) {
    int limit = luaL_checkinteger(L, 2);
    int offset = luaL_optinteger(L, 3, 0);
    /* Variable pop because offset may not exist */
    lua_pop(L, lua_gettop(L)-1);

    return mp_unpack_full(L, limit, offset);
}
