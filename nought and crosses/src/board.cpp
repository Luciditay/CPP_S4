#include "board.hpp"

glm::vec2 cell_index_to_top_left_position(p6::Context& ctx, float nb_rows, float nb_columns, cellIndex index)
{
    float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
    float yRadius = 2.f / nb_rows;
    float posX    = -ctx.aspect_ratio() + index.x * xRadius;
    float posY    = 1 - index.y * yRadius;
    return glm::vec2(posX, posY);
}

std::optional<cellIndex> mouse_position_to_index(p6::Context& ctx, float nb_rows, float nb_columns)
{
    if (ctx.mouse_is_in_window()) {
        float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
        float yRadius = 2.f / nb_rows;

        int x = static_cast<int>((ctx.aspect_ratio() + ctx.mouse().x) / xRadius);
        int y = static_cast<int>((1 - ctx.mouse().y) / yRadius);

        return cellIndex(y, x);
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

void draw_cross(p6::Context& ctx, float x, float y, float xRadius, float yRadius)
{
    glm::vec2 crossPos = cell_index_to_top_left_position(ctx, 3, 3, glm::vec2(x, y));

    float x1 = crossPos.x;
    float y1 = crossPos.y;
    ctx.line(glm::vec2(x1, y1), glm::vec2(x1 + xRadius, y1 - yRadius));
    ctx.line(glm::vec2(x1, y1 - yRadius), glm::vec2(x1 + xRadius, y1));
}

void draw_square(p6::Context& ctx, int x, int y, float xRadius, float yRadius)
{
    ctx.rectangle(p6::TopLeftCorner{x, y}, p6::Radii{xRadius, yRadius});
}