#pragma once

#include "init.h"

void Title(void); //���ӽ���ȭ�� 
void Reset(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info); //������ �ʱ�ȭ 
void Reset_Main(Map_Info * map_info); //���� ������(main_org[][]�� �ʱ�ȭ)
void Reset_Main_Cpy(Map_Info * map_info); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void Draw_Map(Game_Info * game_info, UI_Info * ui_info); //���� ��ü �������̽��� ǥ�� 
void Draw_Main(Map_Info * map_info); //�������� �׸� 
void New_Block(Block_Info * block_info, Game_Info * game_info, Map_Info * map_info); //���ο� ����� �ϳ� ���� 
void Check_Key(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info); //Ű����� Ű�� �Է¹��� 
void Drop_Block(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info); //����� �Ʒ��� ����Ʈ�� 
int Non_Crush(int bx, int by, int b_rotation, int bType, Map_Info * map_info); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ�  
void Move_Left(Block_Info * block_info, Map_Info * map_info);	// left �������� ����� ������
void Move_Right(Block_Info * block_info, Map_Info * map_info);	// right �������� ����� ������
void Move_Up(Block_Info * block_info, Map_Info * map_info);		// ����� ȸ����Ŵ
void Move_Down(Block_Info * block_info, Map_Info * map_info);	// down �������� ����� ������
void Move_Bottom_Rotation(Block_Info * block_info, Map_Info * map_info);	// ����� �ظ� �Ǵ� ��Ͽ� ����� �� ȸ����Ŵ
void Check_Line(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info); //���� ����á������ �Ǵ��ϰ� ���� 
void Cal_Score_Line(Game_Info* game_info, Map_Info* map_info, int i); // ����� ���� �� ��� ���� ��ĭ �� ������ �Լ�
void Check_Level_Up(Game_Info * game_info, Map_Info * map_info, UI_Info * ui_info, Block_Info * block_info); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void Check_Game_Over(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void Pause(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info);//������ �Ͻ�������Ŵ 
void Setcursortype(CURSOR_TYPE c);
void Gotoxy(int x, int y);

CONSOLE_CURSOR_INFO SetCurInfo(int size, BOOL flag); // Ŀ�� ������ �޾Ƽ� �����ϰ� Ŀ�� ��ü�� ������
void File_Control(Game_Info * game_info, char * file_name, char * ch);
void Init_Reset(Game_Info * game_info); //�� ���Ӹ��� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ��Ŵ
void GenerateNextBlock(Block_Info *block_info);
void Set_New_Block(Block_Info * block_info, Game_Info * game_info); //New_Block���� �ʿ��� ���� ��������.

void Set_Map_Main(Map_Info * map_info, int index1, int index2, int status);
void Set_Map_Cpy(Map_Info * map_info, int index1, int index2, int status);
int Get_Map_Main(Map_Info * map_info, int index1, int index2);
int Get_Map_Cpy(Map_Info * map_info, int index1, int index2);
void Move_Space(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info);

void Set_New_Block(Block_Info * block_info, Game_Info * game_info) {
	(*block_info).bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
	(*block_info).by = 0;  //��� ������ġ y��ǥ(���� ��) 
	(*block_info).b_type = (*block_info).b_type_next; //���������� ������ 
	(*block_info).b_type_next = rand() % 7; //���� ���� ���� 
	(*block_info).b_rotation = 0;  //ȸ���� 0������ ������ 
	(*game_info).new_block_on = 0; //New_Block flag�� ��  
}
int get_UI_Position_X(void) {//��������ǥ�� ��ġ���� 

	return MAIN_X_ADJ + MAIN_X + 1;
}
void Init_Reset(Game_Info * game_info) {
	(*game_info).level = 1; //�������� �ʱ�ȭ 
	(*game_info).score = 0;
	(*game_info).level_goal = 1000;
	(*game_info).key = 0;
	(*game_info).crush_on = 0;
	(*game_info).cnt = 0;
	(*game_info).speed = 100;
}

void File_Control(Game_Info * game_info, char * file_name, char * ch) { //file control�Լ��� �б� �����ϱ� �ݱ� ����� ������.

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
			Gotoxy(0, 0);
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

void Gotoxy(int x, int y) { //Gotoxy�Լ� 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

CONSOLE_CURSOR_INFO SetCurInfo(int size, BOOL flag) { // Ŀ�� ������ �޾Ƽ� �����ϰ� Ŀ�� ��ü�� ������
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = size;
	CurInfo.bVisible = flag;
	return CurInfo;
}

void Setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo = SetCurInfo(1, FALSE);
		break;
	case SOLIDCURSOR:
		CurInfo = SetCurInfo(100, TRUE);
		break;
	case NORMALCURSOR:
		CurInfo = SetCurInfo(20, TRUE);
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	//Ư�� �ܼ�â�� Ŀ���� ������� ������ ���ϴ� �Լ��Դϴ�. 
	//ù��? ���ڷ� GetStdHandle()�� ���� �ڵ��� ��������
	//ǥ���ܼ������ �ڵ�(STD_OUTPUT_HANDLE)�� �Ѱ��ݴϴ�. 
	//�ι�° ���ڷ� �ܼ�â Ŀ���� �����͸� �Ѱ��ݴϴ�.

	return;
}

void Title(void) {
	int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
	int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
	int cnt; //Ÿ��Ʋ �������� ���� ����  

	Gotoxy(x, y + 0); printf("����������������"); Sleep(100);
	Gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
	Gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
	Gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
	Gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
	Gotoxy(x, y + 5); printf("      blog.naver.com/azure0777"); Sleep(100);
	Gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
	Gotoxy(x, y + 7); printf("Please Enter Any Key to Start..");
	Gotoxy(x, y + 9); printf("  ��   : Shift");
	Gotoxy(x, y + 10); printf("��  �� : Left / Right");
	Gotoxy(x, y + 11); printf("  ��   : Soft Drop");
	Gotoxy(x, y + 12); printf(" SPACE : Hard Drop");
	Gotoxy(x, y + 13); printf("   P   : Pause");
	Gotoxy(x, y + 14); printf("  ESC  : Quit");
	Gotoxy(x, y + 16); printf("BONUS FOR HARD DROPS / COMBOS");

	for (cnt = 0;; cnt++) { //cnt�� 1�� ������Ű�鼭 ��� �ݺ�    //�ϳ��� ���߿��� �� ��¦�̴� �ִϸ��̼�ȿ�� 
		if (_kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
		if (cnt % 200 == 0) { Gotoxy(x + 4, y + 1); printf("��"); }       //cnt�� 200���� ������ �������� ���� ǥ�� 
		if ((cnt % 200 - 100) == 0) { Gotoxy(x + 4, y + 1); printf("  "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
		if ((cnt % 350) == 0) { Gotoxy(x + 13, y + 2); printf("��"); } //������ ������ �ð����� ���� 
		if ((cnt % 350 - 100) == 0) { Gotoxy(x + 13, y + 2); printf("  "); }
		Sleep(10); // 00.1�� ������  
	}

	while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 
	return;
}


void Reset(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info) {

	File_Control(game_info, "score.dat", "rb"); //file control�Լ��� �б� �����ϱ� �ݱ� ����� ������.

	Init_Reset(game_info);	//�� ���Ӹ��� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ��Ŵ

	system("cls"); //ȭ������ 
	Reset_Main(map_info); // main_org�� �ʱ�ȭ 
	Draw_Map(game_info, ui_info); // ����ȭ���� �׸�
	Draw_Main(map_info); // �������� �׸� 

	(*block_info).b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
	New_Block(block_info, game_info, map_info); //���ο� ����� �ϳ� ����  

	return;
}

void Reset_Main(Map_Info* map_info) { // �������� ������ �����ϴ� main_org�� �ʱ�ȭ�Ѵ�
	int i;
	int j;

	for (i = 0; i < MAIN_Y; i++) { // main_org�� EMPTY, 0���� �ʱ�ȭ  
		for (j = 0; j < MAIN_X; j++) {
			Set_Map_Main(map_info, i, j, EMPTY);
			Set_Map_Cpy(map_info, i, j, 999); //main_cpy�� ���ӿ� ������ �ʴ� ���ڸ� ����
		}
	}
	for (j = 1; j < MAIN_X; j++) { //y ��ǥ���� 3�� ��ġ�� õ���� ����
		Set_Map_Main(map_info, 3, j, CEILLING);
	}
	for (i = 1; i < MAIN_Y - 1; i++) { //��, �� ���� ����  
		Set_Map_Main(map_info, i, 0, WALL);
		Set_Map_Main(map_info, i, MAIN_X - 1, WALL);
	}
	for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
		Set_Map_Main(map_info, MAIN_Y - 1, j, WALL);
	}

	return;
}

void Reset_Main_Cpy(Map_Info* map_info) { //main_cpy�� �ʱ�ȭ 
	int i;
	int j;

	for (i = 0; i < MAIN_Y; i++) {  //main_cpy�� main_org �� ���ϱ� ���� ���ӿ� ������ �ʴ� ���ڷ� �ʱ�ȭ�Ѵ�.            
		for (j = 0; j < MAIN_X; j++) {
			Set_Map_Cpy(map_info, i, j, 999);
		}
	}

	return;
}

void Draw_Map(Game_Info * game_info, UI_Info * ui_info) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
	int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
						 // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
	Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", (*game_info).level);
	Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - (*game_info).cnt);
	Gotoxy(get_UI_Position_X(), y + 2); printf("+-  N E X T  -+ ");
	Gotoxy(get_UI_Position_X(), y + 3); printf("|             | ");
	Gotoxy(get_UI_Position_X(), y + 4); printf("|             | ");
	Gotoxy(get_UI_Position_X(), y + 5); printf("|             | ");
	Gotoxy(get_UI_Position_X(), y + 6); printf("|             | ");
	Gotoxy(get_UI_Position_X(), y + 7); printf("+-- -  -  - --+ ");
	Gotoxy(get_UI_Position_X(), y + 8); printf(" YOUR SCORE :");
	Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE = y + 9); printf("        %6d", (*game_info).score);
	Gotoxy(get_UI_Position_X(), y + 10); printf(" LAST SCORE :");
	Gotoxy(get_UI_Position_X(), y + 11); printf("        %6d", (*game_info).last_score);
	Gotoxy(get_UI_Position_X(), y + 12); printf(" BEST SCORE :");
	Gotoxy(get_UI_Position_X(), y + 13); printf("        %6d", (*game_info).best_score);
	Gotoxy(get_UI_Position_X(), y + 15); printf("  ��   : Shift        SPACE : Hard Drop");
	Gotoxy(get_UI_Position_X(), y + 16); printf("��  �� : Left / Right   P   : Pause");
	Gotoxy(get_UI_Position_X(), y + 17); printf("  ��   : Soft Drop     ESC  : Quit");
	Gotoxy(get_UI_Position_X(), y + 20); printf("Original codes  :   blog.naver.com/azure0777");
	Gotoxy(get_UI_Position_X(), y + 23); printf("Refactoring codes : https://github.com/wlsdn2316/1-tetris-"); Sleep(100);

	return;
}

void Draw_Main(Map_Info * map_info) { //������ �׸��� �Լ� 
	int i, j;

	for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
		if (Get_Map_Main(map_info, 3, j) == EMPTY)
			Set_Map_Main(map_info, 3, j, CEILLING);
	}
	for (i = 0; i < MAIN_Y; i++) {
		for (j = 0; j < MAIN_X; j++) {
			if (Get_Map_Cpy(map_info, i, j) != Get_Map_Main(map_info, i, j)) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
												//�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
				Gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch (Get_Map_Main(map_info, i, j)) {
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
			Set_Map_Cpy(map_info, i, j, Get_Map_Main(map_info, i, j));
		}
	}

	return;
}

void New_Block(Block_Info * block_info, Game_Info * game_info, Map_Info * map_info) { //���ο� ��� ����  
	int i, j;

	//New_Block���� �ʿ��� �� ����
	Set_New_Block(block_info, game_info);

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
				Set_Map_Main(map_info, by + i, bx + j, ACTIVE_BLOCK);
		}
	}
	GenerateNextBlock(block_info); //������ϻ��� �Լ� �߰�!

	return;
}

