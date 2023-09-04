#include "arena.hpp"

class FFA_Arena : public Arena {
public:
	enum Size {
		SMALL = 0,
		MEDIUM = 1,
		LARGE = 2,
		GIANT = 3
	};

	void start(const Size size);

	static const Colour TILE_COLOURS[4];
protected:
	void update();
};