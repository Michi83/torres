#include <stdlib.h>
#include "generate.h"
#include "position.h"
#include "random.h"
#include "xboard.h"

Position random_move(Position* position)
{
    PositionList position_list;
    generate_moves(position, &position_list);
    int i = rand() % position_list.count;
    return position_list.positions[i];
}

int main(void)
{
    talk_to_xboard(&random_move);
    return 0;
}
