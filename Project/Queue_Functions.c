#include "MKL25z4.h"
#include "gpio_defs.h"



void Q_Init(Q_T * q){
	unsigned int i;
	for (i = 0; i < Q_MAX_SIZE; i++){
		q->Data[i] = 0;
	}
	
	q->Head = 0;
	q->Tail = 0;
	q->Size = 0;
}

int Q_Empty(Q_T *q) {
	return q->Size == 0;
}

int Q_Full(Q_T *q){
	return q->Size == Q_MAX_SIZE;
}

int Q_Size(Q_T *q){
	return q->Size;
}

int Q_Enqueue(Q_T *q, uint8_t d){
	uint32_t masking_state;
	//check if the queue is full
	if(!Q_Full(q)){
		q->Data[q->Tail++] = d;
		q->Tail %= Q_MAX_SIZE;
		//save current masking state
		masking_state = __get_PRIMASK();
		//disable intrupts
		__disable_irq();
		//update the size
		q->Size++;
		//restore the masking state
		__set_PRIMASK(masking_state);
		
		return 1;
	} else {
		return 0;
	}
}

int Q_Dequeue(Q_T *q){
	uint32_t masking_state;
	
	uint8_t t = 0;
	//check if the queue is full
	if(!Q_Empty(q)){
		t = q->Data[q->Head];
		q->Data[q->Head++] = '_';
		q->Head %= Q_MAX_SIZE;
		//save current masking state
		masking_state = __get_PRIMASK();
		//disable inturrupts
		__disable_irq();
		//update variable
		q->Size--;
		//restore masking state
		__set_PRIMASK(masking_state);
	}
	return t;
}