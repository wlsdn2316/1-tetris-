#include"function.h"


int main() {

	//���ӿ� �ʿ��� ����ü ����
	UI_Info ui_info;
	Block_Info block_info;
	Game_Info game_info;
	Map_Info map_info;

	//���� �ʱ�ȭ �κ�
	Init_Game(&game_info, &block_info, &map_info, &ui_info);
	//���� ���� �κ�
	Excute_Game(&game_info, &block_info, &map_info, &ui_info);
	
}

