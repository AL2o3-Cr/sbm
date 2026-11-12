
typedef struct _LListN{
    char data;
    bool isnend;
    int times;
    struct _LListN * next;
} LList;