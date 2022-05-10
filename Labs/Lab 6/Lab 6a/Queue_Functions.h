#include "MKL25z4.h"
#include "gpio_defs.h"

void Q_Init(Q_T * q);

int Q_Empty(Q_T *q);

int Q_Full(Q_T *q);

int Q_Size(Q_T *q);

int Q_Enqueue(Q_T *q, uint8_t d);

int Q_Dequeue(Q_T *q);
	