raxNode *raxReallocForData(raxNode *n, void *data) {
    if (data == NULL) return n; /* No reallocation needed, setting isnull=1 */
    size_t curlen = raxNodeCurrentLength(n);
    return rax_realloc(n,curlen+sizeof(void*));
}
