#include <p6/p6.h>
#include <cstdlib>
#include <iostream>

struct cellIndex {
    int x;
    int y;
};

std::optional<glm::vec2> index_to_posTopLeft(p6::Context& ctx, float nb_rows, float nb_columns, int x, int y)
{
    if (ctx.mouse_is_in_window()) {
        float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
        float yRadius = 2.f / nb_rows;
        float x1      = glm::ceil(ctx.mouse().x / xRadius);
        float y1      = (int)ctx.mouse().y / yRadius;
        return glm::vec2(x, y);
    }
    return std::nullopt;
}

std::optional<glm::vec2> position_to_index(p6::Context& ctx, float nb_rows, float nb_columns)
{
    if (ctx.mouse_is_in_window()) {
        float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
        float yRadius = 2.f / nb_rows;
        // float x_begin_cell = -ctx.aspect_ratio();
        // float y_begin_cell = 1;
        // float x_next_cell  = -ctx.aspect_ratio() + xRadius;
        // float y_next_cell  = 1 + yRadius;
        //std::cout << xRadius << ' ' << yRadius << std::endl;

        float x = static_cast<int>((ctx.aspect_ratio() + ctx.mouse().x) / xRadius);
        float y = static_cast<int>((1 - ctx.mouse().y) / yRadius);

        // while (!(x_begin_cell < ctx.mouse().x && ctx.mouse().x < x_next_cell)) {
        //     x++;
        //     x_begin_cell += xRadius;
        //     x_next_cell += xRadius;
        // }

        // while (!(y_begin_cell < ctx.mouse().y && ctx.mouse().y < y_next_cell)) {
        //     y++;
        //     y_begin_cell += yRadius;
        //     y_next_cell += yRadius;
        // }

        return glm::vec2(x, y);
    }
    return {};
}

void draw_board(p6::Context& ctx, float nb_rows, float nb_columns)
{
    ctx.use_fill  = true;
    ctx.fill      = {0.5f, 0.5f, 0.5f, 1.f};
    ctx.stroke    = {1.f, 1.f, 1.f, 1.f};
    float xTile   = -ctx.aspect_ratio();
    float yTile   = 1;
    float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
    float yRadius = 2.f / nb_rows;

    for (int y = 0; y < static_cast<int>(nb_rows); y++) {
        for (int x = 0; x < static_cast<int>(nb_columns); x++) {
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
        if (auto result = position_to_index(ctx, 3.f, 3.f)) {
            std::cout << result->x << ' ' << result->y << std::endl;
            // //   std::cout << ctx.mouse().y << std::endl;
        }

    };
    ctx.start();
}