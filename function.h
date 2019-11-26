#pragma once

#include "init.h"

void title(void); //게임시작화면 
void reset(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info); //게임판 초기화 
void reset_main(Map_Info * map_info); //메인 게임판(main_org[][]를 초기화)
void reset_main_cpy(Map_Info * map_info); //copy 게임판(main_cpy[][]를 초기화)
void draw_map(Game_Info * game_info, UI_Info * ui_info); //게임 전체 인터페이스를 표시 
void draw_main(Map_Info * map_info); //게임판을 그림 
void new_block(Block_Info * block_info, Game_Info * game_info, Map_Info * map_info); //새로운 블록을 하나 만듦 
void check_key(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info); //키보드로 키를 입력받음 
void drop_block(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info); //블록을 아래로 떨어트림 
int check_crush(int bx, int by, int b_rotation, int bType, Map_Info * map_info); //bx, by위치에 rotation회전값을 같는 경우 충돌 판단 
void move_block(int dir, Block_Info * block_info, Map_Info * map_info); //dir방향으로 블록을 움직임 
void check_line(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info); //줄이 가득찼는지를 판단하고 지움 
void check_level_up(Game_Info * game_info, Map_Info * map_info, UI_Info * ui_info, Block_Info * block_info); //레벨목표가 달성되었는지를 판단하고 levelup시킴 
void check_game_over(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info); //게임오버인지 판단하고 게임오버를 진행 
void pause(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info);//게임을 일시정지시킴 
void setcursortype(CURSOR_TYPE c);
void gotoxy(int x, int y);

int get_UI_Position_X(void) {//게임정보표시 위치조정 

	return MAIN_X_ADJ + MAIN_X + 1;
}


void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setcursortype(CURSOR_TYPE c) { //커서숨기는 함수 
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
	int x = 5; //타이틀화면이 표시되는 x좌표 
	int y = 4; //타이틀화면이 표시되는 y좌표 
	int cnt; //타이틀 프레임을 세는 변수  

	gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■"); Sleep(100);
	gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■"); Sleep(100);
	gotoxy(x, y + 2); printf("□□□■              □■  ■"); Sleep(100);
	gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□"); Sleep(100);
	gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□"); Sleep(100);
	gotoxy(x, y + 5); printf("      blog.naver.com/azure0777"); Sleep(100);
	gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
	gotoxy(x, y + 7); printf("Please Enter Any Key to Start..");
	gotoxy(x, y + 9); printf("  △   : Shift");
	gotoxy(x, y + 10); printf("◁  ▷ : Left / Right");
	gotoxy(x, y + 11); printf("  ▽   : Soft Drop");
	gotoxy(x, y + 12); printf(" SPACE : Hard Drop");
	gotoxy(x, y + 13); printf("   P   : Pause");
	gotoxy(x, y + 14); printf("  ESC  : Quit");
	gotoxy(x, y + 16); printf("BONUS FOR HARD DROPS / COMBOS");

	for (cnt = 0;; cnt++) { //cnt를 1씩 증가시키면서 계속 반복    //하나도 안중요한 별 반짝이는 애니메이션효과 
		if (_kbhit()) break; //키입력이 있으면 무한루프 종료 
		if (cnt % 200 == 0) { gotoxy(x + 4, y + 1); printf("★"); }       //cnt가 200으로 나누어 떨어질때 별을 표시 
		if ((cnt % 200 - 100) == 0) { gotoxy(x + 4, y + 1); printf("  "); } //위 카운트에서 100카운트 간격으로 별을 지움 
		if ((cnt % 350) == 0) { gotoxy(x + 13, y + 2); printf("☆"); } //윗별과 같지만 시간차를 뒀음 
		if ((cnt % 350 - 100) == 0) { gotoxy(x + 13, y + 2); printf("  "); }
		Sleep(10); // 00.1초 딜레이  
	}

	while (_kbhit()) _getch(); //버퍼에 기록된 키값을 버림 
	return;
}


