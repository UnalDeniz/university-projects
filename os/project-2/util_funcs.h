int str2int(char *string);

void quick_int_sort(int *arr, int low, int high);

int intCompare(const void *i1, const void *i2);
//static int intCompare(const void *i1, const void *i2);

void generate_arr(int **arr_pointer, int size, int seed);

void print_all(char filename[12], double time);

void *execute(void *args);

struct fun_list{

    int list_size;
    void* (*func_ptr[10])();

};
