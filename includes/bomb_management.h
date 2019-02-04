#ifndef _BOMB_MANAGEMENT_H_
#define _BOMB_MANAGEMENT_H_

int get_target(t_map_destroyable bomb, int dir, int cases);
void kill_payer(int id);
int check_fire_effect(t_srv **srv, t_map_destroyable case_in_fire);
void boom(t_srv **srv, int indexes[5]);

#endif /* !_BOMB_MANAGEMENT_H_ */