void reset(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info) {

	FILE *file;
	fopen_s(&file, "score.dat", "rb"); // score.dat파일을 연결 
	if (file == 0) { (*game_info).best_score = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
	else {
		fscanf_s(file, "%d", &(*game_info).best_score); // 파일이 열리면 최고점수를 불러옴 
		fclose(file); //파일 닫음 
	}

	(*game_info).level = 1; //각종변수 초기화 
	(*game_info).score = 0;
	(*game_info).level_goal = 1000;
	(*game_info).key = 0;
	(*game_info).crush_on = 0;
	(*game_info).cnt = 0;
	(*game_info).speed = 100;

	system("cls"); //화면지움 
	reset_main(map_info); // main_org를 초기화 
	draw_map(game_info, ui_info); // 게임화면을 그림
	draw_main(map_info); // 게임판을 그림 

	(*block_info).b_type_next = rand() % 7; //다음번에 나올 블록 종류를 랜덤하게 생성 
	new_block(block_info, game_info, map_info); //새로운 블록을 하나 만듦  

	return;
}

void reset_main(Map_Info   * map_info) { //게임판을 초기화  
	int i, j;

	for (i = 0; i < MAIN_Y; i++) { // 게임판을 0으로 초기화  
		for (j = 0; j < MAIN_X; j++) {
			(*map_info).main_org[i][j] = 0;
			(*map_info).main_cpy[i][j] = 100;
		}
	}
	for (j = 1; j < MAIN_X; j++) { //y값이 3인 위치에 천장을 만듦 
		(*map_info).main_org[3][j] = CEILLING;
	}
	for (i = 1; i < MAIN_Y - 1; i++) { //좌우 벽을 만듦  
		(*map_info).main_org[i][0] = WALL;
		(*map_info).main_org[i][MAIN_X - 1] = WALL;
	}
	for (j = 0; j < MAIN_X; j++) { //바닥벽을 만듦 
		(*map_info).main_org[MAIN_Y - 1][j] = WALL;
	}

	return;
}

void reset_main_cpy(Map_Info * map_info) { //main_cpy를 초기화 
	int i, j;

	for (i = 0; i < MAIN_Y; i++) {         //게임판에 게임에 사용되지 않는 숫자를 넣음 
		for (j = 0; j < MAIN_X; j++) {  //이는 main_org와 같은 숫자가 없게 하기 위함 
			(*map_info).main_cpy[i][j] = 100;
		}
	}

	return;
}

void draw_map(Game_Info * game_info, UI_Info * ui_info) { //게임 상태 표시를 나타내는 함수  
	int y = 3;             // level, goal, score만 게임중에 값이 바뀔수 도 있음 그 y값을 따로 저장해둠 
						 // 그래서 혹시 게임 상태 표시 위치가 바뀌어도 그 함수에서 안바꿔도 되게.. 
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
	gotoxy(get_UI_Position_X(), y + 15); printf("  △   : Shift        SPACE : Hard Drop");
	gotoxy(get_UI_Position_X(), y + 16); printf("◁  ▷ : Left / Right   P   : Pause");
	gotoxy(get_UI_Position_X(), y + 17); printf("  ▽   : Soft Drop     ESC  : Quit");
	gotoxy(get_UI_Position_X(), y + 20); printf("blog.naver.com/azure0777");

	return;
}

void draw_main(Map_Info * map_info) { //게임판 그리는 함수 
	int i, j;

	for (j = 1; j < MAIN_X - 1; j++) { //천장은 계속 새로운블럭이 지나가서 지워지면 새로 그려줌 
		if ((*map_info).main_org[3][j] == EMPTY) (*map_info).main_org[3][j] = CEILLING;
	}
	for (i = 0; i < MAIN_Y; i++) {
		for (j = 0; j < MAIN_X; j++) {
			if ((*map_info).main_cpy[i][j] != (*map_info).main_org[i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
												//이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch ((*map_info).main_org[i][j]) {
				case EMPTY: //빈칸모양 
					printf("  ");
					break;
				case CEILLING: //천장모양 
					printf(". ");
					break;
				case WALL: //벽모양 
					printf("▩");
					break;
				case INACTIVE_BLOCK: //굳은 블럭 모양  
					printf("□");
					break;
				case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
					printf("■");
					break;
				}
			}
		}
	}
	for (i = 0; i < MAIN_Y; i++) { //게임판을 그린 후 main_cpy에 복사  
		for (j = 0; j < MAIN_X; j++) {
			(*map_info).main_cpy[i][j] = (*map_info).main_org[i][j];
		}
	}

	return;
}

void new_block(Block_Info * block_info, Game_Info * game_info, Map_Info * map_info) { //새로운 블록 생성  
	int i, j;
	
	(*block_info).bx = (MAIN_X / 2) - 1; //블록 생성 위치x좌표(게임판의 가운데) 
	(*block_info).by = 0;  //블록 생성위치 y좌표(제일 위) 
	(*block_info).b_type = (*block_info).b_type_next; //다음블럭값을 가져옴 
	(*block_info).b_type_next = rand() % 7; //다음 블럭을 만듦 
	(*block_info).b_rotation = 0;  //회전은 0번으로 가져옴 

	(*game_info).new_block_on = 0; //new_block flag를 끔  

	for (i = 0; i < 4; i++) { //게임판 bx, by위치에 블럭생성  
		for (j = 0; j < 4; j++) {
			if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = ACTIVE_BLOCK;
		}
	}
	for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
		for (j = 0; j < 4; j++) {
			if (blocks[(*block_info).b_type_next][0][i][j] == 1) {
				gotoxy(get_UI_Position_X() + 2 + j, i + 6);
				printf("■");
			}
			else {
				gotoxy(get_UI_Position_X() + 2 + j, i + 6);
				printf("  ");
			}
		}
	}

	return;
}

