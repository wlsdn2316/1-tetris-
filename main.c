#include"function.h"


int main() {

	UI_Info ui_info;
	Block_Info block_info;
	Game_Info game_info;
	Map_Info map_info;

	memset(&ui_info, 0, sizeof(UI_Info));
	memset(&game_info, 0, sizeof(Game_Info));
	memset(&block_info, 0, sizeof(Block_Info));
	memset(&map_info, 0, sizeof(Map_Info));
	
	int i;

	srand((unsigned)time(NULL)); //����ǥ���� 
	setcursortype(NOCURSOR); //Ŀ�� ���� 
	title(); //����Ÿ��Ʋ ȣ�� 
	reset(&game_info, &block_info, &ui_info, &map_info); //������ ���� 

	while (1) {
		for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
			check_key(&game_info,&block_info,&ui_info,&map_info); //Ű�Է�Ȯ�� 
			draw_main(&map_info); //ȭ���� �׸� 
			Sleep(game_info.speed); //���Ӽӵ����� 
			if (game_info.crush_on&&check_crush(block_info.bx, block_info.by + 1, block_info.b_rotation,block_info.b_type,&map_info) == false) Sleep(100);
			//����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
			if (game_info.space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
				game_info.space_key_on = 0;
				break;
			}
		}
		drop_block(&game_info,&block_info,&map_info,&ui_info); // ����� ��ĭ ���� 
		check_level_up(&game_info,&map_info,&ui_info,&block_info); // �������� üũ 
		check_game_over(&game_info,&map_info,&block_info,&ui_info); //���ӿ����� üũ 
		if (game_info.new_block_on == 1) new_block(&block_info,&game_info,&map_info); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
	}
}

