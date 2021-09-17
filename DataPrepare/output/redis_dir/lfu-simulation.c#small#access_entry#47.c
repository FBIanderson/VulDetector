void access_entry(struct entry *e) {
    e->counter = log_incr(e->counter);
    e->hits++;
}
