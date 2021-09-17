quicklistBookmark *_quicklistBookmarkFindByName(quicklist *ql, const char *name) {
    unsigned i;
    for (i=0; i<ql->bookmark_count; i++) {
        if (!strcmp(ql->bookmarks[i].name, name)) {
            return &ql->bookmarks[i];
        }
    }
    return NULL;
}
