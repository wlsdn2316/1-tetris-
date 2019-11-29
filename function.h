#pragma once

#include "init.h"

void title(void); //���ӽ���ȭ�� 
void reset(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info); //������ �ʱ�ȭ 
void reset_main(Map_Info * map_info); //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(Map_Info * map_info); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void draw_map(Game_Info * game_info, UI_Info * ui_info); //���� ��ü �������̽��� ǥ�� 
void draw_main(Map_Info * map_info); //�������� �׸� 
void new_block(Block_Info * block_info, Game_Info * game_info, Map_Info * map_info); //���ο� ����� �ϳ� ���� 
void check_key(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info); //Ű����� Ű�� �Է¹��� 
void drop_block(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info); //����� �Ʒ��� ����Ʈ�� 
int non_crush(int bx, int by, int b_rotation, int bType, Map_Info * map_info); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ�  
void move_left(Block_Info * block_info, Map_Info * map_info);	// left �������� ����� ������
void move_right(Block_Info * block_info, Map_Info * map_info);	// right �������� ����� ������
void move_up(Block_Info * block_info, Map_Info * map_info);		// ����� ȸ����Ŵ
void move_down(Block_Info * block_info, Map_Info * map_info);	// down �������� ����� ������
void move_bottom_ratation(Block_Info * block_info, Map_Info * map_info);	// ����� �ظ� �Ǵ� ��Ͽ� ����� �� ȸ����Ŵ
void check_line(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(Game_Info * game_info, Map_Info * map_info, UI_Info * ui_info, Block_Info * block_info); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void pause(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info);//������ �Ͻ�������Ŵ 
void setcursortype(CURSOR_TYPE c);
void gotoxy(int x, int y);

CONSOLE_CURSOR_INFO setCurInfo(int size, BOOL flag); // Ŀ�� ������ �޾Ƽ� �����ϰ� Ŀ�� ��ü�� ������
void file_control(Game_Info * game_info, char * file_name, char * ch);
void init_reset(Game_Info * game_info); //�� ���Ӹ��� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ��Ŵ
void generateNextBlock(Block_Info *block_info);
void set_new_block(Block_Info * block_info, Game_Info * game_info); //new_block���� �ʿ��� ���� ��������.

void set_map_main(Map_Info * map_info, int index1, int index2, int status);
void set_map_cpy(Map_Info * map_info, int index1, int index2, int status);
int get_map_main(Map_Info * map_info, int index1, int index2);
int get_map_cpy(Map_Info * map_info, int index1, int index2);

void set_new_block(Block_Info * block_info, Game_Info * game_info) {
	(*block_info).bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
	(*block_info).by = 0;  //��� ������ġ y��ǥ(���� ��) 
	(*block_info).b_type = (*block_info).b_type_next; //���������� ������ 
	(*block_info).b_type_next = rand() % 7; //���� ���� ���� 
	(*block_info).b_rotation = 0;  //ȸ���� 0������ ������ 
	(*game_info).new_block_on = 0; //new_block flag�� ��  
}
int get_UI_Position_X(void) {//��������ǥ�� ��ġ���� 

	return MAIN_X_ADJ + MAIN_X + 1;
}
void init_reset(Game_Info * game_info) {
	(*game_info).level = 1; //�������� �ʱ�ȭ 
	(*game_info).score = 0;
	(*game_info).level_goal = 1000;
	(*game_info).key = 0;
	(*game_info).crush_on = 0;
	(*game_info).cnt = 0;
	(*game_info).speed = 100;
}

void file_control(Game_Info * game_info, char * file_name, char * ch) { //file control�Լ��� �б� �����ϱ� �ݱ� ����� ������.

	/*
	����ü ������ �����ؼ� ����ϰԵǸ� ������ ���̰�
	�ʹ� ������Ƿ� ������������ ���� �־��ݴϴ�.
	����ü ������ �ϳ� �̻� �ݺ��� �� ���� ������ �ٲ��ݴϴ�.
	������ ���� ���� ���� �̿��� ��쿡�� �ش�˴ϴ�.
	���� �ٲٷ��� �ϸ� ���������� ����� �� �����ϴ�.

	*/
	FILE * pfile = (*game_info).file;

	if (ch == "rb") {
		fopen_s(&pfile, file_name, ch);
		if (pfile == 0) { (*game_info).best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
		else {
			fscanf_s(pfile, "%d", &(*game_info).best_score); // ������ ������ �ְ������� �ҷ��� 
		}
	}
	else if (ch == "wb") {
		fopen_s(&pfile, file_name, ch); //score.dat�� ���� ����                
		if (pfile == NULL) {
			gotoxy(0, 0);
			printf("�������� �ʴ� ���� �Դϴ�. \n");
		}
		fprintf(pfile, "%d", (*game_info).score);

	}

	//��� �۾��Ŀ� �׻� close�� �ؾ��ϹǷ� 
	if (pfile == NULL) {
		printf("NULL ������ ������ �ϰ��ֽ��ϴ�.\n");
		return;
	}
	fclose(pfile); //���� ����	

}

void gotoxy(int x, int y) { //gotoxy�Լ� 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

CONSOLE_CURSOR_INFO setCurInfo(int size, BOOL flag) { // Ŀ�� ������ �޾Ƽ� �����ϰ� Ŀ�� ��ü�� ������
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = size;
	CurInfo.bVisible = flag;
	return CurInfo;
}

void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo = setCurInfo(1, FALSE);
		break;
	case SOLIDCURSOR:
		CurInfo = setCurInfo(100, TRUE);
		break;
	case NORMALCURSOR:
		CurInfo = setCurInfo(20, TRUE);
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	//Ư�� �ܼ�â�� Ŀ���� ������� ������ ���ϴ� �Լ��Դϴ�. 
	//ù��? ���ڷ� GetStdHandle()�� ���� �ڵ��� ��������
	//ǥ���ܼ������ �ڵ�(STD_OUTPUT_HANDLE)�� �Ѱ��ݴϴ�. 
	//�ι�° ���ڷ� �ܼ�â Ŀ���� �����͸� �Ѱ��ݴϴ�.

	return;
}

void title(void) {
	int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
	int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
	int cnt; //Ÿ��Ʋ �������� ���� ����  

	gotoxy(x, y + 0); printf("����������������"); Sleep(100);
	gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
	gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
	gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
	gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
	gotoxy(x, y + 5); printf("      blog.naver.com/azure0777"); Sleep(100);
	gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
	gotoxy(x, y + 7); printf("Please Enter Any Key to Start..");
	gotoxy(x, y + 9); printf("  ��   : Shift");
	gotoxy(x, y + 10); printf("��  �� : Left / Right");
	gotoxy(x, y + 11); printf("  ��   : Soft Drop");
	gotoxy(x, y + 12); printf(" SPACE : Hard Drop");
	gotoxy(x, y + 13); printf("   P   : Pause");
	gotoxy(x, y + 14); printf("  ESC  : Quit");
	gotoxy(x, y + 16); printf("BONUS FOR HARD DROPS / COMBOS");

	for (cnt = 0;; cnt++) { //cnt�� 1�� ������Ű�鼭 ��� �ݺ�    //�ϳ��� ���߿��� �� ��¦�̴� �ִϸ��̼�ȿ�� 
		if (_kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
		if (cnt % 200 == 0) { gotoxy(x + 4, y + 1); printf("��"); }       //cnt�� 200���� ������ �������� ���� ǥ�� 
		if ((cnt % 200 - 100) == 0) { gotoxy(x + 4, y + 1); printf("  "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
		if ((cnt % 350) == 0) { gotoxy(x + 13, y + 2); printf("��"); } //������ ������ �ð����� ���� 
		if ((cnt % 350 - 100) == 0) { gotoxy(x + 13, y + 2); printf("  "); }
		Sleep(10); // 00.1�� ������  
	}

	while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 
	return;
}


void reset(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info) {

	file_control(game_info, "score.dat", "rb"); //file control�Լ��� �б� �����ϱ� �ݱ� ����� ������.

	init_reset(game_info);	//�� ���Ӹ��� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ��Ŵ

	system("cls"); //ȭ������ 
	reset_main(map_info); // main_org�� �ʱ�ȭ 
	draw_map(game_info, ui_info); // ����ȭ���� �׸�
	draw_main(map_info); // �������� �׸� 

	(*block_info).b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
	new_block(block_info, game_info, map_info); //���ο� ����� �ϳ� ����  

	return;
}


void reset_main(Map_Info   * map_info) { //�������� �ʱ�ȭ  
	int i, j;

	for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
		for (j = 0; j < MAIN_X; j++) {
			set_map_main(map_info, i, j, EMPTY);
			set_map_cpy(map_info, i, j, 999); //���纻�� ���ӿ� ������ �ʴ� ���ڸ� ����
		}
	}
	for (j = 1; j < MAIN_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
		set_map_main(map_info, 3, j, CEILLING);
	}
	for (i = 1; i < MAIN_Y - 1; i++) { //�¿� ���� ����  
		set_map_main(map_info, i, 0, WALL);
		set_map_main(map_info, i, MAIN_X - 1, WALL);
	}
	for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
		set_map_main(map_info, MAIN_Y - 1, j, WALL);
	}

	return;
}

void reset_main_cpy(Map_Info * map_info) { //main_cpy�� �ʱ�ȭ 
	int i, j;

	for (i = 0; i < MAIN_Y; i++) {         //���纻�� ���ӿ� ������ �ʴ� ���ڸ� ����
		for (j = 0; j < MAIN_X; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
			set_map_cpy(map_info, i, j, 999);
		}
	}

	return;
}

void draw_map(Game_Info * game_info, UI_Info * ui_info) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
	int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
						 // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
	gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", (*game_info).level);
	gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - (*game_info).cnt);
	gotoxy(get_UI_Position_X(), y + 2); printf("+-  N E X T  -+ ");
	gotoxy(get_UI_Position_X(), y + 3); printf("|             | ");
	gotoxy(get_UI_Position_X(), y + 4); printf("|             | ");
	gotoxy(get_UI_Position_X(), y + 5); printf("|             | ");
	gotoxy(get_UI_Position_X(), y + 6); printf("|             | ");
	gotoxy(get_UI_Position_X(), y + 7); printf("+-- -  -  - --+ ");
	gotoxy(get_UI_Position_X(), y + 8); printf(" YOUR SCORE :");
	gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE = y + 9); printf("        %6d", (*game_info).score);
	gotoxy(get_UI_Position_X(), y + 10); printf(" LAST SCORE :");
	gotoxy(get_UI_Position_X(), y + 11); printf("        %6d", (*game_info).last_score);
	gotoxy(get_UI_Position_X(), y + 12); printf(" BEST SCORE :");
	gotoxy(get_UI_Position_X(), y + 13); printf("        %6d", (*game_info).best_score);
	gotoxy(get_UI_Position_X(), y + 15); printf("  ��   : Shift        SPACE : Hard Drop");
	gotoxy(get_UI_Position_X(), y + 16); printf("��  �� : Left / Right   P   : Pause");
	gotoxy(get_UI_Position_X(), y + 17); printf("  ��   : Soft Drop     ESC  : Quit");
	gotoxy(get_UI_Position_X(), y + 20); printf("Original codes  :   blog.naver.com/azure0777");
	gotoxy(get_UI_Position_X(), y + 23); printf("Refactoring codes : https://github.com/wlsdn2316/1-tetris-"); Sleep(100);

	return;
}

