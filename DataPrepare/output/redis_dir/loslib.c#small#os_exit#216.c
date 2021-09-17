static int os_exit (lua_State *L) {
  exit(luaL_optint(L, 1, EXIT_SUCCESS));
}
