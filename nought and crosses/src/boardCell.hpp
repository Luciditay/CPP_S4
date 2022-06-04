#pragma once

#include <cstdlib>
#include <optional>
#include "board.hpp"

enum class Player {
    Noughts,
    Crosses,
};

class BoardCell {
private:
    cellIndex             _index;
    std::optional<Player> _player;

public:
    BoardCell(int x, int y);

    cellIndex get_cell_index() const
    {
        return _index;
    }

    std::optional<Player> get_cell_player() const
    {
        return _player;
    }

    void set_cell_player(Player p)
    {
        _player = p;
    }
};