void check_key(Game_Info * game_info, Block_Info * block_info, UI_Info * ui_info, Map_Info * map_info) {
	(*game_info).key = 0; //키값 초기화  

	if (_kbhit()) { //키입력이 있는 경우  
		(*game_info).key = _getch(); //키값을 받음
		if ((*game_info).key == 224) { //방향키인경우 
			do { (*game_info).key = _getch(); } while ((*game_info).key == 224);//방향키지시값을 버림 
			switch ((*game_info).key) {
			case LEFT: //왼쪽키 눌렀을때  
				if (check_crush((*block_info).bx - 1, (*block_info).by, (*block_info).b_rotation, (*block_info).b_type,map_info) == true) move_block(LEFT,block_info,map_info);
				break;                            //왼쪽으로 갈 수 있는지 체크 후 가능하면 이동
			case RIGHT: //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨 
				if (check_crush((*block_info).bx + 1, (*block_info).by, (*block_info).b_rotation, (*block_info).b_type, map_info) == true) move_block(RIGHT, block_info, map_info);
				break;
			case DOWN: //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨 
				if (check_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == true) move_block(DOWN, block_info, map_info);
				break;
			case UP: //위쪽 방향키 눌렀을때 
				if (check_crush((*block_info).bx, (*block_info).by, ((*block_info).b_rotation + 1) % 4, (*block_info).b_type, map_info) == true) move_block(UP, block_info, map_info);
				//회전할 수 있는지 체크 후 가능하면 회전
				else if ((*game_info).crush_on == 1 && check_crush((*block_info).bx, (*block_info).by - 1, ((*block_info).b_rotation + 1) % 4, (*block_info).b_type, map_info) == true) move_block(100, block_info, map_info);
			}                    //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)
		}
		else { //방향키가 아닌경우 
			switch ((*game_info).key) {
			case SPACE: //스페이스키 눌렀을때 
				(*game_info).space_key_on = 1; //스페이스키 flag를 띄움 
				while ((*game_info).crush_on == 0) { //바닥에 닿을때까지 이동시킴 
					drop_block(game_info,block_info,map_info,ui_info);
					(*game_info).score += (*game_info).level; // hard drop 보너스
					gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_SCORE); printf("        %6d", (*game_info).score); //점수 표시  
				}
				break;
			case P: //P(대문자) 눌렀을때 
			case p: //p(소문자) 눌렀을때 
				pause(game_info,map_info,block_info,ui_info); //일시정지 
				break;
			case ESC: //ESC눌렀을때 
				system("cls"); //화면을 지우고 
				exit(0); //게임종료 
			}
		}
	}
	while (_kbhit()) _getch(); //키버퍼를 비움 

	return;
}