void draw_main(Map_Info * map_info) { //������ �׸��� �Լ� 
	int i, j;

	for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
		if (get_map_main(map_info, 3, j) == EMPTY) 
			set_map_main(map_info, 3, j, CEILLING);
	}
	for (i = 0; i < MAIN_Y; i++) {
		for (j = 0; j < MAIN_X; j++) {
			if (get_map_cpy(map_info,i,j) != get_map_main(map_info,i,j)) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
												//�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch (get_map_main(map_info,i,j)) {
				case EMPTY: //��ĭ��� 
					printf("  ");
					break;
				case CEILLING: //õ���� 
					printf(". ");
					break;
				case WALL: //����� 
					printf("��");
					break;
				case INACTIVE_BLOCK: //���� �� ���  
					printf("��");
					break;
				case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
					printf("��");
					break;
				}
			}
		}
	}
	for (i = 0; i < MAIN_Y; i++) { //�������� �׸� �� main_cpy�� ����  
		for (j = 0; j < MAIN_X; j++) {
			set_map_cpy(map_info, i, j, get_map_main(map_info, i, j));
		}
	}

	return;
}

void new_block(Block_Info * block_info, Game_Info * game_info, Map_Info * map_info) { //���ο� ��� ����  
	int i, j;

	//new_block���� �ʿ��� �� ����
	set_new_block(block_info, game_info);

	/*
	����ü ������ �����ؼ� ����ϰԵǸ� ������ ���̰�
	�ʹ� ������Ƿ� ������������ ���� �־��ݴϴ�.
	����ü ������ �ϳ� �̻� �ݺ��� �� ���� ������ �ٲ��ݴϴ�.
	������ ���� ���� ���� �̿��� ��쿡�� �ش�˴ϴ�.
	���� �ٲٷ��� �ϸ� ���������� ����� �� �����ϴ�.

	*/

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int bx = (*block_info).bx;
	int by = (*block_info).by;
	int b_type_next = (*block_info).b_type_next;

	for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j, ACTIVE_BLOCK);
		}
	}
	generateNextBlock(block_info); //������ϻ��� �Լ� �߰�!

	return;
}

