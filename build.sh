gcc -O3 -Wall -Werror -Wextra -Wpedantic -o torres-minimax evaluate.c generate.c minimax.c position.c xboard.c
ln -f -s torres-minimax torres
ln -f -s torres-minimax torres-default
gcc -O3 -Wall -Werror -Wextra -Wpedantic -o torres-mcts generate.c mcts.c position.c xboard.c -lm
