#pragma once

#include "init.h"

void title(void); //���ӽ���ȭ��.
void reset(void); //������ �ʱ�ȭ 
void reset_main(void); //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(void); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void draw_map(void); //���� ��ü �������̽��� ǥ�� 
void draw_main(void); //�������� �׸� 
void new_block(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void pause(void);//������ �Ͻ�������Ŵ 

CONSOLE_CURSOR_INFO setCurInfo(int size, BOOL flag); // Ŀ�� ������ �޾Ƽ� �����ϰ� Ŀ�� ��ü�� ������
void file_control(FILE * file, char * file_name, char * ch);
void init_reset(void); //�� ���Ӹ��� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ��Ŵ

void init_reset(void) {
	level = 1; //�������� �ʱ�ȭ 
	score = 0;
	level_goal = 1000;
	key = 0;
	crush_on = 0;
	cnt = 0;
	speed = 100;
}

void file_control(FILE * file, char * file_name, char * ch) { //file control�Լ��� �б� �����ϱ� �ݱ� ����� ������.

	if (ch == "rt") {
		fopen_s(&file, file_name, ch);
		if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
		else {
			fscanf_s(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
		}
	}
	else if (ch == "wt") {
		fopen_s(&file, file_name, ch); //score.dat�� ���� ����                
		if (file == NULL) {	
			gotoxy(0, 0); 
			printf("�������� �ʴ� ���� �Դϴ�. \n");
		}
		fprintf(file, "%d", score);

	}
	
	//��� �۾��Ŀ� �׻� close�� �ؾ��ϹǷ� 
	if (file == NULL) {
		printf("NULL ������ ������ �ϰ��ֽ��ϴ�.\n");
		return;
	}
	fclose(file); //���� ����	
	
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
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);

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


void reset(void) {

	FILE *file;
	fopen_s(&file, "score.dat", "rt"); // score.dat������ ���� 
	if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
	else {
		fscanf_s(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
		fclose(file); //���� ���� 
	}

	level = 1; //�������� �ʱ�ȭ 
	score = 0;
	level_goal = 1000;
	key = 0;
	crush_on = 0;
	cnt = 0;
	speed = 100;

	system("cls"); //ȭ������ 
	reset_main(); // main_org�� �ʱ�ȭ 
	draw_map(); // ����ȭ���� �׸�
	draw_main(); // �������� �׸� 

	b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
	new_block(); //���ο� ����� �ϳ� ����  

	return;
}

void reset_main(void) { //�������� �ʱ�ȭ  
	int i, j;

	for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
		for (j = 0; j < MAIN_X; j++) {
			main_org[i][j] = 0;
			main_cpy[i][j] = 100;
		}
	}
	for (j = 1; j < MAIN_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
		main_org[3][j] = CEILLING;
	}
	for (i = 1; i < MAIN_Y - 1; i++) { //�¿� ���� ����  
		main_org[i][0] = WALL;
		main_org[i][MAIN_X - 1] = WALL;
	}
	for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
		main_org[MAIN_Y - 1][j] = WALL;
	}

	return;
}

void reset_main_cpy(void) { //main_cpy�� �ʱ�ȭ 
	int i, j;

	for (i = 0; i < MAIN_Y; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
		for (j = 0; j < MAIN_X; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
			main_cpy[i][j] = 100;
		}
	}

	return;
}

void draw_map(void) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
	int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
						 // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
	gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
	gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt);
	gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+ ");
	gotoxy(STATUS_X_ADJ, y + 3); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 4); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
	gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+ ");
	gotoxy(STATUS_X_ADJ, y + 8); printf(" YOUR SCORE :");
	gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
	gotoxy(STATUS_X_ADJ, y + 10); printf(" LAST SCORE :");
	gotoxy(STATUS_X_ADJ, y + 11); printf("        %6d", last_score);
	gotoxy(STATUS_X_ADJ, y + 12); printf(" BEST SCORE :");
	gotoxy(STATUS_X_ADJ, y + 13); printf("        %6d", best_score);
	gotoxy(STATUS_X_ADJ, y + 15); printf("  ��   : Shift        SPACE : Hard Drop");
	gotoxy(STATUS_X_ADJ, y + 16); printf("��  �� : Left / Right   P   : Pause");
	gotoxy(STATUS_X_ADJ, y + 17); printf("  ��   : Soft Drop     ESC  : Quit");
	gotoxy(STATUS_X_ADJ, y + 20); printf("blog.naver.com/azure0777");

	return;
}

void draw_main(void) { //������ �׸��� �Լ� 
	int i, j;

	for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
		if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
	}
	for (i = 0; i < MAIN_Y; i++) {
		for (j = 0; j < MAIN_X; j++) {
			if (main_cpy[i][j] != main_org[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
												//�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch (main_org[i][j]) {
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
			main_cpy[i][j] = main_org[i][j];
		}
	}

	return;
}

void new_block(void) { //���ο� ��� ����  
	int i, j;

	bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
	by = 0;  //��� ������ġ y��ǥ(���� ��) 
	b_type = b_type_next; //���������� ������ 
	b_type_next = rand() % 7; //���� ���� ���� 
	b_rotation = 0;  //ȸ���� 0������ ������ 

	new_block_on = 0; //new_block flag�� ��  

	for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
		}
	}
	for (i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				printf("��");
			}
			else {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				printf("  ");
			}
		}
	}

	return;
}

