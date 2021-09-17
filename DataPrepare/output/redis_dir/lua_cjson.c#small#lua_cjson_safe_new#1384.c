static int lua_cjson_safe_new(lua_State *l)
{
    const char *func[] = { "decode", "encode", NULL };
    int i;

    lua_cjson_new(l);

    /* Fix new() method */
    lua_pushcfunction(l, lua_cjson_safe_new);
    lua_setfield(l, -2, "new");

    for (i = 0; func[i]; i++) {
        lua_getfield(l, -1, func[i]);
        lua_pushcclosure(l, json_protect_conversion, 1);
        lua_setfield(l, -2, func[i]);
    }

    return 1;
}
