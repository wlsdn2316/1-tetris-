#include"function.h"


int main() {

	//���ӿ� �ʿ��� ����ü ����
	UI_Info ui_info;
	Block_Info block_info;
	Game_Info game_info;
	Map_Info map_info;

	/*memeset �Լ��� � �޸��� ������ ���� ���ӵ� ������ � ��(byte����)���� 
	��� �����ϰ� ���� �� ��� �˴ϴ�. ���� �ڵ忡���� �ʱ�ȭ�� ��Ű������ ���ƽ��ϴ�.*/
	memset(&ui_info, 0, sizeof(UI_Info));
	memset(&game_info, 0, sizeof(Game_Info));
	memset(&block_info, 0, sizeof(Block_Info));
	memset(&map_info, 0, sizeof(Map_Info));

	int i;

	srand((unsigned)time(NULL)); //����ǥ���� 
	Setcursortype(NOCURSOR); //Ŀ�� ���� 
	Title(); //����Ÿ��Ʋ ȣ�� 
	Reset(&game_info, &block_info, &ui_info, &map_info); //������ ���� 

	while (1) {
		for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 

			Check_Key(&game_info, &block_info, &ui_info, &map_info); //Ű�Է�Ȯ�� 
			Draw_Main(&map_info); //ȭ���� �׸� 
			Sleep(game_info.speed); //���Ӽӵ����� 
			if (game_info.crush_on 
				&& Non_Crush(block_info.bx, block_info.by + 1, block_info.b_rotation, block_info.b_type, &map_info) == false) Sleep(100);
			//����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
			if (game_info.space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
				game_info.space_key_on = 0;
				break;
			}
		}

		Drop_Block(&game_info, &block_info, &map_info, &ui_info); // ����� ��ĭ ���� 
		Check_Level_Up(&game_info, &map_info, &ui_info, &block_info); // �������� üũ 
		Check_Game_Over(&game_info, &map_info, &block_info, &ui_info); //���ӿ����� üũ 
		if (game_info.new_block_on == 1) New_Block(&block_info, &game_info, &map_info); // �� �� flag�� �ִ� ��� ���ο� �� ���� 

	}
}