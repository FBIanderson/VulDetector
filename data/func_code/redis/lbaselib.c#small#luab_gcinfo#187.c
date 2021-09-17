static int luaB_gcinfo (lua_State *L) {
  lua_pushinteger(L, lua_getgccount(L));
  return 1;
}
