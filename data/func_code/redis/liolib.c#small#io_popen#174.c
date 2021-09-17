static int io_popen (lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  const char *mode = luaL_optstring(L, 2, "r");
  FILE **pf = newfile(L);
  *pf = lua_popen(L, filename, mode);
  return (*pf == NULL) ? pushresult(L, 0, filename) : 1;
}