void check_key(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info) {
	(*game_info).key = 0; //Ű�� �ʱ�ȭ  

	/*
	����ü ������ �����ؼ� ����ϰԵǸ� ������ ���̰�
	�ʹ� ������Ƿ� ������������ ���� �־��ݴϴ�.
	����ü ������ �ϳ� �̻� �ݺ��� �� ���� ������ �ٲ��ݴϴ�.
	������ ���� ���� ���� �̿��� ��쿡�� �ش�˴ϴ�.
	���� �ٲٷ��� �ϸ� ���������� ����� �� �����ϴ�.

	*/
	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int bx = (*block_info).bx;
	int by = (*block_info).by;
	int b_type_next = (*block_info).b_type_next;

	if (_kbhit()) { //Ű�Է��� �ִ� ���  
		(*game_info).key = _getch(); //Ű���� ����
		if ((*game_info).key == 224) { //����Ű�ΰ�� 
			do { (*game_info).key = _getch(); } while ((*game_info).key == 224);//����Ű���ð��� ���� 

			switch ((*game_info).key) {
			case LEFT: //����Ű ��������  
				if (non_crush(bx - 1, by, b_rotation, b_type, map_info) == true)
					move_left(block_info, map_info);
				break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
			case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
				if (non_crush(bx + 1, by, b_rotation, b_type, map_info) == true)
					move_right(block_info, map_info);
				break;
			case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
				if (non_crush(bx, by + 1, b_rotation, b_type, map_info) == true)
					move_down(block_info, map_info);
				break;
			case UP: //���� ����Ű �������� 
				if (non_crush(bx, by, (b_rotation + 1) % 4, b_type, map_info) == true)
					move_up(block_info, map_info);
				//ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
				else if ((*game_info).crush_on == 1
					&& non_crush(bx, by - 1, (b_rotation + 1) % 4, b_type, map_info) == true)
					move_bottom_ratation(block_info, map_info);
				//�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
			}//switch       
		}//if
		else { //����Ű�� �ƴѰ�� 
			switch ((*game_info).key) {
			case SPACE: //�����̽�Ű �������� 
				(*game_info).space_key_on = 1; //�����̽�Ű flag�� ��� 

				while ((*game_info).crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
					drop_block(game_info, block_info, map_info, ui_info);
					(*game_info).score += (*game_info).level; // hard drop ���ʽ�
					gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE); printf("        %6d", (*game_info).score); //���� ǥ��  
				}
				break;
			case P: //P(�빮��) �������� 
			case p: //p(�ҹ���) �������� 
				pause(game_info, map_info, block_info, ui_info); //�Ͻ����� 
				break;
			case ESC: //ESC�������� 
				system("cls"); //ȭ���� ����� 
				exit(0); //�������� 
			}//switch
		}//else
	}//if
	while (_kbhit()) _getch(); //Ű���۸� ��� 
	/* Ű ���۸� ����ִ� ������ �ش� �����߿� �Է��� ���� �ʾҴµ�
	�Է��� ���� ��� ���ۿ� �ش� Ű���� �� �ְ� �˴ϴ�. �̰���
	�Է°��� �ʿ��Ҷ� ȣ���ϸ� ���ϴ� �Է°��� �ƴ϶� ���߿� ������ Ű �� ��
	�ϳ��� ���� �˴ϴ�. ���� Ű ���۴� �Է��� ������ ���� ���۸� ������ �մϴ�.*/

	return;
}

