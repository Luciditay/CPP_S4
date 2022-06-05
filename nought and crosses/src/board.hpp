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

//Renvoie depuis l'index d'une case, un point correspondant au début Haut/Gauche de la case
glm::vec2 cell_index_to_top_left_position(p6::Context& ctx, int nb_rows, int nb_columns, cellIndex index);

//A partir de la position de la souris, renvoie l'index de la case correspondante (allant de 0 à nb_rows x nb_columns)
std::optional<cellIndex> mouse_position_to_index(p6::Context& ctx, int nb_rows, int nb_columns);

//Dessine un terrain de taille nb_rows X nb_columns
void draw_board(p6::Context& ctx, int nb_rows, int nb_columns);

//Dessine une croix dans une case de longueur xRadius et de hauteur yRadius, à partir d'un point (X, Y) situé en haut à gauche
void draw_cross(p6::Context& ctx, float x, float y, float xRadius, float yRadius);

//Idemn pour draw_cross, mais dessine un cercle
void draw_nought(p6::Context& ctx, int x, int y, float xRadius, float yRadius);
