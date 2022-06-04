#include <cstdlib>
#include <vector>
#include "boardCell.hpp"

class Board {
public:
    Board(int rows, int columns, int pawn = 0)
        : _pawn_played(pawn)
    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                board.push_back(BoardCell(i, j));
            }
        }
    }

    BoardCell operator[](std::size_t index) const
    {
        return board.at(index);
    }

    int pawn_played() { return _pawn_played; }

    bool is_full()
    {
        return _pawn_played == 9;
    }

    void assign_player_to_cell(cellIndex cell, Player p, int nb_rows)
    {
        board.at(cell.y * nb_rows + cell.x).set_cell_player(p);
    }

    void assign_player_to_cell(int index, Player p)
    {
        board.at(index).set_cell_player(p);
    }

    void player_played() { _pawn_played++; }

    const cellIndex getCell(size_t index) const
    {
        return board.at(index).get_cell_index();
    }

    void update();

    const size_t getBoardSize() const
    {
        return board.size();
    }

private:
    std::vector<BoardCell> board;
    int                    _pawn_played;
};

void display_winning_message(Board& board, Player winning_player);
void display_board(p6::Context& ctx, Board& board, int nb_row, int nb_column, Player current_player);

bool is_cell_empty(Board& board, int index);
int  cell_index_to_board_index(cellIndex index, float nb_rows);

void draw_noughts_and_crosses(const Board& board, p6::Context& ctx, int nb_rows, int nb_columns);
void put_current_player_on_cell(Board& board, Player current_player, int index);

bool check_win_after_pawn(Board& board, Player current_player, int pawn_index);
bool check_win_by_diagonal(Board& board, Player current_player, int pawn_index);
bool check_win_by_line(Board& board, Player current_player, int pawn_index);
bool check_win_by_row(Board& board, Player current_player, int pawn_index);

bool   current_player_play_on_board(p6::Context& ctx, Board& board, Player current_player, float nb_rows, float nb_columns);
void   highligh_hovered_cell(p6::Context& ctx, Board& board, Player current_player, float nb_rows, float nb_columns);
Player swap_player(Player current_player);