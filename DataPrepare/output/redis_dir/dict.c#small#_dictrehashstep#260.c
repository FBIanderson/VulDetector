static void _dictRehashStep(dict *d) {
    if (d->iterators == 0) dictRehash(d,1);
}
