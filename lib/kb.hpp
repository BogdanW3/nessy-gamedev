#ifndef KB_HPP
#define KB_HPP

namespace KB
{
	struct PlayerKBData
	{
		bool A, B, SELECT, START, UP, DOWN, LEFT, RIGHT;
	};

	char *const KB_CONTROL =				(char *)0x4016;
	volatile char *const KB_DATA1 = 		(char *)0x4016;
	volatile char *const KB_DATA2 =			(char *)0x4017;

	void tick();

#ifdef NONES
	extern PlayerKBData **PLAYER_KB_DATA;
#else
	PlayerKBData **const PLAYER_KB_DATA = (PlayerKBData **)0x1F00;
#endif
}; // namespace KB

#endif // !KB_HPP