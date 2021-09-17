void fsl_aofrw(RedisModuleIO *aof, RedisModuleString *key, void *value) {
    fsl_t *fsl = value;
    for (long long i = 0; i < fsl->length; i++)
        RedisModule_EmitAOF(aof, "FSL.PUSH","sl", key, fsl->list[i]);
}
