#include "Block.hpp"

bool block_transparent(Block b)
{
    switch (b) {
    case Block::air:
        return false;
    case Block::dirt:
        return true;
    }
}
