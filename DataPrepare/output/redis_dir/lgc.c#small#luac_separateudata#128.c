size_t luaC_separateudata (lua_State *L, int all) {
  global_State *g = G(L);
  size_t deadmem = 0;
  GCObject **p = &g->mainthread->next;
  GCObject *curr;
  while ((curr = *p) != NULL) {
    if (!(iswhite(curr) || all) || isfinalized(gco2u(curr)))
      p = &curr->gch.next;  /* don't bother with them */
    else if (fasttm(L, gco2u(curr)->metatable, TM_GC) == NULL) {
      markfinalized(gco2u(curr));  /* don't need finalization */
      p = &curr->gch.next;
    }
    else {  /* must call its gc method */
      deadmem += sizeudata(gco2u(curr));
      markfinalized(gco2u(curr));
      *p = curr->gch.next;
      /* link `curr' at the end of `tmudata' list */
      if (g->tmudata == NULL)  /* list is empty? */
        g->tmudata = curr->gch.next = curr;  /* creates a circular list */
      else {
        curr->gch.next = g->tmudata->gch.next;
        g->tmudata->gch.next = curr;
        g->tmudata = curr;
      }
    }
  }
  return deadmem;
}
