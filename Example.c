
#include "FIFO.h"

typedef struct T
{
    uint8_t  name[20];
    uint8_t  sex;
    uint8_t  addr;
    uint32_t tel;
}T;

#define ELE_CNT 2

T FIFO_Pool[ELE_CNT];

static void TestCase_DynamicMemory(void)
{
    FIFO_t* MyFifo = FIFO_Create(sizeof(T), ELE_CNT);
    FIFO_Destory(MyFifo);
}

static void TestCase_StaticMemory(void)
{
    FIFO_t MyFifo;
    int ret = 0;
    T MyT_A, MyT_B, MyT_C;
    T MyT;

    MyT.sex  = 0;
    MyT.addr = 0;
    MyT.tel  = 0;

    MyT_A.sex  = 1;
    MyT_A.addr = 1;
    MyT_A.tel  = 1;

    MyT_B.sex  = 2;
    MyT_B.addr = 2;
    MyT_B.tel  = 2;

    MyT_C.sex  = 3;
    MyT_C.addr = 3;
    MyT_C.tel  = 3;

    FIFO_Init(&MyFifo, FIFO_Pool, sizeof(T), ELE_CNT);

    ret = FIFO_IsEmpty(&MyFifo);
    ret = FIFO_IsFull(&MyFifo);
    ret = FIFO_CountFree(&MyFifo);
    ret = FIFO_CountUsed(&MyFifo);

    FIFO_Put(&MyFifo, &MyT_A);
    FIFO_Put(&MyFifo, &MyT_B);
    FIFO_Put(&MyFifo, &MyT_C);

    ret = FIFO_IsEmpty(&MyFifo);
    ret = FIFO_IsFull(&MyFifo);
    ret = FIFO_CountFree(&MyFifo);
    ret = FIFO_CountUsed(&MyFifo);

    FIFO_Get(&MyFifo, &MyT);
    FIFO_Get(&MyFifo, &MyT);
    FIFO_Get(&MyFifo, &MyT);

    ret = FIFO_IsEmpty(&MyFifo);
    ret = FIFO_IsFull(&MyFifo);
    ret = FIFO_CountFree(&MyFifo);
    ret = FIFO_CountUsed(&MyFifo);

    FIFO_Put(&MyFifo, &MyT_A);
    FIFO_Put(&MyFifo, &MyT_B);
    FIFO_Put(&MyFifo, &MyT_C);

    ret = FIFO_Flush(&MyFifo);

    ret = FIFO_IsEmpty(&MyFifo);
    ret = FIFO_IsFull(&MyFifo);
    ret = FIFO_CountFree(&MyFifo);
    ret = FIFO_CountUsed(&MyFifo);
}

int main(void)
{
    static uint8_t Test[20];
    uint8_t retval = 0;
    
    FIFO_S_t SingleFifo;
    
    TestCase_DynamicMemory();
    TestCase_StaticMemory();
    
    FIFO_S_Init(&SingleFifo, Test, sizeof(Test));
    FIFO_S_Put(&SingleFifo, 'A');
    FIFO_S_Put(&SingleFifo, 'B');
    FIFO_S_Put(&SingleFifo, 'C');
    FIFO_S_Put(&SingleFifo, 'D');
    FIFO_S_Put(&SingleFifo, 'E');
    
    retval = FIFO_S_IsEmpty(&SingleFifo);
    retval = FIFO_S_IsFull(&SingleFifo);
    retval = FIFO_S_CountUsed(&SingleFifo);
    retval = FIFO_S_CountFree(&SingleFifo);    

    retval = FIFO_S_PreRead(&SingleFifo, 0);
    retval = FIFO_S_PreRead(&SingleFifo, 1);
    retval = FIFO_S_PreRead(&SingleFifo, 2);
    retval = FIFO_S_PreRead(&SingleFifo, 3);
    retval = FIFO_S_PreRead(&SingleFifo, 4);
    
    retval = FIFO_S_Get(&SingleFifo);
    retval = FIFO_S_Get(&SingleFifo);
    retval = FIFO_S_Get(&SingleFifo);
    retval = FIFO_S_Get(&SingleFifo);
    retval = FIFO_S_Get(&SingleFifo);    
    
    
    return (0);
}
