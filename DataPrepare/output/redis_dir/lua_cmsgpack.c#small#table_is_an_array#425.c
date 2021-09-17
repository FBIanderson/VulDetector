int table_is_an_array(lua_State *L) {
    int count = 0, max = 0;
#if LUA_VERSION_NUM < 503
    lua_Number n;
#else
    lua_Integer n;
#endif

    /* Stack top on function entry */
    int stacktop;

    stacktop = lua_gettop(L);

    lua_pushnil(L);
    while(lua_next(L,-2)) {
        /* Stack: ... key value */
        lua_pop(L,1); /* Stack: ... key */
        /* The <= 0 check is valid here because we're comparing indexes. */
#if LUA_VERSION_NUM < 503
        if ((LUA_TNUMBER != lua_type(L,-1)) || (n = lua_tonumber(L, -1)) <= 0 ||
            !IS_INT_EQUIVALENT(n))
#else
        if (!lua_isinteger(L,-1) || (n = lua_tointeger(L, -1)) <= 0)
#endif
        {
            lua_settop(L, stacktop);
            return 0;
        }
        max = (n > max ? n : max);
        count++;
    }
    /* We have the total number of elements in "count". Also we have
     * the max index encountered in "max". We can't reach this code
     * if there are indexes <= 0. If you also note that there can not be
     * repeated keys into a table, you have that if max==count you are sure
     * that there are all the keys form 1 to count (both included). */
    lua_settop(L, stacktop);
    return max == count;
}
