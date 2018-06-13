#ifndef _BASE_MAP_H_
#define _BASE_MAP_H_
#include "player.h"
#include "sdl.h"
typedef enum texture_type
  {
    wall,
    ground,
    ground_shadowed,
    firstPlayer,
    pannel,
    timer
  } texture_type;

typedef struct s_map
{
  SDL_Rect	src_rect;
  SDL_Rect	dest_rect;
  texture_type  texture_type;
} t_map;

typedef struct s_data
{
  SDL_Texture	*texture;
  SDL_Renderer	*renderer;
  SDL_Window	*window;
  t_map		array_map[14][15];
  t_player	players[4];
} t_data;

// in the picture, the size of the square is 16 for a wall block, so i use 48

static const int WINDOW_W = 1024;
static const int WINDOW_H = 768;
static const int PIXEL_SIZE = 48;
static const int I_BEGIN = ((1024 - (15 * 48)) / 2 ) / 48;
static const int J_BEGIN = (768 - (13 * 48)) / 48;
enum BomberSpriteDir {bomber_d = 0,
		      bomber_l = 1,
		      bomber_r = 2,
		      bomber_u = 3,
		      not_move = 0,
		      die = 4};  

void *init_sprites_sheet(void *arg);
void *draw_player_1(void *arg);
void *draw_map_model(void *arg);
void *draw_pannel(void *arg);
void *draw_timer(void *arg);
void *draw_all(void *arg);
void *rebuild_map(void *arg);
void *white_bomber_sprite(void *arg);
SDL_Rect init_rect(int x, int y, int w, int z);
t_map init_t_map(SDL_Rect src, SDL_Rect dest, texture_type type);
int start_map(t_sdl *sdl);
#endif
