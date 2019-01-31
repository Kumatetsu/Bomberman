#ifndef _MOVING_H_
#define _MOVING_H_

void move_player(t_srv **srv, enum COMMAND_REQUEST command, int num_player);
void change_sprite(t_player_info *player, int sprite_direction, int player_command);
int check_collision(int requested_x, int requested_y, int num_player);

#endif /* !_MOVING_H_ */
