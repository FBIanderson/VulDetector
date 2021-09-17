static int io_pclose (lua_State *L) {
  FILE **p = tofilep(L);
  int ok = lua_pclose(L, *p);
  *p = NULL;
  return pushresult(L, ok, NULL);
}
