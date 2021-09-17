static int db_getfenv (lua_State *L) {
  luaL_checkany(L, 1);
  lua_getfenv(L, 1);
  return 1;
}
