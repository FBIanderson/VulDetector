void raxIteratorDelChars(raxIterator *it, size_t count) {
    it->key_len -= count;
}
