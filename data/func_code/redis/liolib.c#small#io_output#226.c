static int io_output (lua_State *L) {
  return g_iofile(L, IO_OUTPUT, "w");
}
