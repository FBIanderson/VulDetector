static int _dictInit(dict *ht, dictType *type, void *privDataPtr) {
    _dictReset(ht);
    ht->type = type;
    ht->privdata = privDataPtr;
    return DICT_OK;
}
