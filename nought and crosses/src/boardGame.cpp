#include "boardGame.hpp"

void display_winning_message(Board& board, Player winning_player)
{
    if (board.pawn_played() == 9) {
        std::cout << "That's a tie !" << std::endl;
    }
    else if (winning_player == Player::Crosses) {
        std::cout << "Crosses won !" << std::endl;
    }
    else if (winning_player == Player::Noughts) {
        std::cout << "Noughts won !" << std::endl;
    }
}

void display_board(p6::Context& ctx, Board& board, int nb_row, int nb_column, Player current_player)
{
    draw_board(ctx, nb_row, nb_column);
    draw_noughts_and_crosses(board, ctx, nb_row, nb_column);
    highligh_hovered_cell(ctx, board, current_player, nb_row, nb_column);
}

bool is_cell_empty(Board& board, int index)
{
    return !board[index].get_cell_player();
}

int cell_index_to_board_index(cellIndex index, float nb_rows)
{
    return static_cast<int>(index.y * (nb_rows) + index.x);
}

void draw_noughts_and_crosses(const Board& board, p6::Context& ctx, int nb_rows, int nb_columns)
{
    for (int i = 0; i < board.getBoardSize(); i++) {
        if (board[i].get_cell_player() == Player::Noughts) {
            draw_nought(ctx, board.getCell(i).x, board.getCell(i).y, 2.f * ctx.aspect_ratio() / nb_columns, 2.f / nb_rows);
        }
        if (board[i].get_cell_player() == Player::Crosses) {
            draw_cross(ctx, board.getCell(i).x, board.getCell(i).y, 2.f * ctx.aspect_ratio() / nb_columns, 2.f / nb_rows);
        }
    }
}

void put_current_player_on_cell(Board& board, Player current_player, int index)
{
    board.assign_player_to_cell(index, current_player);
    board.player_played();
}

bool check_win_by_diagonal(Board& board, Player current_player, int pawn_index)
{
    if (pawn_index == 0 || pawn_index == 4 || pawn_index == 8) {
        if (board[0].get_cell_player() == current_player && board[4].get_cell_player() == current_player && board[8].get_cell_player() == current_player)
            return true;
    }

    if (pawn_index == 2 || pawn_index == 4 || pawn_index == 6) {
        if (board[2].get_cell_player() == current_player && board[4].get_cell_player() == current_player && board[6].get_cell_player() == current_player)
            return true;
    }
    return false;
}

bool check_win_by_line(Board& board, Player current_player, int pawn_index)
{
    int ligne_index = pawn_index / 3 * 3;
    if (board[ligne_index].get_cell_player() == current_player && board[ligne_index + 1].get_cell_player() == current_player && board[ligne_index + 2].get_cell_player() == current_player) {
        return true;
    }
    return false;
}

bool check_win_by_row(Board& board, Player current_player, int pawn_index)
{
    int row_index = pawn_index % 3;
    if (board[row_index].get_cell_player() == current_player && board[row_index + 3].get_cell_player() == current_player && board[row_index + 6].get_cell_player() == current_player) {
        return true;
    }
    return false;
}

bool check_win_after_pawn(Board& board, Player current_player, int pawn_index)
{
    if (board.is_full()) {
        return true;
    }
    if (check_win_by_diagonal(board, current_player, pawn_index)) {
        return true;
    }

    if (check_win_by_line(board, current_player, pawn_index)) {
        return true;
    }

    if (check_win_by_row(board, current_player, pawn_index)) {
        return true;
    }
    return false;
}

bool current_player_play_on_board(p6::Context& ctx, Board& board, Player current_player, float nb_rows, float nb_columns)
{
    if (auto clickedCell = mouse_position_to_index(ctx, nb_rows, nb_columns)) {
        int index = cell_index_to_board_index(*clickedCell, nb_rows);
        std::cout << index << std::endl;

        if (is_cell_empty(board, index)) {
            put_current_player_on_cell(board, current_player, index);
            if (check_win_after_pawn(board, current_player, index)) {
                display_winning_message(board, current_player);
                exit(EXIT_SUCCESS);
            }
            return true;
        }
        else {
            std::cout << "Not empty cell" << std::endl;
        }
    }
    else {
        return false;
    }
}

void highligh_hovered_cell(p6::Context& ctx, Board& board, Player current_player, float nb_rows, float nb_columns)
{
    if (auto clickedCell = mouse_position_to_index(ctx, nb_rows, nb_columns)) {
        int index = cell_index_to_board_index(*clickedCell, nb_rows);

        if (index <= 8 && is_cell_empty(board, index)) {
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

Player swap_player(Player current_player)
{
    if (current_player == Player::Noughts) {
        return Player::Crosses;
    }
    if (current_player == Player::Crosses) {
        return Player::Noughts;
    }
}