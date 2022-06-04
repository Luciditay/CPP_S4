#include "boardCell.hpp"

BoardCell::BoardCell(int x, int y)
    : _index(x, y), _player(std::nullopt)
{
}
