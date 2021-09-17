void *fsl_rdb_load(RedisModuleIO *rdb, int encver) {
    if (encver != 0) {
        return NULL;
    }
    fsl_t *fsl = fsl_type_create();
    fsl->length = RedisModule_LoadUnsigned(rdb);
    for (long long i = 0; i < fsl->length; i++)
        fsl->list[i] = RedisModule_LoadSigned(rdb);
    return fsl;
}
