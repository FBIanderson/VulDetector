uint16_t intrev16(uint16_t v) {
    memrev16(&v);
    return v;
}
