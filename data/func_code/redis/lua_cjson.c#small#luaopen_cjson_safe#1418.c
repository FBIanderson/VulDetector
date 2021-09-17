int luaopen_cjson_safe(lua_State *l)
{
    lua_cjson_safe_new(l);

    /* Return cjson.safe table */
    return 1;
}
