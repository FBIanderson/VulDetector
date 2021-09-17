static int luaB_getfenv (lua_State *L) {
  getfunc(L, 1);
  if (lua_iscfunction(L, -1))  /* is a C function? */
    lua_pushvalue(L, LUA_GLOBALSINDEX);  /* return the thread's global env. */
  else
    lua_getfenv(L, -1);
  return 1;
}
