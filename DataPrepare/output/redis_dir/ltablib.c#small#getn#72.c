static int getn (lua_State *L) {
  lua_pushinteger(L, aux_getn(L, 1));
  return 1;
}
