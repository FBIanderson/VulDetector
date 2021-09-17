void testrdb_type_save(RedisModuleIO *rdb, void *value) {
    RedisModuleString *str = (RedisModuleString*)value;
    RedisModule_SaveSigned(rdb, 1);
    RedisModule_SaveString(rdb, str);
    RedisModule_SaveFloat(rdb, 1.5);
    RedisModule_SaveLongDouble(rdb, 0.333333333333333333L);
}
