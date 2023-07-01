#include<stdio.h>


#define BOARD_SIDE_LENGTH 5
#define BOARD_SIZE BOARD_SIDE_LENGTH * BOARD_SIDE_LENGTH


typedef enum Moves {
    Up = 1, Down = 2, Left = 4, Right = 9
} BoardMove;

int convert_1d_to_2d(int index, int result_buffer[2]) {

    if (index > BOARD_SIZE) {
        return 1;
    }

    result_buffer[0] = index / BOARD_SIDE_LENGTH;
    result_buffer[1] = index % BOARD_SIDE_LENGTH;

    return 0;
}


int convert_2d_to_1d(int x, int y) {
    return x * BOARD_SIDE_LENGTH + y;
}


int get_next_free_space_index(int index, BoardMove move) {
    int next_index = index;

    switch (move) {
        case Up: {
            next_index -= BOARD_SIDE_LENGTH;
            break;
        }
        case Down: {
            next_index += BOARD_SIDE_LENGTH;
            break;
        }
        case Left: {
            next_index -= 1;
            break;
        }
        case Right: {
            next_index += 1;
            break;
        }
    }

    return (next_index > 0 && next_index < BOARD_SIZE) ? next_index : -1;
}


int main() {
    return 0;
}
