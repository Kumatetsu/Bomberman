#ifndef _TIME_TICK_H_
#define _TIME_TICK_H_

int	sec_sleep(int seconds);
int	milli_sleep(int milliseconds);
int	sec_to_milli();
int	nano_sleep();
int	sleep_ms(int sec, int ms);
int	sec_in_tick();

#endif /* !_TIME_TICK_H_ */
