static inline char sdsReqType(size_t string_size) {
    if (string_size < 32)
        return SDS_TYPE_5;
    if (string_size < 0xff)
        return SDS_TYPE_8;
    if (string_size < 0xffff)
        return SDS_TYPE_16;
    if (string_size < 0xffffffff)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
}
