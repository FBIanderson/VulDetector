static int f_write (lua_State *L) {
  return g_write(L, tofile(L), 2);
}
