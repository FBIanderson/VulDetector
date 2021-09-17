size_t HelloTypeMemUsage(const void *value) {
    const struct HelloTypeObject *hto = value;
    struct HelloTypeNode *node = hto->head;
    return sizeof(*hto) + sizeof(*node)*hto->len;
}
