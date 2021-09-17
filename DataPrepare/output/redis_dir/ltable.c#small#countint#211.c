static int countint (const TValue *key, int *nums) {
  int k = arrayindex(key);
  if (0 < k && k <= MAXASIZE) {  /* is `key' an appropriate array index? */
    nums[ceillog2(k)]++;  /* count as such */
    return 1;
  }
  else
    return 0;
}
