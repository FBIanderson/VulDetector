uint64_t intrev64(uint64_t v) {
    memrev64(&v);
    return v;
}
