#include "enum.h"
#include "response_type_utils.h"

int define_response_type(int command) {
    int type;

    if (command == MOVE_UP || MOVE_DOWN || MOVE_LEFT || MOVE_RIGHT) {
        return MOVE;
    }

    return BOMB;
}
