static int str_lower (lua_State *L) {
  size_t l;
  size_t i;
  luaL_Buffer b;
  const char *s = luaL_checklstring(L, 1, &l);
  luaL_buffinit(L, &b);
  for (i=0; i<l; i++)
    luaL_addchar(&b, tolower(uchar(s[i])));
  luaL_pushresult(&b);
  return 1;
}
