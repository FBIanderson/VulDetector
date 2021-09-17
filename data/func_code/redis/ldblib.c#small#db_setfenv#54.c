static int db_setfenv (lua_State *L) {
  luaL_checktype(L, 2, LUA_TTABLE);
  lua_settop(L, 2);
  if (lua_setfenv(L, 1) == 0)
    luaL_error(L, LUA_QL("setfenv")
                  " cannot change environment of given object");
  return 1;
}
