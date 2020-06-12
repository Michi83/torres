#include <stdint.h>
#include <stdio.h>
#include "generate.h"
#include "position.h"

uint64_t recurse(Position* position, int depth)
{
    PositionList position_list;
    generate_moves(position, &position_list);
    if (depth == 1)
    {
        return position_list.count;
    }
    uint64_t count = 0;
    for (int i = 0; i < position_list.count; i++)
    {
        Position* child = position_list.positions + i;
        count += recurse(child, depth - 1);
    }
    return count;
}

void perft(char fen[], int max_depth, uint64_t expected[])
{
    Position position;
    initialize_position(&position, fen);
    print_position(&position);
    printf("depth   count           expected        \n");
    for (int i = 0; i < max_depth; i++)
    {
        uint64_t count = recurse(&position, i + 1);
        printf("%7d %15lu %15lu ", i + 1, count, expected[i]);
        if (count != expected[i])
        {
            printf("!!!");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    char fen1[] =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    char fen2[] =
        "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";
    char fen3[] =
        "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -";
    char fen4[] =
        "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq -";
    char fen5[] =
        "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ -";
    char fen6[] =
        "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - -";
    char fen7[] =
        "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - -";
    uint64_t expected1[] = {20, 400, 8902, 197281, 4865609, 119060324};
    uint64_t expected2[] = {48, 2039, 97862, 4085603, 193690690};
    uint64_t expected3[] = {14, 191, 2812, 43238, 674624, 11030083, 178633661};
    uint64_t expected4[] = {6, 264, 9467, 422333, 15833292, 706045033};
    uint64_t expected5[] = {44, 1486, 62379, 2103487, 89941194};
    uint64_t expected6[] = {46, 2079, 89890, 3894594, 164075551};
    uint64_t expected7[] = {24, 496, 9483, 182838, 3605103, 71179139};
    perft(fen1, 6, expected1);
    perft(fen2, 5, expected2);
    perft(fen3, 7, expected3);
    perft(fen4, 6, expected4);
    perft(fen5, 5, expected5);
    perft(fen6, 5, expected6);
    perft(fen7, 6, expected7);
    return 0;
}
