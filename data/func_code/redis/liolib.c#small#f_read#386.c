static int f_read (lua_State *L) {
  return g_read(L, tofile(L), 2);
}
