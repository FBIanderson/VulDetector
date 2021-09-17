static int singlevaraux (FuncState *fs, TString *n, expdesc *var, int base) {
  if (fs == NULL) {  /* no more levels? */
    init_exp(var, VGLOBAL, NO_REG);  /* default is global variable */
    return VGLOBAL;
  }
  else {
    int v = searchvar(fs, n);  /* look up at current level */
    if (v >= 0) {
      init_exp(var, VLOCAL, v);
      if (!base)
        markupval(fs, v);  /* local will be used as an upval */
      return VLOCAL;
    }
    else {  /* not found at current level; try upper one */
      if (singlevaraux(fs->prev, n, var, 0) == VGLOBAL)
        return VGLOBAL;
      var->u.s.info = indexupvalue(fs, n, var);  /* else was LOCAL or UPVAL */
      var->k = VUPVAL;  /* upvalue in this level */
      return VUPVAL;
    }
  }
}
