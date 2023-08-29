#ifndef ARENA_H
#define ARENA_H

#include "../h/player.hpp"


const constexpr PLAYER_COUNT = 4;

class Arena 
{
	public:
		uint8_t inline getWidth() const;
		uint8_t inline getHeight() const;
		bool inline isPaintable(uint8_t x, uint8_t y) const;
		void paint(
			const Player& player, 
			uint8_t x, 
			uint8_t y
		);

	private:
		const constexpr uint8_t height;
		const constexpr uint8_t width;
		uint8_t tile_map[width][height]
		Player player[PLAYER_COUNT];
		Arena(
			const constexpr uint8_t width, 
			const constexpr uint8_t height
		);
		
		void fillTileMap();
		

}		

#endif // !ARENA_H

