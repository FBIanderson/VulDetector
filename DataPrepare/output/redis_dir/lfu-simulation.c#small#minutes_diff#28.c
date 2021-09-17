uint16_t minutes_diff(uint16_t now, uint16_t prev) {
    if (now >= prev) return now-prev;
    return 65535-prev+now;
}
