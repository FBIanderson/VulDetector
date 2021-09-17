static int json_protect_conversion(lua_State *l)
{
    int err;

    /* Deliberately throw an error for invalid arguments */
    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    /* pcall() the function stored as upvalue(1) */
    lua_pushvalue(l, lua_upvalueindex(1));
    lua_insert(l, 1);
    err = lua_pcall(l, 1, 1, 0);
    if (!err)
        return 1;

    if (err == LUA_ERRRUN) {
        lua_pushnil(l);
        lua_insert(l, -2);
        return 2;
    }

    /* Since we are not using a custom error handler, the only remaining
     * errors are memory related */
    return luaL_error(l, "Memory allocation error in CJSON protected call");
}
