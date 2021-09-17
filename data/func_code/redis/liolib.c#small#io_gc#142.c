static int io_gc (lua_State *L) {
  FILE *f = *tofilep(L);
  /* ignore closed files */
  if (f != NULL)
    aux_close(L);
  return 0;
}
