static void errorlimit (FuncState *fs, int limit, const char *what) {
  const char *msg = (fs->f->linedefined == 0) ?
    luaO_pushfstring(fs->L, "main function has more than %d %s", limit, what) :
    luaO_pushfstring(fs->L, "function at line %d has more than %d %s",
                            fs->f->linedefined, limit, what);
  luaX_lexerror(fs->ls, msg, 0);
}
