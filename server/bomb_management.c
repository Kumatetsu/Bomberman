#include "enum.h"
#include "constant.h"
#include "sdl.h"
#include "map.h"
#include "player_info.h"
#include "base_map_manager.h"
#include "collision.h"
// pour game_info.h
#include "client_request.h"
#include "server.h"
//
#include "game_info.h"
#include "coord_index_swapper.h"
#include "bomb_management.h"

// retourne l'index de la matrice correspondant à un déplacement dans 'direction' de 'cases' cases
// depuis 'bomb', si le 'next_index' est hors map, on retourne -1
int get_target(t_map_destroyable bomb, int direction, int cases)
{
  int col, line, index, next_index;

  // on récupère l'index, la colonne et la ligne de la bombe
  index = coord_to_index(bomb.x, bomb.y);
  col = (index + 1) % COLUMNS;
  line = (index + 1) / COLUMNS;
  if (col != 0)
    line++;
  // retour par défaut constant OUTOFMAP
  next_index = OUTOFMAP;
  switch (direction)
  {
  case BOMBER_D:
    // pour uniformiser le retour on retourne -1 mais on aurait pu tester sur < 0 à la sortie
    if (line + cases < LINES)
      next_index = index + COLUMNS * cases;
    break;
  case BOMBER_L:
    // si la colonne actuelle est inférieure aux nombre de cases souhaitées
    // pas la place donc on soustrait le nombre de case si on peut sinon return -1
    if (col >= cases)
      next_index = index - cases;
    break;
  case BOMBER_R:
    // si la colonne de la bombe est supérieure
    // au nombre total de colonnes moins le nombre de cases
    // il n'a pas la place , donc si col est inférieure on ajoute cases
    if (col < COLUMNS - cases)
      next_index = index + cases;
    break;
  case BOMBER_U:
    if (line - cases > 0)
      next_index = index - COLUMNS * cases;
    break;
  }
  return next_index;
}

void kill_player(t_srv **srv, int id)
{
  (*srv)->players[id].dying = 0;
  (*srv)->players[id].alive = 0;
  (*srv)->players[id].x = -50;
  (*srv)->players[id].bomb_left = -50;
  printf("\nSERVER, bomb_management: player %d killed\n", id);
}

// fire effect:
// wall: -1
// kill: index du joueur
// nothing: enum texture_type fire
int check_fire_effect(t_srv **srv, t_map_destroyable case_in_fire)
{
  // on réduit le carré de controle des collisions pour éviter que ca collisionne à tout va
  // on vérifie avec un carré de 16x16 avec 16 de margin
  const SDL_Rect sdl_target = init_rect(case_in_fire.x + 16, case_in_fire.y + 16, 16, 16);
  int player = 0;

  if (has_collision_with_wall(sdl_target))
  {
    return -1;
  }
  if ((player = has_collision_with_player(srv, sdl_target, -1)) >= 0)
  {

    kill_player(srv, player);
    return player;
  }
  return fire;
}

void boom(t_srv **srv, int index)
{
  t_map_destroyable boom_origin;
  int target, effect;
  int iterator, it;

  effect = -1;
  target = -1;
  boom_origin = (*srv)->map_destroyable[index];
  boom_origin.fire[BOMBER_U] = 0;
  boom_origin.fire[BOMBER_D] = 0;
  boom_origin.fire[BOMBER_L] = 0;
  boom_origin.fire[BOMBER_R] = 0;
  for (iterator = 1; iterator <= 3; iterator++)
  {
    // pour chaque direction on appelle une fonction capable de tester si
    // on peut avancer d'1, 2 ou 3
    // on applique check_fire_effect qui gère les murs et les kills
    for (it = 0; it < 4; it++)
    {
      target = get_target(boom_origin, it, iterator);
      if (target != OUTOFMAP)
      {
        // it = direction
        // iterator = cases souhaitées depuis le point d'origine
        // si le précédent tour pour cette direction à validé la présence
        // d'une explosion sur la case 'target', le fire[it] correspondant
        // DOIT être égal à iterator - 1, si ce n'est pas le cas, c'est
        // que le précédent effect était un wall. Dans ce cas, on ne souhaite pas appellé
        // check_fire_effect (car on ne veut pas tuer un joueur derrière un mur)
        // d'où l'ordre de la condition.
        (*srv)->map_destroyable[target].x = index_to_x(target);
        (*srv)->map_destroyable[target].y = index_to_y(target);
        if (boom_origin.fire[it] == iterator - 1 && (effect = check_fire_effect(srv, (*srv)->map_destroyable[target])) != -1)
        {
          boom_origin.fire[it] = iterator;
          (*srv)->map_destroyable[target].exist = 1;
          (*srv)->map_destroyable[target].explosion_stage = 5;
          (*srv)->map_destroyable[target].start_explode = 0;
        }
      }
    }
    boom_origin.bomb = 0;
    boom_origin.start_explode = 0;
    boom_origin.explosion_stage = 5;
    (*srv)->map_destroyable[index] = boom_origin;
  }
}
