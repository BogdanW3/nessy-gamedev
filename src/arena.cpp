#include "../h/arena.hpp"
#include "../h/tile.hpp"

constexpr uint8_t inline Arena::getWidth() const 
{
    return width;
}

constexpr uint8_t inline Arena::getHeight() const
{
    return height
}

bool inline Arena::isPaintable(uint8_t x, uint8_t y) const
{
    if(x >= width) return false;
    if(y >= height) return false;
    uint8_t tile = tile_map[x][y]
    return !(tile & TILE_WALL_MASK)
}

void Arena::paint(uint8_t player_id, uint8_t x, uint8_t y)
{
    if(player_id >= PLAYER_COUNT) return;
    if(!isPaintable(x,y)) return;
    uint8_t tile = tile_map[x][y];

    //Decrease score of last owner (if they exists)
    if(tile & TILE_TAKEN_MASK) {
        player[tile & TILE_OWNER_MASK].decreaseScore();
    }

    //Set taken bit;
    tile |= TILE_TAKEN_MASK;
    
    //Write tile owner ID;
    tile &= ~TILE_OWNER_MASK;
    tile |= player_id & TILE_OWNER_MASK;

    //Increase score of new owner
    player[player_id].increaseScore();
 
}
