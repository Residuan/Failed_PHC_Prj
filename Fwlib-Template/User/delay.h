#ifndef __DELAY_H
#define __DELAY_H 			   

void DelayInit(void);
void DelayMs(unsigned int nms);
void DelayUs(unsigned long nus);
void DelayS(unsigned int ns);
int get_tick_count(unsigned long *count);

#endif
