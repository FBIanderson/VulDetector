static void error_expected (LexState *ls, int token) {
  luaX_syntaxerror(ls,
      luaO_pushfstring(ls->L, LUA_QS " expected", luaX_token2str(ls, token)));
}
