/*
** draw_base_map.c for  in /home/notwak42/Projects/C/Bomberman/BombGit/Bomberman/base_map
**
** Made by MASERA Mathieu
** Login   <masera_m@etna-alternance.net>
**
** Started on  Wed Jul  4 09:31:13 2018 MASERA Mathieu
** Last update Wed Jul  4 09:31:14 2018 MASERA Mathieu
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "constant.h"
#include "enum.h"
#include "sdl.h"
#include "player_info.h"
#include "client_request.h"
#include "server.h"
#include "map.h"
#include "base_map_manager.h"
#include "data.h"
#include "base_map_manager.h"
#include "bomber_sprites.h"
#include "coord_index_swapper.h"
#include "draw_base_map.h"

void *draw_map_model(void *arg)
{
    int i, j, a, b, error, element_type;

    t_data *data = (t_data *) arg;
    error = 0;
    a = 1;
    SDL_Rect ground_value;
    texture_type texture_value;
    SDL_Rect wall_src_rect = {71, 175, 16, 16};
    SDL_Rect ground_src_rect = {122, 175, 16, 16};
    SDL_Rect ground_shadowed_rect = {105, 175, 16, 16};

    // hauteur
    for (j = J_BEGIN; j < J_BEGIN + 13; j++) {
        b = 0;
        // largeur
        for (i = I_BEGIN; i < I_BEGIN + 15; i++) {
            SDL_Rect dest_rect = {i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE};

            element_type = get_element_type(i, j);
            if (element_type == WALL) {
                ground_value = wall_src_rect;
                texture_value = wall;
            }
            else if (element_type == FREE_SLOT_SHADOW) {
                ground_value = ground_shadowed_rect;
                texture_value = ground_shadowed;
            }
            else if (element_type == FREE_SLOT) {
                ground_value = ground_src_rect;
                texture_value = ground_shadowed;
            }
            else {
                error = 1;
                SDL_ShowSimpleMessageBox(0, "adding texture in renderer error", SDL_GetError(), data->window);
                break;
            }

            error = SDL_RenderCopy(data->renderer, data->texture, &ground_value, &dest_rect);
	    // on range le carré dans array map en commençant à a == 1 pour laisser la première ligne libre
            data->array_map[a][b] = init_t_map(ground_value, dest_rect, texture_value);

            if (error < 0) {
                SDL_ShowSimpleMessageBox(0, "adding texture in renderer error",
                                         SDL_GetError(), data->window);
                break;
            }
            b++;
        }
        if (error < 0)
            break;
        a++;
    }
    if (error < 0)
        return (NULL);
    return ((void *) data);
}

int		draw_timer(void *arg)
{
  int		error;
  t_data	*data = (t_data*) arg;
  SDL_Rect	timer_panel_rect = {413, 37, 32, 14};
  SDL_Rect	dest_rect_score = {0, 0, WINDOW_W , J_BEGIN * PIXEL_SIZE};
  SDL_Rect	dest_rect_timer = {(WINDOW_W / 2) - ((timer_panel_rect.w / 2) * 5),
				   (dest_rect_score.h / 2) -
				   ((timer_panel_rect.h / 2) * 5),
				   timer_panel_rect.w * 5,
				   timer_panel_rect.h * 5};

  error = SDL_RenderCopy(data->renderer, data->texture,
			 &timer_panel_rect, &dest_rect_timer);
  data->array_map[0][1] = init_t_map(timer_panel_rect, dest_rect_timer,
				     timer);
  if (error < 0)
    {
      SDL_ShowSimpleMessageBox(0, "drawing Timer Failed",
			     SDL_GetError(), data->window);
      return (0);
    }
  return (1);
}

int		draw_pannel(void *arg)
{
  int		error;
  t_data	*data = (t_data*) arg;
  SDL_Rect	score_panel_rect = {414, 175, 256, 32};
  SDL_Rect	dest_rect_score = {0, 0, WINDOW_W , J_BEGIN * PIXEL_SIZE};

  error = SDL_RenderCopy(data->renderer, data->texture,
			 &score_panel_rect, &dest_rect_score);
  data->array_map[0][0] = init_t_map(score_panel_rect, dest_rect_score,
				     pannel);
  if (error < 0)
    {
      SDL_ShowSimpleMessageBox(0, "drawing Score Tab Failed",
			     SDL_GetError(), data->window);
      return (0);
    }
  return (1);
}

/*
 BOMBER_D == 0
 BOMBER_L == 1
 BOMBER_R == 2
 BOMBER_U == 3
 */