void Check_Key(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info) {
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
				if (Non_Crush(bx - 1, by, b_rotation, b_type, map_info) == true)
					Move_Left(block_info, map_info);
				break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
			case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
				if (Non_Crush(bx + 1, by, b_rotation, b_type, map_info) == true)
					Move_Right(block_info, map_info);
				break;
			case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
				if (Non_Crush(bx, by + 1, b_rotation, b_type, map_info) == true)
					Move_Down(block_info, map_info);
				break;
			case UP: //���� ����Ű �������� 
				if (Non_Crush(bx, by, (b_rotation + 1) % 4, b_type, map_info) == true)
					Move_Up(block_info, map_info);
				//ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
				else if ((*game_info).crush_on == 1
					&& Non_Crush(bx, by - 1, (b_rotation + 1) % 4, b_type, map_info) == true)
					Move_Bottom_Rotation(block_info, map_info);
				//�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
			}//switch       
		}//if
		else { //����Ű�� �ƴѰ�� 
			switch ((*game_info).key) {
			case SPACE: //�����̽�Ű �������� 
				(*game_info).space_key_on = 1; //�����̽�Ű flag�� ��� 

				while ((*game_info).crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
					Drop_Block(game_info, block_info, map_info, ui_info);
					(*game_info).score += (*game_info).level; // hard drop ���ʽ�
					Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE); printf("        %6d", (*game_info).score); //���� ǥ��  
				}
				break;
			case P: //P(�빮��) �������� 
			case p: //p(�ҹ���) �������� 
				Pause(game_info, map_info, block_info, ui_info); //�Ͻ����� 
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

void Drop_Block(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info) {
	int i;
	int j;

	if ((*game_info).crush_on&&Non_Crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == true)
		(*game_info).crush_on = 0; //���� ��������� crush flag �� 

	if (Non_Crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == true)
		Move_Down(block_info, map_info); //���� ��������� ������ ��ĭ �̵� 

	if ((*game_info).crush_on&&Non_Crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == false) { //���� ��������ʰ� crush flag�� ���������� 
		for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
			for (j = 0; j < MAIN_X; j++) {
				if (Get_Map_Main(map_info, i, j) == ACTIVE_BLOCK)
					Set_Map_Main(map_info, i, j, INACTIVE_BLOCK);
			}
		}
		(*game_info).crush_on = 0; //crush flag�� �� 
		Check_Line(game_info, map_info, block_info, ui_info); //����üũ�� �� 
		(*game_info).new_block_on = 1; //���ο� ������ flag�� ��    
		return; //�Լ� ���� 
	}

	if (Non_Crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == false)
		(*game_info).crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��

	return;
}

