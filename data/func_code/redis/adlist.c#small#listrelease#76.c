void listRelease(list *list)
{
    listEmpty(list);
    zfree(list);
}