void drop_block(Game_Info * game_info, Block_Info * block_info, Map_Info * map_info, UI_Info * ui_info) {
	int i;
	int j;

	if ((*game_info).crush_on&&check_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation,(*block_info).b_type,map_info) == true) 
		(*game_info).crush_on = 0; //밑이 비어있으면 crush flag 끔 
	if ((*game_info).crush_on&&check_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == false) { //밑이 비어있지않고 crush flag가 켜저있으면 
		for (i = 0; i < MAIN_Y; i++) { //현재 조작중인 블럭을 굳힘 
			for (j = 0; j < MAIN_X; j++) {
				if ((*map_info).main_org[i][j] == ACTIVE_BLOCK) 
					(*map_info).main_org[i][j] = INACTIVE_BLOCK;
			}
		}
		(*game_info).crush_on = 0; //flag를 끔 
		check_line(game_info, map_info,block_info,ui_info); //라인체크를 함 
		(*game_info).new_block_on = 1; //새로운 블럭생성 flag를 켬    
		return; //함수 종료 
	}
	if (check_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == true) 
		move_block(DOWN,block_info,map_info); //밑이 비어있으면 밑으로 한칸 이동 
	if (check_crush((*block_info).bx, (*block_info).by + 1, (*block_info).b_rotation, (*block_info).b_type, map_info) == false) 
		(*game_info).crush_on++; //밑으로 이동이 안되면  crush flag를 켬

	return;
}

int check_crush(int bx, int by, int b_rotation, int bType, Map_Info * map_info) { //지정된 좌표와 회전값으로 충돌이 있는지 검사 
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) { //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
			if (blocks[bType][b_rotation][i][j] == 1 && (* map_info).main_org[by + i][bx + j] > 0) return false;
		}
	}
	return true; //하나도 안겹치면 true리턴 
}

void move_block(int dir, Block_Info * block_info, Map_Info * map_info) { //블록을 이동시킴 
	int i, j;

	switch (dir) {
	case LEFT: //왼쪽방향 
		for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음 
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j - 1] = ACTIVE_BLOCK;
			}
		}
		(*block_info).bx--; //좌표값 이동 
		break;

	case RIGHT:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j + 1] = ACTIVE_BLOCK;
			}
		}
		(*block_info).bx++;
		break;

	case DOWN:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i + 1][(*block_info).bx + j] = ACTIVE_BLOCK;
			}
		}
		(*block_info).by++;
		break;

	case UP: //키보드 위쪽 눌렀을때 회전시킴. 
		for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움  
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = EMPTY;
			}
		}
		(*block_info).b_rotation = ((*block_info).b_rotation + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림) 
		for (i = 0; i < 4; i++) { //회전된 블록을 찍음 
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = ACTIVE_BLOCK;
			}
		}
		break;

	case 100: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 
			  //이를 동작시키는 특수동작 
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i][(*block_info).bx + j] = EMPTY;
			}
		}
		(*block_info).b_rotation = ((*block_info).b_rotation + 1) % 4;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				if (blocks[(*block_info).b_type][(*block_info).b_rotation][i][j] == 1) (*map_info).main_org[(*block_info).by + i - 1][(*block_info).bx + j] = ACTIVE_BLOCK;
			}
		}
		(*block_info).by--;
		break;
	}

	return;
}