int Non_Crush(int bx, int by, int b_rotation, int bType, Map_Info * map_info) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
			if (blocks[bType][b_rotation][i][j] == EXISTING_BLOCK
				&& Get_Map_Main(map_info, by + i, bx + j) > 0)
				return false;
		}
	}
	return true; //�ϳ��� �Ȱ�ġ�� true���� 
}

void Move_Left(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK) // �� blckos[b_type][b_rotation][i][j] == EXISTING_BLOCK �϶��� ��Ʈ���� ����� ���� ���̴�.
				Set_Map_Main(map_info, by + i, bx + j, EMPTY);
		}
	}
	for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j - 1, ACTIVE_BLOCK);
		}
	}
	(*block_info).bx--; //��ǥ�� �̵� 
}

void Move_Right(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j, EMPTY);
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j + 1, ACTIVE_BLOCK);
		}
	}
	(*block_info).bx++;
}

void Move_Up(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j, EMPTY);
		}
	}
	(*block_info).b_rotation = ((*block_info).b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
	b_rotation = (*block_info).b_rotation;

	for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j, ACTIVE_BLOCK);
		}
	}
}

void Move_Down(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j, EMPTY);
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i + 1, bx + j, ACTIVE_BLOCK);
		}
	}
	(*block_info).by++;
}

