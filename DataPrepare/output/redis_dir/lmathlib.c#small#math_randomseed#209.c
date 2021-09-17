static int math_randomseed (lua_State *L) {
  srand(luaL_checkint(L, 1));
  return 0;
}
