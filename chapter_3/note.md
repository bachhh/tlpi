
# va_list

    C setup function parameters on the stack from lower to
    higher memory

    A call va_start() initialize a pointer to the first parameter
    as such

    ```c
    void func(int n, ...)
    {
        char *p =  (char *) &a + sizeof(a);
        // now p point to the first argument in the list
    }
    ```

    Subsequent call to va_arg() macro increment va_list to point to
    next parameters




