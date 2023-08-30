#ifndef KB_HPP
#define KB_HPP

namespace KB
{
	struct PlayerKBData
	{
		bool A,B,SELECT,START,UP,DOWN,LEFT,RIGHT;
	};


	char* const KB_CONTROL =    (char*)0x4016;
	char* const KB_DATA1 =      (char*)0x4016;
	char* const KB_DATA2 =      (char*)0x4017;

	void tick();

	PlayerKBData** const PLAYER_KB_DATA = (PlayerKBData**)0x1F00;
}; // namespace KB

#endif // !KB_HPP