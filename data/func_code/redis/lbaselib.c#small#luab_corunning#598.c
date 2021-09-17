static int luaB_corunning (lua_State *L) {
  if (lua_pushthread(L))
    lua_pushnil(L);  /* main thread is not a coroutine */
  return 1;
}
