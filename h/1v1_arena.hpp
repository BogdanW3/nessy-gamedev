#include "arena.hpp"

class One_V_One_Arena : public Arena
{
public:
	enum Size
	{
		SMALL = 0,
		MEDIUM = 1,
		LARGE = 2
	};

	void start(const Size size);

	static const uint8_t TILE_MAP_SMALL[];
	static const uint8_t TILE_MAP_MEDIUM[];
	static const uint8_t TILE_MAP_LARGE[];
	static const Colour TILE_COLOURS[2];

protected:
	void update();
};