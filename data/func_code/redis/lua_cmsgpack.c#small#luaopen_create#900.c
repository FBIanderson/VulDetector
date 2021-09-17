int luaopen_create(lua_State *L) {
    int i;
    /* Manually construct our module table instead of
     * relying on _register or _newlib */
    lua_newtable(L);

    for (i = 0; i < (sizeof(cmds)/sizeof(*cmds) - 1); i++) {
        lua_pushcfunction(L, cmds[i].func);
        lua_setfield(L, -2, cmds[i].name);
    }

    /* Add metadata */
    lua_pushliteral(L, LUACMSGPACK_NAME);
    lua_setfield(L, -2, "_NAME");
    lua_pushliteral(L, LUACMSGPACK_VERSION);
    lua_setfield(L, -2, "_VERSION");
    lua_pushliteral(L, LUACMSGPACK_COPYRIGHT);
    lua_setfield(L, -2, "_COPYRIGHT");
    lua_pushliteral(L, LUACMSGPACK_DESCRIPTION);
    lua_setfield(L, -2, "_DESCRIPTION");
    return 1;
}
