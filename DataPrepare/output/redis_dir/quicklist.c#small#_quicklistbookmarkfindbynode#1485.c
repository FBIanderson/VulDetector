quicklistBookmark *_quicklistBookmarkFindByNode(quicklist *ql, quicklistNode *node) {
    unsigned i;
    for (i=0; i<ql->bookmark_count; i++) {
        if (ql->bookmarks[i].node == node) {
            return &ql->bookmarks[i];
        }
    }
    return NULL;
}
