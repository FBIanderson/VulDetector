void luaC_callGCTM (lua_State *L) {
  while (G(L)->tmudata)
    GCTM(L);
}
