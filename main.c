#include"function.h"


int main() {
	int i;

	srand((unsigned)time(NULL)); //����ǥ���� 
	setcursortype(NOCURSOR); //Ŀ�� ���� 
	title(); //����Ÿ��Ʋ ȣ�� 
	reset(); //������ ���� 

	while (1) {
		for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
			check_key(); //Ű�Է�Ȯ�� 
			draw_main(); //ȭ���� �׸� 
			Sleep(speed); //���Ӽӵ����� 
			if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
			//����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
			if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
				space_key_on = 0;
				break;
			}
		}
		drop_block(); // ����� ��ĭ ���� 
		check_level_up(); // �������� üũ 
		check_game_over(); //���ӿ����� üũ 
		if (new_block_on == 1) new_block(); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
	}
}