void Move_Bottom_Rotation(Block_Info * block_info, Map_Info * map_info)
{
	int i, j;

	int b_type = (*block_info).b_type;
	int b_rotation = (*block_info).b_rotation;
	int by = (*block_info).by;
	int bx = (*block_info).bx;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i, bx + j, EMPTY);
		}
	}
	(*block_info).b_rotation = ((*block_info).b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
	b_rotation = (*block_info).b_rotation;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == EXISTING_BLOCK)
				Set_Map_Main(map_info, by + i - 1, bx + j, ACTIVE_BLOCK);
		}
	}
	(*block_info).by--;
}

void Check_Line(Game_Info* game_info, Map_Info* map_info, Block_Info* block_info, UI_Info* ui_info) { //����� ����á���� �˻��ϰ� ������ ����ϴ� �Լ�
	int i;
	int j;
	int block_amount; //������ ��ϰ����� �����ϴ� ���� 
	int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

	for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
		block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
		for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ����� �� 
			if (Get_Map_Main(map_info, i, j) > 0)
				block_amount++;
		}
		if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
			if ((*game_info).level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
				(*game_info).score += 100 * (*game_info).level; //�����߰� 
				(*game_info).cnt++; //���� �� ���� ī��Ʈ ���� 
				combo++; //�޺��� ����  
			}
			Cal_Score_Line(game_info, map_info, i); //����� ���� �� ��� ���� ��ĭ�� ������ �Լ�
		}
		else i--;
	}

	if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
		if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
			Gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + (*block_info).by - 2);
			printf("%d COMBO!", combo);
			Sleep(500);
			(*game_info).score += (combo * (*game_info).level * 100);
			Reset_Main_Cpy(map_info); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
			//main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��
		}
		Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL);
		printf(" GOAL  : %5d", ((*game_info).cnt <= 10) ? 10 - (*game_info).cnt : 0);
		Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE);
		printf("        %6d", (*game_info).score);
	}

	return;
}

