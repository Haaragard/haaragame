#include <stdio.h>

#ifndef HAARAGAME_UTILS_CALLSTACK_C
    #define HAARAGAME_UTILS_CALLSTACK_C

    typedef struct haaragame_utils_callstack {
        unsigned int size;
        void **stack;
    } HGCallStack;

    unsigned int HGCallStackPush(HGCallStack *callStack, void *callback) {
        callStack->size++;

        void **newCallStack = (void **) memcpy(sizeof(void *) * callStack->size);
        free(callStack->stack);

        callStack->stack = newCallStack;
    }


#endif