#include "arena.hpp"

class One_V_One_Arena : public Arena {
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