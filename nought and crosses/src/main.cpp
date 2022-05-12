#include <p6/p6.h>
#include <boid.hpp>
#include <cstdlib>
#include <iostream>

void draw_board(p6::Context& ctx, float nb_rows, float nb_columns)
{
    ctx.use_fill  = true;
    ctx.fill      = {0.5f, 0.5f, 0.5f, 1.f};
    ctx.stroke    = {1.f, 1.f, 1.f, 1.f};
    float xTile   = -ctx.aspect_ratio();
    float yTile   = 1;
    float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
    float yRadius = 2.f / nb_rows;

    for (int y = 0; y < nb_rows; y++) {
        for (int x = 0; x < nb_columns; x++) {
            ctx.rectangle(p6::TopLeftCorner{xTile, yTile}, p6::Radii{xRadius, yRadius});
            xTile += xRadius;
        }
        xTile = -ctx.aspect_ratio();
        yTile -= yRadius;
    }
    ctx.use_fill = false;
    ctx.rectangle(p6::Center{0, 0}, p6::Radii{ctx.aspect_ratio(), 1}); //Permit the white stroke at the extreme right and bottom to be there
}

int main()
{
    float stroke_weight = 0.001f;
    auto  ctx           = p6::Context{{1280, 720, "Noughts and crosses"}};

    ctx.update = [&]() {                         // Define the function that will be called in a loop once you call ctx.start()
        ctx.background({0.5f, 0.3f, 0.8f, 1.f}); // Clear the background with some color (Try to comment out this line to see what happens)
                                                 // ctx.stroke = {0.8f, 1., 1., 1.};
        draw_board(ctx, 3.f, 3.f);
    };
    ctx.start();
}