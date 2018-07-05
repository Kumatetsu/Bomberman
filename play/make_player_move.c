/*
** make_player_move.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/play
** 
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
** 
** Started on  Tue Jul  3 23:52:36 2018 MASERA Mathieu
*/


void function_test(t_game_info game_info, t_base_map base_map) {
  int i;
  int convert_x;
  int convert_y;
  
  for (i = 0; i < 4; i++) {
    if (game_info->players[i].alive) {
      convert_x = walk_X_into_pixels(game_info->players[i].x_pos);
      convert_y = walk_Y_into_pixels(game_info->players[i].y_pos);
      if (convert_x == base_map->players[i].x && convert_y == base_map->players[i].y) {
	continue;
      } else if (convert_x != base_map->players[i].x) {
	if (game_info->players[i].current_dir == bomb_d) {
	  move_player_down(base_map,i);
	} else {
	  move_player_up(base_map,i);
	}
      } else if (convert_y != base_map->players[i].y) {
	if (game_info->players[i].current_dir == bomb_l) {
	  move_player_left(base_map, i);
	} else {
	  move_player_right(base_map, i);
	}
      }
      
    } else if (game_info->players[i].dying) {
      //what to do here ? anim the dying mother fucker
    }
  }
}

void	update_destroyable_stuffs(t_game_info game_info){
  int	i;
  int	j;
  
  for (i = 0; i < 14; i++) {
    for (j = 0; i < 15; i++) {
      if (game_info->map_destroyable[i][j].wall_destroyable) {
	draw_destroyable_wall(game_info);
      }
      }
    }
  }
}

int walk_Y_into_pixels(int value) {
  int first_step_X =  (I_BEGIN + 1) * 48;
  value *= first_step_X;
  return (value);
}

int walk_X_into_pixels(int value) {
  int first_step_Y = ((J_BEGIN + 1) * 48) - 36;
  value *= first_step_Y;
  return (value);
}

int step_X_into_walk(int value) {
  int first_step_X =  (I_BEGIN + 1) * 48;
  value /= first_step_Y;
  return (value);
}

int step_Y_into_walk(int value) {
  int first_step_Y = ((J_BEGIN + 1) * 48) - 36;
  value /= first_step_Y;
  return (value);
}
