static dict *dictCreate(dictType *type, void *privDataPtr) {
    dict *ht = malloc(sizeof(*ht));
    _dictInit(ht,type,privDataPtr);
    return ht;
}
