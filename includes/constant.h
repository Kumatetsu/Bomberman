#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define Y_BLUE_B 92
#define Y_RED_B 120
#define Y_WHITE_B 38
#define Y_BLACK_B 66
#define Y_BOMB 255
#define Y_FIRE 255
// general
static const int SLEEP = 250; // en millisecond
static const int TICK_IN_SEC = 1000 / 250;

// full map
static const int WINDOW_W = 1024; // 21 * 48
static const int WINDOW_H = 768; // 16
static const int PIXEL_SIZE = 48;
static const int I_BEGIN = ((1024 - (15 * 48)) / 2 ) / 48; // 3.166 soit 3 cases de chaque côté
static const int J_BEGIN = (768 - (14 * 48)) / 48; // 2

// playground
static const int COLUMNS = 15;
static const int LINES = 13;
static const int INLINE_MATRIX = 13 * 15;
static const int PX = ((1024 - (15 * 48)) / 2 ) / 48;
static const int PY = (768 - (13 * 48)) / 48;

static const int XFIRE1 = 153;
static const int XFIRE2 = 235;
static const int XFIRE3 = 318;
static const int XFIRE4 = 403;
static const int XFIRE5 = 487;

static const int OUTOFMAP = 3333;
static const int ENDGAME = 123431;

#endif /* !_CONSTANT_H_ */
