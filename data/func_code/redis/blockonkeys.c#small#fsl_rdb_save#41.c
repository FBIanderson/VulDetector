void fsl_rdb_save(RedisModuleIO *rdb, void *value) {
    fsl_t *fsl = value;
    RedisModule_SaveUnsigned(rdb,fsl->length);
    for (long long i = 0; i < fsl->length; i++)
        RedisModule_SaveSigned(rdb, fsl->list[i]);
}
