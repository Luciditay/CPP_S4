#include <p6/p6.h>
#include <cstdlib>
#include <iostream>
#include <optional>
#include "board.hpp"
#include "boardGame.hpp"

void put_current_player_on_cell(Board& board, Player current_player, int index)
{
    board.assign_player_to_cell(index, current_player);
}

bool is_cell_empty(Board& board, int index)
{
    return !board[index].get_cell_player();
}

void current_player_click_on_board(p6::Context& ctx, Board& board, Player current_player, float nb_rows, float nb_columns)
{
    if (auto clickedCell = mouse_position_to_index(ctx, nb_rows, nb_columns)) {
        int index = cell_index_to_board_index(*clickedCell, nb_rows);
        std::cout << index << std::endl;

        if (is_cell_empty(board, index)) {
            put_current_player_on_cell(board, current_player, index);
        }
        else {
            std::cout << "Not empty cell" << std::endl;
        }
    }
}

void highligh_hovered_cell(p6::Context& ctx, Board& board, Player current_player, float nb_rows, float nb_columns)
{
    if (auto clickedCell = mouse_position_to_index(ctx, nb_rows, nb_columns)) {
        int index = cell_index_to_board_index(*clickedCell, nb_rows);

        if (is_cell_empty(board, index)) {
            float xRadius = 2.f * ctx.aspect_ratio() / nb_columns;
            float yRadius = 2.f / nb_rows;
            if (current_player == Player::Crosses) {
                draw_cross(ctx, clickedCell->y, clickedCell->x, xRadius, yRadius);
            }
            if (current_player == Player::Noughts) {
                draw_nought(ctx, clickedCell->y, clickedCell->x, xRadius, yRadius);
            }
        }
    }
}

//void check_win(Board& board, Player current_player)

int main()
{
    float stroke_weight = 0.001f;
    auto  ctx           = p6::Context{{1280, 720, "Noughts and crosses"}};
    Board board(3, 3);
    board.assign_player_to_cell(glm::vec2(0, 0), Player::Crosses, 3);

    ctx.update = [&]() {                         // Define the function that will be called in a loop once you call ctx.start()
        ctx.background({0.5f, 0.3f, 0.8f, 1.f}); // Clear the background with some color (Try to comment out this line to see what happens)
                                                 // ctx.stroke = {0.8f, 1., 1., 1.};
        draw_board(ctx, 3.f, 3.f);
        draw_noughts_and_crosses(board, ctx, 3, 3);
        highligh_hovered_cell(ctx, board, Player::Noughts, 3, 3);
        //  ctx.mouse_pressed();

    };

    ctx.mouse_pressed = [&](p6::MouseButton event) {
        current_player_click_on_board(ctx, board, Player::Crosses, 3.f, 3.f);
    };
    ctx.start();
}