void drop_block(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info) {
	int i;
	int j;

	if ((*game_info).crush_on&&non_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == true)
		(*game_info).crush_on = 0; //���� ��������� crush flag �� 
	if ((*game_info).crush_on&&non_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == false) { //���� ��������ʰ� crush flag�� ���������� 
		for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
			for (j = 0; j < MAIN_X; j++) {
				if (get_map_main(map_info, i, j) == ACTIVE_BLOCK)
					set_map_main(map_info, i, j, INACTIVE_BLOCK);
			}
		}
		(*game_info).crush_on = 0; //flag�� �� 
		check_line(game_info, map_info, block_info, ui_info); //����üũ�� �� 
		(*game_info).new_block_on = 1; //���ο� ������ flag�� ��    
		return; //�Լ� ���� 
	}
	if (non_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == true)
		move_down(block_info, map_info); //���� ��������� ������ ��ĭ �̵� 
	if (non_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == false)
		(*game_info).crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��

	return;
}

int non_crush(int bx, int by, int b_rotation, int bType, Map_Info * map_info) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
			if (blocks[bType][b_rotation][i][j] == EXISTING_BLOCK 
				&& get_map_main(map_info,by + i,bx + j) > 0)
				return false;
		}
	}
	return true; //�ϳ��� �Ȱ�ġ�� true���� 
}

