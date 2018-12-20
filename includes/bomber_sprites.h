#ifndef _BOMBER_SPRITES_H_
#define _BOMBER_SPRITES_H_

#include "sdl.h"
/**
 * GETTERS
**/
SDL_Rect getBomberSprites(int num_player, int dir, int action);
SDL_Rect getBlueSprites(int dir, int action);
SDL_Rect getBlackSprites(int dir, int action);
SDL_Rect getRedSprites(int dir, int action);
SDL_Rect getWhiteSprites(int dir, int action);
SDL_Rect getBombSprites(int type);

/**
 * INIT
**/
void initSprites();
void initBlueBomberSprites();
void initBlackBomberSprites();
void initRedBomberSprites();
void initWhiteBomberSprites();
void initBombSprites();


#endif /* !_BOMBER_SPRITES_H_ */