void check_line(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) {
	int i;
	int j; 
	int k;
	int l;
	int block_amount; //한줄의 블록갯수를 저장하는 변수 
	int combo = 0; //콤보갯수 저장하는 변수 지정및 초기화 

	for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사 
		block_amount = 0; //블록갯수 저장 변수 초기화 
		for (j = 1; j < MAIN_X - 1; j++) { //벽과 벽사이의 블록갯루를 셈 
			if ((*map_info).main_org[i][j] > 0) 
				block_amount++;
		}
		if (block_amount == MAIN_X - 2) { //블록이 가득 찬 경우 
			if ((*game_info).level_up_on == 0) { //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음) 
				(*game_info).score += 100 * (*game_info).level; //점수추가 
				(*game_info).cnt++; //지운 줄 갯수 카운트 증가 
				combo++; //콤보수 증가  
			}
			for (k = i; k > 1; k--) { //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) 
				for (l = 1; l < MAIN_X - 1; l++) {
					if ((*map_info).main_org[k - 1][l] != CEILLING) 
						(*map_info).main_org[k][l] = (*map_info).main_org[k - 1][l];
					if ((*map_info).main_org[k - 1][l] == CEILLING) 
						(*map_info).main_org[k][l] = EMPTY;
					//윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
				}
			}
		}
		else i--;
	}

	if (combo) { //줄 삭제가 있는 경우 점수와 레벨 목표를 새로 표시함  
		if (combo > 1) { //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움 
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + (*block_info).by - 2);
			printf("%d COMBO!", combo);
			Sleep(500);
			(*game_info).score += (combo*(*game_info).level * 100);
			reset_main_cpy(map_info); //텍스트를 지우기 위해 main_cpy을 초기화.
			//(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 
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

	if ((*game_info).cnt >= 10) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
		draw_main(map_info);
		(*game_info).level_up_on = 1; //레벨업 flag를 띄움 
		(*game_info).level += 1; //레벨을 1 올림 
		(*game_info).cnt = 0; //지운 줄수 초기화   

		for (i = 0; i < 4; i++) {
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
			printf("             ");
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
			printf("             ");
			Sleep(200);

			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
			printf("☆LEVEL UP!☆");
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
			printf("☆SPEED UP!☆");
			Sleep(200);
		}
		reset_main_cpy(map_info); //텍스트를 지우기 위해 main_cpy을 초기화.
							//(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 

		for (i = MAIN_Y - 2; i > MAIN_Y - 2 - ((*game_info).level - 1); i--) { //레벨업보상으로 각 레벨-1의 수만큼 아랫쪽 줄을 지워줌 
			for (j = 1; j < MAIN_X - 1; j++) {
				(*map_info).main_org[i][j] = INACTIVE_BLOCK; // 줄을 블록으로 모두 채우고 
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // 별을 찍어줌.. 이뻐보이게 
				printf("★");
				Sleep(20);
			}
		}
		Sleep(100); //별찍은거 보여주기 위해 delay 
		check_line(game_info,map_info,block_info,ui_info); //블록으로 모두 채운것 지우기
//.check_line()함수 내부에서 level up flag가 켜져있는 경우 점수는 없음.         
		switch ((*game_info).level) { //레벨별로 속도를 조절해줌. 
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
		(*game_info).level_up_on = 0; //레벨업 flag꺼줌

		gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_LEVEL); printf(" LEVEL : %5d", (*game_info).level); //레벨표시 
		gotoxy(get_UI_Position_X(), (*ui_info).STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - (*game_info).cnt); // 레벨목표 표시 

	}
	return;
}

void check_game_over(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) {
	int i;

	int x = 5;
	int y = 5;

	for (i = 1; i < MAIN_X - 2; i++) {
		if ((*map_info).main_org[3][i] > 0) { //천장(위에서 세번째 줄)에 inactive가 생성되면 게임 오버 
			gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //게임오버 메세지 
			gotoxy(x, y + 1); printf("▤                              ▤");
			gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
			gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
			gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
			gotoxy(x, y + 5); printf("▤   YOUR SCORE: %6d         ▤", (*game_info).score);
			gotoxy(x, y + 6); printf("▤                              ▤");
			gotoxy(x, y + 7); printf("▤  Press any key to restart..  ▤");
			gotoxy(x, y + 8); printf("▤                              ▤");
			gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
			(*game_info).last_score = (*game_info).score; //게임점수를 옮김 

			if ((*game_info).score > (*game_info).best_score) { //최고기록 갱신시 
				FILE* file;
				fopen_s(&file, "score.dat", "wt"); //score.dat에 점수 저장                

				gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

				if (file == 0) { //파일 에러메세지  
					gotoxy(0, 0);
					printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
				}
				else {
					fprintf(file, "%d", (*game_info).score);
					fclose(file);
				}

			}
			Sleep(1000);
			while (_kbhit()) _getch();
			(*game_info).key = _getch();
			reset(game_info,block_info,ui_info,map_info);
		}
	}
	return;
}
void pause(Game_Info * game_info, Map_Info * map_info, Block_Info * block_info, UI_Info * ui_info) { //게임 일시정지 함수 
	int i, j;

	int x = 5;
	int y = 5;

	for (i = 1; i < MAIN_X - 2; i++) { //게임 일시정지 메세지 
		gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
		gotoxy(x, y + 1); printf("▤                              ▤");
		gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
		gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
		gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
		gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
		gotoxy(x, y + 6); printf("▤                              ▤");
		gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	}
	_getch(); //키입력시까지 대기 

	system("cls"); //화면 지우고 새로 그림 
	system("cls"); //화면 지우고 새로 그림 
	reset_main_cpy(map_info);
	draw_main(map_info);
	draw_map(game_info,ui_info);

	for (i = 1; i < 3; i++) { // 다음블록 그림 
		for (j = 0; j < 4; j++) {
			if (blocks[(*block_info).b_type_next][0][i][j] == 1) {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("■");
			}
			else {
				gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
				printf("  ");
			}
		}
	}
	return;
} //끝! 