void check_key(void) {
	key = 0; //Ű�� �ʱ�ȭ  

	if (_kbhit()) { //Ű�Է��� �ִ� ���  
		key = _getch(); //Ű���� ����
		if (key == 224) { //����Ű�ΰ�� 
			do { key = _getch(); } while (key == 224);//����Ű���ð��� ���� 
			switch (key) {
			case LEFT: //����Ű ��������  
				if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
				break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
			case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
				if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
				break;
			case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
				if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
				break;
			case UP: //���� ����Ű �������� 
				if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
				//ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
				else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
			}                    //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
		}
		else { //����Ű�� �ƴѰ�� 
			switch (key) {
			case SPACE: //�����̽�Ű �������� 
				space_key_on = 1; //�����̽�Ű flag�� ��� 
				while (crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
					drop_block();
					score += level; // hard drop ���ʽ�
					gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //���� ǥ��  
				}
				break;
			case P: //P(�빮��) �������� 
			case p: //p(�ҹ���) �������� 
				pause(); //�Ͻ����� 
				break;
			case ESC: //ESC�������� 
				system("cls"); //ȭ���� ����� 
				exit(0); //�������� 
			}
		}
	}
	while (_kbhit()) _getch(); //Ű���۸� ��� 

	return;
}

void drop_block(void) {
	int i, j;

	if (crush_on&&check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //���� ��������� crush flag �� 
	if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) { //���� ��������ʰ� crush flag�� ���������� 
		for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
			for (j = 0; j < MAIN_X; j++) {
				if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
			}
		}
		crush_on = 0; //flag�� �� 
		new_block_on = 1;
		check_line(); //����üũ�� �� 
		 //���ο� ������ flag�� ��    
		return; //�Լ� ���� 
	}
	if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //���� ��������� ������ ��ĭ �̵� 
	if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��

	return;
}

int check_crush(int bx, int by, int b_rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
			if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
		}
	}
	return true; //�ϳ��� �Ȱ�ġ�� true���� 
}

void move_block(int dir) { //����� �̵���Ŵ 
	int i, j;

	switch (dir) {
	case LEFT: //���ʹ��� 
		for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
			}
		}
		bx--; //��ǥ�� �̵� 
		break;

	case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
			}
		}
		bx++;
		break;

	case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
			}
		}
		by++;
		break;

	case UP: //Ű���� ���� �������� ȸ����Ŵ. 
		for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
		for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
			}
		}
		break;

	case 100: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
			  //�̸� ���۽�Ű�� Ư������ 
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
			}
		}
		by--;
		break;
	}

	return;
}

void check_line(void) {
	int i, j, k, l;

	int block_amount; //������ ��ϰ����� �����ϴ� ���� 
	int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

	for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
		block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
		for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 �� 
			if (main_org[i][j] > 0) block_amount++;
		}
		if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
			if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
				score += 100 * level; //�����߰� 
				cnt++; //���� �� ���� ī��Ʈ ���� 
				combo++; //�޺��� ����  
			}
			for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
				for (l = 1; l < MAIN_X - 1; l++) {
					if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
					if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
					//������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
				}
			}
		}
		else i--;
	}
	if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
		if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
			Sleep(500);
			score += (combo*level * 100);
			reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
			//(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
		}
		gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
		gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
	}
	return;
}

void check_level_up(void) {
	int i, j;

	if (cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
		draw_main();
		level_up_on = 1; //������ flag�� ��� 
		level += 1; //������ 1 �ø� 
		cnt = 0; //���� �ټ� �ʱ�ȭ   

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
		reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
							//(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

		for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
			for (j = 1; j < MAIN_X - 1; j++) {
				main_org[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // ���� �����.. �̻����̰� 
				printf("��");
				Sleep(20);
			}
		}
		Sleep(100); //�������� �����ֱ� ���� delay 
		check_line(); //������� ��� ä��� �����
//.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
		switch (level) { //�������� �ӵ��� ��������. 
		case 2:
			speed = 50;
			break;
		case 3:
			speed = 25;
			break;
		case 4:
			speed = 10;
			break;
		case 5:
			speed = 5;
			break;
		case 6:
			speed = 4;
			break;
		case 7:
			speed = 3;
			break;
		case 8:
			speed = 2;
			break;
		case 9:
			speed = 1;
			break;
		case 10:
			speed = 0;
			break;
		}
		level_up_on = 0; //������ flag����

		gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //����ǥ�� 
		gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // ������ǥ ǥ�� 

	}

	return;
}

void check_game_over(void) {
	int i;

	int x = 5;
	int y = 5;

	for (i = 1; i < MAIN_X - 2; i++) {
		if (main_org[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
			gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
			gotoxy(x, y + 1); printf("��                              ��");
			gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
			gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
			gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
			gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score);
			gotoxy(x, y + 6); printf("��                              ��");
			gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
			gotoxy(x, y + 8); printf("��                              ��");
			gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
			last_score = score; //���������� �ű� 

			if (score > best_score) { //�ְ��� ���Ž� 
				FILE* file;
				fopen_s(&file, "score.dat", "wt"); //score.dat�� ���� ����                

				gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

				if (file == 0) { //���� �����޼���  
					gotoxy(0, 0);
					printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
				}
				else {
					fprintf(file, "%d", score);
					fclose(file);
				}
			}
			Sleep(1000);
			while (_kbhit()) _getch();
			key = _getch();
			reset();
		}
	}
	return;
}

void pause(void) { //���� �Ͻ����� �Լ� 
	int i, j;

	int x = 5;
	int y = 5;

	for (i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
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
	reset_main_cpy();
	draw_main();
	draw_map();

	for (i = 1; i < 3; i++) { // ������� �׸� 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("��");
			}
			else {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("  ");
			}
		}
	}
	return;
} //��! 
