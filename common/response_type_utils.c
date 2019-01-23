#include "enum.h"
#include "response_type_utils.h"

int define_response_type(int command) {
    int type;

    if (command == MOVE_UP
        || command == MOVE_DOWN
        || command == MOVE_LEFT
        || command == MOVE_RIGHT
    ) {
        return MOVE;
    }

    return BOMB;
}
