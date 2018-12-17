#ifndef _BOMBER_SPRITES_H_
#define _BOMBER_SPRITES_H_

#include "sdl.h"
/**
 * GETTERS
**/
SDL_Rect getBlueSprites();
SDL_Rect getBlackSprites();
SDL_Rect getRedSprites();
SDL_Rect getWhiteSprites();
SDL_Rect getBombSprites();

/**
 * INIT
**/
SDL_Rect initBlueBomberSprites();
SDL_Rect initBlackBomberSprites();
SDL_Rect initRedBomberSprites();
SDL_Rect initWhiteBomberSprites();
SDL_Rect initBombSprites();


#endif /* !_BOMBER_SPRITES_H_ */
