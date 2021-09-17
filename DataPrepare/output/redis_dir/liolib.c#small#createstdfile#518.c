static void createstdfile (lua_State *L, FILE *f, int k, const char *fname) {
  *newfile(L) = f;
  if (k > 0) {
    lua_pushvalue(L, -1);
    lua_rawseti(L, LUA_ENVIRONINDEX, k);
  }
  lua_pushvalue(L, -2);  /* copy environment */
  lua_setfenv(L, -2);  /* set it */
  lua_setfield(L, -3, fname);
}
