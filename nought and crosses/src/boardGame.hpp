#include <cstdlib>
#include <vector>
#include "boardCell.hpp"

class Board {
public:
    Board(int rows, int columns)
    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                board.push_back(BoardCell(i, j));
            }
        }
    }

    const BoardCell operator[](std::size_t index) const
    {
        return board.at(index);
    }

    void assign_player_to_cell(cellIndex cell, Player p, int nb_rows)
    {
        board.at(cell.y * nb_rows + cell.x).set_cell_player(p);
    }

    void assign_player_to_cell(int index, Player p)
    {
        board.at(index).set_cell_player(p);
    }

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
};

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