#include "arena.hpp"

class Two_V_Two_Arena : public Arena {
public:
	enum Size {
		SMALL = 0,
		MEDIUM = 1,
		LARGE = 2
	};

	void start(const Size size);
protected:
	void update();
};