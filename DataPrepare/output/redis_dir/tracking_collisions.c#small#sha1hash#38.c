uint64_t sha1Hash(char *key, size_t len) {
    SHA1_CTX ctx;
    unsigned char hash[20];

    SHA1Init(&ctx);
    SHA1Update(&ctx,(unsigned char*)key,len);
    SHA1Final(hash,&ctx);
    uint64_t hash64;
    memcpy(&hash64,hash,sizeof(hash64));
    return hash64;
}
