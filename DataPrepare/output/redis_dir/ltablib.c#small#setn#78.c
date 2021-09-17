static int setn (lua_State *L) {
  luaL_checktype(L, 1, LUA_TTABLE);
#ifndef luaL_setn
  luaL_setn(L, 1, luaL_checkint(L, 2));
#else
  luaL_error(L, LUA_QL("setn") " is obsolete");
#endif
  lua_pushvalue(L, 1);
  return 1;
}
