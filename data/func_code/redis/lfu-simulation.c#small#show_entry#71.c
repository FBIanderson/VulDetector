void show_entry(long pos, struct entry *e) {
    char *tag = "normal       ";

    if (pos >= 10 && pos <= 14) tag = "new no access";
    if (pos >= 15 && pos <= 19) tag = "new accessed ";
    if (pos >= keyspace_size -5) tag= "old no access";

    printf("%ld] <%s> frequency:%d decrtime:%d [%lu hits | age:%ld sec]\n",
        pos, tag, e->counter, e->decrtime, (unsigned long)e->hits,
            time(NULL) - e->ctime);
}
