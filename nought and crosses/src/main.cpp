#include <p6/p6.h>
#include <cstdlib>
#include <iostream>
#include "board.hpp"

int main()
{
    float stroke_weight = 0.001f;
    auto  ctx           = p6::Context{{1280, 720, "Noughts and crosses"}};

    ctx.update = [&]() {                         // Define the function that will be called in a loop once you call ctx.start()
        ctx.background({0.5f, 0.3f, 0.8f, 1.f}); // Clear the background with some color (Try to comment out this line to see what happens)
                                                 // ctx.stroke = {0.8f, 1., 1., 1.};
        draw_board(ctx, 3.f, 3.f);
        if (auto result = mouse_position_to_index(ctx, 3.f, 3.f)) {
            std::cout << result->x << ' ' << result->y << std::endl;
            // //   std::cout << ctx.mouse().y << std::endl;
        }
    };
    ctx.start();
}