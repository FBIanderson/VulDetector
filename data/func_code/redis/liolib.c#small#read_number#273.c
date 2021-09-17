static int read_number (lua_State *L, FILE *f) {
  lua_Number d;
  if (fscanf(f, LUA_NUMBER_SCAN, &d) == 1) {
    lua_pushnumber(L, d);
    return 1;
  }
  else {
    lua_pushnil(L);  /* "result" to be removed */
    return 0;  /* read fails */
  }
}
