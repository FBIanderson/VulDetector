static int loader_Croot (lua_State *L) {
  const char *funcname;
  const char *filename;
  const char *name = luaL_checkstring(L, 1);
  const char *p = strchr(name, '.');
  int stat;
  if (p == NULL) return 0;  /* is root */
  lua_pushlstring(L, name, p - name);
  filename = findfile(L, lua_tostring(L, -1), "cpath");
  if (filename == NULL) return 1;  /* root not found */
  funcname = mkfuncname(L, name);
  if ((stat = ll_loadfunc(L, filename, funcname)) != 0) {
    if (stat != ERRFUNC) loaderror(L, filename);  /* real error */
    lua_pushfstring(L, "\n\tno module " LUA_QS " in file " LUA_QS,
                       name, filename);
    return 1;  /* function not found */
  }
  return 1;
}
