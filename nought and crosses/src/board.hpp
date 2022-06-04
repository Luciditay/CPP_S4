#pragma once

#include <cstdlib>
#include <iostream>
#include "p6/p6.h"

struct cellIndex {
    int x;
    int y;

    cellIndex(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

    cellIndex(glm::vec2 vec)
    {
        x = vec.x;
        y = vec.y;
    }
};

glm::vec2 cell_index_to_top_left_position(p6::Context& ctx, int nb_rows, int nb_columns, cellIndex index);

std::optional<cellIndex> mouse_position_to_index(p6::Context& ctx, int nb_rows, int nb_columns);

void draw_board(p6::Context& ctx, int nb_rows, int nb_columns);

void draw_cross(p6::Context& ctx, float x, float y, float xRadius, float yRadius);

void draw_nought(p6::Context& ctx, int x, int y, float xRadius, float yRadius);
