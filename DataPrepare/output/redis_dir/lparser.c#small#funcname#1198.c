static int funcname (LexState *ls, expdesc *v) {
  /* funcname -> NAME {field} [`:' NAME] */
  int needself = 0;
  singlevar(ls, v);
  while (ls->t.token == '.')
    field(ls, v);
  if (ls->t.token == ':') {
    needself = 1;
    field(ls, v);
  }
  return needself;
}
