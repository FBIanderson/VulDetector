uint8_t scan_entry(struct entry *e) {
    if (minutes_diff(to_16bit_minutes(time(NULL)),e->decrtime)
        >= decr_every)
    {
        if (e->counter) {
            if (e->counter > COUNTER_INIT_VAL*2) {
                e->counter /= 2;
            } else {
                e->counter--;
            }
        }
        e->decrtime = to_16bit_minutes(time(NULL));
    }
    return e->counter;
}
