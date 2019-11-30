#include"function.h"


int main() {

	//게임에 필요한 구조체 선언
	UI_Info ui_info;
	Block_Info block_info;
	Game_Info game_info;
	Map_Info map_info;

	//게임 초기화 부분
	Init_Game(&game_info, &block_info, &map_info, &ui_info);
	//게임 실행 부분
	Excute_Game(&game_info, &block_info, &map_info, &ui_info);
	
}

