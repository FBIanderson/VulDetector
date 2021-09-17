uint64_t crc64Hash(char *key, size_t len) {
    return crc64(0,(unsigned char*)key,len);
}
