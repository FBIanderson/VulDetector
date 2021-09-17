static int precheck (const Proto *pt) {
  check(pt->maxstacksize <= MAXSTACK);
  check(pt->numparams+(pt->is_vararg & VARARG_HASARG) <= pt->maxstacksize);
  check(!(pt->is_vararg & VARARG_NEEDSARG) ||
              (pt->is_vararg & VARARG_HASARG));
  check(pt->sizeupvalues <= pt->nups);
  check(pt->sizelineinfo == pt->sizecode || pt->sizelineinfo == 0);
  check(pt->sizecode > 0 && GET_OPCODE(pt->code[pt->sizecode-1]) == OP_RETURN);
  return 1;
}
