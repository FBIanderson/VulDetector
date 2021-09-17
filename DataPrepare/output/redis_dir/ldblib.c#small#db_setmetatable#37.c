static int db_setmetatable (lua_State *L) {
  int t = lua_type(L, 2);
  luaL_argcheck(L, t == LUA_TNIL || t == LUA_TTABLE, 2,
                    "nil or table expected");
  lua_settop(L, 2);
  lua_pushboolean(L, lua_setmetatable(L, 1));
  return 1;
}
