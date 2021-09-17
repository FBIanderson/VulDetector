static int dictReplace(dict *ht, void *key, void *val) {
    dictEntry *entry, auxentry;

    /* Try to add the element. If the key
     * does not exists dictAdd will succeed. */
    if (dictAdd(ht, key, val) == DICT_OK)
        return 1;
    /* It already exists, get the entry */
    entry = dictFind(ht, key);
    /* Free the old value and set the new one */
    /* Set the new value and free the old one. Note that it is important
     * to do that in this order, as the value may just be exactly the same
     * as the previous one. In this context, think to reference counting,
     * you want to increment (set), and then decrement (free), and not the
     * reverse. */
    auxentry = *entry;
    dictSetHashVal(ht, entry, val);
    dictFreeEntryVal(ht, &auxentry);
    return 0;
}