void Cal_Score_Line(Game_Info* game_info, Map_Info* map_info, int i) {  //����� ���� �� ��� ���� ��ĭ�� ������ �Լ�

	int k;
	int l;

	for (k = i; k > 1; k--) { //������ õ���� �ƴ� ��쿡�� ������ ��ĭ�� ��� ����  
		for (l = 1; l < MAIN_X - 1; l++) {
			if (Get_Map_Main(map_info, k - 1, l) != CEILLING)
				Set_Map_Main(map_info, k, l, Get_Map_Main(map_info, k - 1, l));
			if (Get_Map_Main(map_info, k - 1, l) == CEILLING)
				Set_Map_Main(map_info, k, l, EMPTY);
			//������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 		
		}
	}
}

void Check_Level_Up(Game_Info * game_info, Map_Info * map_info, UI_Info * ui_info, Block_Info * block_info) {
	int i, j;

	if ((*game_info).cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
		Draw_Main(map_info);
		(*game_info).level_up_on = 1; //������ flag�� ��� 
		(*game_info).level += 1; //������ 1 �ø� 
		(*game_info).cnt = 0; //���� �ټ� �ʱ�ȭ   

		for (i = 0; i < 4; i++) {
			Gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
			printf("             ");
			Gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
			printf("             ");
			Sleep(200);

			Gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
			printf("��LEVEL UP!��");
			Gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
			printf("��SPEED UP!��");
			Sleep(200);
		}
		Reset_Main_Cpy(map_info); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
							//(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

		for (i = MAIN_Y - 2; i > MAIN_Y - 2 - ((*game_info).level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
			for (j = 1; j < MAIN_X - 1; j++) {
				Set_Map_Main(map_info, i, j, INACTIVE_BLOCK);// ���� ������� ��� ä��� 
				Gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // ���� �����.. �̻����̰� 
				printf("��");
				Sleep(20);
			}
		}
		Sleep(100); //�������� �����ֱ� ���� delay 
		Check_Line(game_info, map_info, block_info, ui_info); //������� ��� ä��� �����
		//.Check_Line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
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

		Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_LEVEL); printf(" LEVEL : %5d", (*game_info).level); //����ǥ�� 
		Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - (*game_info).cnt); // ������ǥ ǥ�� 

	}
	return;
}

