unsigned long testHashingFunction(uint64_t (*hash)(char *, size_t)) {
    unsigned long collisions = 0;
    memset(Table,0,sizeof(Table));
    char *prefixes[] = {"object", "message", "user", NULL};
    for (int i = 0; prefixes[i] != NULL; i++) {
        for (int j = 0; j < TABLE_SIZE/2; j++) {
            char keyname[128];
            size_t keylen = snprintf(keyname,sizeof(keyname),"%s:%d",
                                     prefixes[i],j);
            uint64_t bucket = hash(keyname,keylen) % TABLE_SIZE;
            if (Table[bucket]) {
                collisions++;
            } else {
                Table[bucket] = 1;
            }
        }
    }
    return collisions;
}
