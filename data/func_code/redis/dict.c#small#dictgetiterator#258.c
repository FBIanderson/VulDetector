static dictIterator *dictGetIterator(dict *ht) {
    dictIterator *iter = malloc(sizeof(*iter));

    iter->ht = ht;
    iter->index = -1;
    iter->entry = NULL;
    iter->nextEntry = NULL;
    return iter;
}
