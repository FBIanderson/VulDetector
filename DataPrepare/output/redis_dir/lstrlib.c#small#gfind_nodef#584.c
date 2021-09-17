static int gfind_nodef (lua_State *L) {
  return luaL_error(L, LUA_QL("string.gfind") " was renamed to "
                       LUA_QL("string.gmatch"));
}
