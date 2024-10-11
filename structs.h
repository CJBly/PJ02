#ifndef _structs_h
#define _structs_h 1

typedef struct TAG_NODE{
    double	key;
    TAG_NODE 	*next;
}NODE;

typedef struct TAG_LIST{
    NODE	*head;
    NODE	*tail;
    int      length;
}LIST;

#endif
