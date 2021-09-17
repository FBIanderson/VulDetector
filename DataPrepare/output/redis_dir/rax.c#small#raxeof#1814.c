int raxEOF(raxIterator *it) {
    return it->flags & RAX_ITER_EOF;
}
