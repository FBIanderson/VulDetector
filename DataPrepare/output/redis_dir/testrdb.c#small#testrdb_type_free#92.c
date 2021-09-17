void testrdb_type_free(void *value) {
    if (value)
        RedisModule_FreeString(NULL, (RedisModuleString*)value);
}
