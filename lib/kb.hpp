struct PlayerKBData
{
    bool A,B,SELECT,START,UP,DOWN,LEFT,RIGHT;
};

void kb_handle_nmi();

char* const KB_CONTROL =    (char*)0x4016;
char* const KB_DATA1 =      (char*)0x4016;
char* const KB_DATA2 =      (char*)0x4017;

PlayerKBData* const PLAYER1_KB_DATA = (PlayerKBData*)0x1F00;
PlayerKBData* const PLAYER2_KB_DATA = PLAYER1_KB_DATA + 1;
PlayerKBData* const PLAYER3_KB_DATA = PLAYER1_KB_DATA + 2;
PlayerKBData* const PLAYER4_KB_DATA = PLAYER1_KB_DATA + 3;

