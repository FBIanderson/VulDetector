static int io_input (lua_State *L) {
  return g_iofile(L, IO_INPUT, "r");
}
