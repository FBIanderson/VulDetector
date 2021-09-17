int main(void) {
    printf("SHA1 : %lu\n", testHashingFunction(sha1Hash));
    printf("CRC64: %lu\n", testHashingFunction(crc64Hash));
    return 0;
}
