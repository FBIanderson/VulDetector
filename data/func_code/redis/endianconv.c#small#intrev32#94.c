uint32_t intrev32(uint32_t v) {
    memrev32(&v);
    return v;
}
