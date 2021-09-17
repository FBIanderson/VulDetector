fsl_t *fsl_type_create() {
    fsl_t *o;
    o = RedisModule_Alloc(sizeof(*o));
    o->length = 0;
    return o;
}
