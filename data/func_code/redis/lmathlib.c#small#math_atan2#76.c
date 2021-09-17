static int math_atan2 (lua_State *L) {
  lua_pushnumber(L, atan2(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
  return 1;
}
