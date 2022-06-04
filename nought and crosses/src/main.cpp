#include <p6/p6.h>
#include <cstdlib>
#include <iostream>
#include <optional>
#include "board.hpp"
#include "boardGame.hpp"

int main()
{
    float  stroke_weight = 0.001f;
    auto   ctx           = p6::Context{{1280, 720, "Noughts and crosses"}};
    Board  board(3, 3, 0);
    Player current_player = Player::Crosses;

    ctx.update = [&]() {                         // Define the function that will be called in a loop once you call ctx.start()
        ctx.background({0.5f, 0.3f, 0.8f, 1.f}); // Clear the background with some color (Try to comment out this line to see what happens)
                                                 // ctx.stroke = {0.8f, 1., 1., 1.};
        display_board(ctx, board, 3, 3, current_player);
        //  ctx.mouse_pressed();

    };

    ctx.mouse_pressed = [&](p6::MouseButton event) {
        if (current_player_play_on_board(ctx, board, current_player, 3.f, 3.f)) {
            current_player = swap_player(current_player);
        }
    };
    ctx.start();
}