void		draw_explosion(void *arg, t_map_destroyable bomb_origin, int bomb_origin_index)
{
  t_data	*data = (t_data*)arg;
  int		x_cut, y_cut, width_cut, height_cut;
  int		up_withdraw, left_withdraw;
  int		x_origin, y_origin;
  int		x_dest, y_dest, index_dest;
  SDL_Rect	explosion;
  SDL_Rect	dest_rect;
  
  // la largeur du sprite sera du nombre de cases à gauche et à droite plus la centrale
  // le tout multiplié par PIXEL_SIZE puis ramener à la taille du fichier surface
  width_cut = (2 + bomb_origin.fire[BOMBER_L] + bomb_origin.fire[BOMBER_R]) * 10; // max total == 80
  height_cut = (2 + bomb_origin.fire[BOMBER_U] + bomb_origin.fire[BOMBER_D]) * 10; // max total == 80
  printf("\nL'explosion découpé (sprite) %d largeur sur %d de hauteur\n", width_cut, height_cut);
  printf("\nL'explosion rendue (game) %d largeur sur %d de hauteur\n", width_cut * 3, height_cut * 3);
  // calculer le nombre de case non remplies depuis le haut du sprite (si une seule case
  // flambe, je dois descendre la découpe du sprite.)
  up_withdraw = (3 - bomb_origin.fire[BOMBER_U]) * 10; // pixels
  y_cut = Y_FIRE + up_withdraw;
  // même chose depuis la gauche
  left_withdraw = (3 - bomb_origin.fire[BOMBER_L]) * 10; // pixels
  x_cut = getExplosionX(bomb_origin.explosion_stage) + left_withdraw;
  explosion = getExplosionSprite(x_cut, y_cut, width_cut, height_cut);


  // calculer le point de départ du collage sur la map
  // on ramène le x et y de la bomb au x et y de la case de la bomb
  x_origin = index_to_x(bomb_origin_index);
  y_origin = index_to_y(bomb_origin_index);
  printf("\nL'explosion part de la bomb à l'index: %d - x_bomb: %d, y_bomb: %d, x from index: %d, y from index: %d", bomb_origin_index, bomb_origin.x, bomb_origin.y, x_origin, y_origin);
  // de la, on fait l'opération inverse en se déplacan du nombre de case souhaitées
  // en haut et à gauche. Le croisement entre le x de la case la plus à gauche et le y de la case la plus haute
  // donne le point de départ de la sprite d'explosion sur la map.
  // de là on extrait l'index de cette case
  x_dest = x_origin - left_withdraw * 3;// + I_BEGIN;
  y_dest = y_origin - up_withdraw * 3;// + J_BEGIN;
  index_dest = coord_to_index(x_dest, y_dest);
  printf("\nL'explosion sera placée à l'index: %d, x=%d et y=%d\n", index_dest, x_dest, y_dest);
  dest_rect = init_rect(x_dest, y_dest, (width_cut * 3), (height_cut * 3));
  // on génère le drawer
  data->map_destroyable[index_dest].exist = 1; 
  data->destroyable_drawer[index_dest] = init_t_map(explosion, dest_rect, fire);
}

void			draw_destroyable_model(void *arg)
{
  int			i;
  t_data		*data = (t_data*) arg;
  t_map_destroyable	destroyable;
  SDL_Rect		bomb_sprite;

  bomb_sprite = getBombSprites(2);
  for (i = 0; i < INLINE_MATRIX; i++)
    {
      destroyable = data->map_destroyable[i];
      if (destroyable.exist)
	{
	  if (destroyable.bomb)
	    {
	      SDL_Rect dest_rect = pixel_rect(destroyable.x, destroyable.y);
	      data->destroyable_drawer[i] = init_t_map(bomb_sprite, dest_rect, bomb);
	    }
	  // dev
	  if (destroyable.explosion_stage == 6)
	    {
	      SDL_Rect explosion = getExplosionSprite((XFIRE1 + 32), (Y_FIRE + 36), 16, 16);
	      // dest_rect = init_rect((96 + 3 * 30), (48 + 3 * 30), (240 - 3 * 30), (240 - 3 * 30));
	      SDL_Rect dest_rect = init_rect(destroyable.x, destroyable.y, 48, 48);
	      printf("\nL'explosion fake sera placée à l'index: %d, x=%d et y=%d\n", i, destroyable.x, destroyable.y);
	      data->map_destroyable[i].exist = 1; 
	      data->destroyable_drawer[i] = init_t_map(explosion, dest_rect, fire);
	    }
	  if (destroyable.explosion_stage > 0 && destroyable.explosion_stage < 6)
	    {
	      printf("\nCLIENTSIDE draw_destroyable model, draw explosion, explosion_stage: %d", destroyable.explosion_stage);
	      draw_explosion(arg, destroyable, i);
	      for (int j = 0; j < 4; j++)
		{
		  printf("\nbomb fire %d = %d\n", j, destroyable.fire[j]);
		}
	    }
	}
    }
}
