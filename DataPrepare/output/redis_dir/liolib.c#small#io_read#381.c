static int io_read (lua_State *L) {
  return g_read(L, getiofile(L, IO_INPUT), 1);
}