void move_left(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK) // �� blckos[b_type][b_rotation][i][j] == EXISTING_BLOCK �϶��� ��Ʈ���� ����� ���� ���̴�.
				set_map_main(map_info, by + i, bx + j, EMPTY); 
		}
	}
	for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j - 1, ACTIVE_BLOCK);
		}
	}
	(*block_info).bx--; //��ǥ�� �̵� 
}

void move_right(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j, EMPTY);
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j + 1, ACTIVE_BLOCK);
		}
	}
	(*block_info).bx++;
}

void move_up(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j, EMPTY);
		}
	}
	(*block_info).b_rotation = ((*block_info).b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
	b_rotation = (*block_info).b_rotation;

	for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j, ACTIVE_BLOCK);
		}
	}
}

void move_down(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j, EMPTY);
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i + 1, bx + j, ACTIVE_BLOCK);
		}
	}
	(*block_info).by++;
}

void move_bottom_ratation(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i, bx + j, EMPTY);
		}
	}
	(*block_info).b_rotation = ((*block_info).b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
	b_rotation = (*block_info).b_rotation;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				set_map_main(map_info, by + i - 1, bx + j, ACTIVE_BLOCK); 
		}
	}
	(*block_info).by--;
}

void check_line(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) {
	int i;
	int j;
	int k;
	int l;
	int block_amount; //������ ��ϰ����� �����ϴ� ���� 
	int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

	for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
		block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
		for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 �� 
			if (get_map_main(map_info,i,j) > 0)
				block_amount++;
		}
		if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
			if ((*game_info).level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
				(*game_info).score += 100 * (*game_info).level; //�����߰� 
				(*game_info).cnt++; //���� �� ���� ī��Ʈ ���� 
				combo++; //�޺��� ����  
			}
			for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
				for (l = 1; l < MAIN_X - 1; l++) {
					if (get_map_main(map_info, k - 1, l) != CEILLING)
						set_map_main(map_info, k, l, get_map_main(map_info, k - 1, l));
					if (get_map_main(map_info, k - 1, l) == CEILLING)
						set_map_main(map_info, k, l, EMPTY);
					//������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
				}
			}
		}
		else i--;
	}

	if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
		if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + (*block_info).by - 2);
			printf("%d COMBO!", combo);
			Sleep(500);
			(*game_info).score += (combo*(*game_info).level * 100);
			reset_main_cpy(map_info); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
			//(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
		}
		gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL);
		printf(" GOAL  : %5d", ((*game_info).cnt <= 10) ? 10 - (*game_info).cnt : 0);
		gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE);
		printf("        %6d", (*game_info).score);
	}

	return;
}
void check_level_up(Game_Info * game_info, Map_Info * map_info, UI_Info * ui_info, Block_Info * block_info) {
	int i, j;

	if ((*game_info).cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
		draw_main(map_info);
		(*game_info).level_up_on = 1; //������ flag�� ��� 
		(*game_info).level += 1; //������ 1 �ø� 
		(*game_info).cnt = 0; //���� �ټ� �ʱ�ȭ   

		for (i = 0; i < 4; i++) {
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
			printf("             ");
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
			printf("             ");
			Sleep(200);

			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
			printf("��LEVEL UP!��");
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
			printf("��SPEED UP!��");
			Sleep(200);
		}
		reset_main_cpy(map_info); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
							//(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

		for (i = MAIN_Y - 2; i > MAIN_Y - 2 - ((*game_info).level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
			for (j = 1; j < MAIN_X - 1; j++) {
				set_map_main(map_info, i, j, INACTIVE_BLOCK);// ���� ������� ��� ä��� 
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // ���� �����.. �̻����̰� 
				printf("��");
				Sleep(20);
			}
		}
		Sleep(100); //�������� �����ֱ� ���� delay 
		check_line(game_info, map_info, block_info, ui_info); //������� ��� ä��� �����
		//.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
		switch ((*game_info).level) { //�������� �ӵ��� ��������. 
		case 2:
			(*game_info).speed = 50;
			break;
		case 3:
			(*game_info).speed = 25;
			break;
		case 4:
			(*game_info).speed = 10;
			break;
		case 5:
			(*game_info).speed = 5;
			break;
		case 6:
			(*game_info).speed = 4;
			break;
		case 7:
			(*game_info).speed = 3;
			break;
		case 8:
			(*game_info).speed = 2;
			break;
		case 9:
			(*game_info).speed = 1;
			break;
		case 10:
			(*game_info).speed = 0;
			break;
		}
		(*game_info).level_up_on = 0; //������ flag����

		gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_LEVEL); printf(" LEVEL : %5d", (*game_info).level); //����ǥ�� 
		gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - (*game_info).cnt); // ������ǥ ǥ�� 

	}
	return;
}