void Check_Game_Over(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) {

	int x = 5;
	int y = 5;

	for (int i = 1; i < MAIN_X - 2; i++) {
		if (Get_Map_Main(map_info, 3, i) > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
			Gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
			Gotoxy(x, y + 1); printf("��                              ��");
			Gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
			Gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
			Gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
			Gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", (*game_info).score);
			Gotoxy(x, y + 6); printf("��                              ��");
			Gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
			Gotoxy(x, y + 8); printf("��                              ��");
			Gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
			(*game_info).last_score = (*game_info).score; //���������� �ű� 

			if ((*game_info).score > (*game_info).best_score) { //�ְ��� ���Ž� 
				File_Control(game_info, "score.dat", "wb");
				Gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");
			}
			Sleep(1000);
			while (_kbhit()) _getch();
			(*game_info).key = _getch();
			Reset(game_info, block_info, ui_info, map_info);
		}
	}
	return;
}
void Pause(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) { //���� �Ͻ����� �Լ� 

	int x = 5;
	int y = 5;

	for (int i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
		Gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
		Gotoxy(x, y + 1); printf("��                              ��");
		Gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
		Gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
		Gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
		Gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
		Gotoxy(x, y + 6); printf("��                              ��");
		Gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
	}
	_getch(); //Ű�Է½ñ��� ��� 

	system("cls"); //ȭ�� ����� ���� �׸� 
	system("cls"); //ȭ�� ����� ���� �׸� 
	Reset_Main_Cpy(map_info);
	Draw_Main(map_info);
	Draw_Map(game_info, ui_info);
	GenerateNextBlock(block_info); //������� �����Լ�
	return;
}

void GenerateNextBlock(Block_Info *block_info)
{
	//������� ������ ���� �ݺ��Ǵ� ��ɾ�� �Լ��� �ٲپ����ϴ�.
	static int i = 1;
	static int j = 0;
	int nextBlock = (*block_info).b_type_next; //���� ����� ��Ŀ� '1'�� ��ġȮ��
	for (int i = 1; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[nextBlock][0][i][j] == EXISTING_BLOCK) { //����� ���� ��ġ �� 1�� ã�´�
				Gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("��");
			}
			else {
				Gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("  ");
			}
		}
	}
}
void Set_Map_Main(Map_Info * map_info, int index1, int index2, int status) { //map_main�� ���°��� ����
	(*map_info).main_org[index1][index2] = status;
}
void Set_Map_Cpy(Map_Info * map_info, int index1, int index2, int status) { //map_cpy�� ���°��� ����
	(*map_info).main_cpy[index1][index2] = status;
}
int Get_Map_Main(Map_Info * map_info, int index1, int index2) { //map_main�� ���°��� ��ȯ
	return (*map_info).main_org[index1][index2];
}
int Get_Map_Cpy(Map_Info * map_info, int index1, int index2) { //map_cpy�� ���°��� ��ȯ
	return (*map_info).main_cpy[index1][index2];
}
void Move_Space(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info) {
	(*game_info).space_key_on = 1; //�����̽�Ű flag�� ��� 

	while ((*game_info).crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
		Drop_Block(game_info, block_info, map_info, ui_info);
		(*game_info).score += (*game_info).level; // hard drop ���ʽ�
		Gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE); printf("        %6d", (*game_info).score); //���� ǥ��  
	}
}
