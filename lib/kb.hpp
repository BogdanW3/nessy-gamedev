#ifndef KB_HPP
#define KB_HPP

namespace KB
{
	struct PlayerKBData
	{
		bool A, B, SELECT, START, UP, DOWN, LEFT, RIGHT;
	};

	volatile char *const KB_CONTROL =		(char *)0x4016;
	volatile char *const KB_DATA1 = 		(char *)0x4016;
	volatile char *const KB_DATA2 =			(char *)0x4017;

	void tick();

#ifdef NONES
	extern PlayerKBData *PLAYER_KB_DATA;
#else
	extern volatile PlayerKBData PLAYER_KB_DATA[4];
#endif
}; // namespace KB

#endif // !KB_HPP