void check_game_over(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) {

	int x = 5;
	int y = 5;

	for (int i = 1; i < MAIN_X - 2; i++) {
		if (get_map_main(map_info,3,i) > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
			gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
			gotoxy(x, y + 1); printf("��                              ��");
			gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
			gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
			gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
			gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", (*game_info).score);
			gotoxy(x, y + 6); printf("��                              ��");
			gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
			gotoxy(x, y + 8); printf("��                              ��");
			gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
			(*game_info).last_score = (*game_info).score; //���������� �ű� 

			if ((*game_info).score > (*game_info).best_score) { //�ְ��� ���Ž� 
				file_control(game_info, "score.dat", "wb");
				gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");
			}
			Sleep(1000);
			while (_kbhit()) _getch();
			(*game_info).key = _getch();
			reset(game_info, block_info, ui_info, map_info);
		}
	}
	return;
}
void pause(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) { //���� �Ͻ����� �Լ� 

	int x = 5;
	int y = 5;

	for (int i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
		gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		gotoxy(x, y + 1); printf("��                              ��");
		gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
		gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
		gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
		gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
		gotoxy(x, y + 6); printf("��                              ��");
		gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	}
	_getch(); //Ű�Է½ñ��� ��� 

	system("cls"); //ȭ�� ����� ���� �׸� 
	system("cls"); //ȭ�� ����� ���� �׸� 
	reset_main_cpy(map_info);
	draw_main(map_info);
	draw_map(game_info, ui_info);
	generateNextBlock(block_info); //������� �����Լ�
	return;
}

void generateNextBlock(Block_Info *block_info)
{
	//������� ������ ���� �ݺ��Ǵ� ��ɾ�� �Լ��� �ٲپ����ϴ�.
	static int i = 1;
	static int j = 0;
	int nextBlock = (*block_info).b_type_next; //���� ����� ��Ŀ� '1'�� ��ġȮ��
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[nextBlock][0][i][j] == EXISTING_BLOCK) { //����� ���� ��ġ �� 1�� ã�´�
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("��");
			}
			else {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("  ");
			}
		}
	}
}
void set_map_main(Map_Info * map_info, int index1, int index2, int status) { //map_main�� ���°��� ����
	(*map_info).main_org[index1][index2] = status;
}
void set_map_cpy(Map_Info * map_info, int index1, int index2, int status) { //map_cpy�� ���°��� ����
	(*map_info).main_cpy[index1][index2] = status;
}
int get_map_main(Map_Info * map_info, int index1, int index2) { //map_main�� ���°��� ��ȯ
	return (*map_info).main_org[index1][index2];
}
int get_map_cpy(Map_Info * map_info, int index1, int index2) { //map_cpy�� ���°��� ��ȯ
	return (*map_info).main_cpy[index1][index2];
}