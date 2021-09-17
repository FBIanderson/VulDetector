static int db_getupvalue (lua_State *L) {
  return auxupvalue(L, 1);
}
