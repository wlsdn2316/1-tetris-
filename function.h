#pragma once

#include "init.h"

void title(void); //게임시작화면.
void reset(void); //게임판 초기화 
void reset_main(void); //메인 게임판(main_org[][]를 초기화)
void reset_main_cpy(void); //copy 게임판(main_cpy[][]를 초기화)
void draw_map(void); //게임 전체 인터페이스를 표시 
void draw_main(void); //게임판을 그림 
void new_block(void); //새로운 블록을 하나 만듦 
void check_key(void); //키보드로 키를 입력받음 
void drop_block(void); //블록을 아래로 떨어트림 
int check_crush(int bx, int by, int rotation); //bx, by위치에 rotation회전값을 같는 경우 충돌 판단 
void move_block(int dir); //dir방향으로 블록을 움직임 
void check_line(void); //줄이 가득찼는지를 판단하고 지움 
void check_level_up(void); //레벨목표가 달성되었는지를 판단하고 levelup시킴 
void check_game_over(void); //게임오버인지 판단하고 게임오버를 진행 
void pause(void);//게임을 일시정지시킴 

CONSOLE_CURSOR_INFO setCurInfo(int size, BOOL flag); // 커서 정보를 받아서 저장하고 커서 객체를 리턴함
void file_control(FILE * file, char * file_name, char * ch);
void init_reset(void); //매 게임마다 초기화가 필요한 변수들을 초기화시킴

void init_reset(void) {
	level = 1; //각종변수 초기화 
	score = 0;
	level_goal = 1000;
	key = 0;
	crush_on = 0;
	cnt = 0;
	speed = 100;
}

void file_control(FILE * file, char * file_name, char * ch) { //file control함수로 읽기 저장하기 닫기 기능을 수행함.

	if (ch == "rt") {
		fopen_s(&file, file_name, ch);
		if (file == 0) { best_score = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
		else {
			fscanf_s(file, "%d", &best_score); // 파일이 열리면 최고점수를 불러옴 
		}
	}
	else if (ch == "wt") {
		fopen_s(&file, file_name, ch); //score.dat에 점수 저장                
		if (file == NULL) {	
			gotoxy(0, 0); 
			printf("존재하지 않는 파일 입니다. \n");
		}
		fprintf(file, "%d", score);

	}
	
	//모든 작업후엔 항상 close를 해야하므로 
	if (file == NULL) {
		printf("NULL 파일을 닫으려 하고있습니다.\n");
		return;
	}
	fclose(file); //파일 닫음	
	
}
void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

CONSOLE_CURSOR_INFO setCurInfo(int size, BOOL flag) { // 커서 정보를 받아서 저장하고 커서 객체를 리턴함
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = size;
	CurInfo.bVisible = flag;
	return CurInfo;
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


void reset(void) {

	FILE *file;
	fopen_s(&file, "score.dat", "rt"); // score.dat파일을 연결 
	if (file == 0) { best_score = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
	else {
		fscanf_s(file, "%d", &best_score); // 파일이 열리면 최고점수를 불러옴 
		fclose(file); //파일 닫음 
	}

	level = 1; //각종변수 초기화 
	score = 0;
	level_goal = 1000;
	key = 0;
	crush_on = 0;
	cnt = 0;
	speed = 100;

	system("cls"); //화면지움 
	reset_main(); // main_org를 초기화 
	draw_map(); // 게임화면을 그림
	draw_main(); // 게임판을 그림 

	b_type_next = rand() % 7; //다음번에 나올 블록 종류를 랜덤하게 생성 
	new_block(); //새로운 블록을 하나 만듦  

	return;
}

void reset_main(void) { //게임판을 초기화  
	int i, j;

	for (i = 0; i < MAIN_Y; i++) { // 게임판을 0으로 초기화  
		for (j = 0; j < MAIN_X; j++) {
			main_org[i][j] = 0;
			main_cpy[i][j] = 100;
		}
	}
	for (j = 1; j < MAIN_X; j++) { //y값이 3인 위치에 천장을 만듦 
		main_org[3][j] = CEILLING;
	}
	for (i = 1; i < MAIN_Y - 1; i++) { //좌우 벽을 만듦  
		main_org[i][0] = WALL;
		main_org[i][MAIN_X - 1] = WALL;
	}
	for (j = 0; j < MAIN_X; j++) { //바닥벽을 만듦 
		main_org[MAIN_Y - 1][j] = WALL;
	}

	return;
}

void reset_main_cpy(void) { //main_cpy를 초기화 
	int i, j;

	for (i = 0; i < MAIN_Y; i++) {         //게임판에 게임에 사용되지 않는 숫자를 넣음 
		for (j = 0; j < MAIN_X; j++) {  //이는 main_org와 같은 숫자가 없게 하기 위함 
			main_cpy[i][j] = 100;
		}
	}

	return;
}

void draw_map(void) { //게임 상태 표시를 나타내는 함수  
	int y = 3;             // level, goal, score만 게임중에 값이 바뀔수 도 있음 그 y값을 따로 저장해둠 
						 // 그래서 혹시 게임 상태 표시 위치가 바뀌어도 그 함수에서 안바꿔도 되게.. 
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
	gotoxy(STATUS_X_ADJ, y + 15); printf("  △   : Shift        SPACE : Hard Drop");
	gotoxy(STATUS_X_ADJ, y + 16); printf("◁  ▷ : Left / Right   P   : Pause");
	gotoxy(STATUS_X_ADJ, y + 17); printf("  ▽   : Soft Drop     ESC  : Quit");
	gotoxy(STATUS_X_ADJ, y + 20); printf("blog.naver.com/azure0777");

	return;
}

void draw_main(void) { //게임판 그리는 함수 
	int i, j;

	for (j = 1; j < MAIN_X - 1; j++) { //천장은 계속 새로운블럭이 지나가서 지워지면 새로 그려줌 
		if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
	}
	for (i = 0; i < MAIN_Y; i++) {
		for (j = 0; j < MAIN_X; j++) {
			if (main_cpy[i][j] != main_org[i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
												//이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
				switch (main_org[i][j]) {
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
			main_cpy[i][j] = main_org[i][j];
		}
	}

	return;
}

void new_block(void) { //새로운 블록 생성  
	int i, j;

	bx = (MAIN_X / 2) - 1; //블록 생성 위치x좌표(게임판의 가운데) 
	by = 0;  //블록 생성위치 y좌표(제일 위) 
	b_type = b_type_next; //다음블럭값을 가져옴 
	b_type_next = rand() % 7; //다음 블럭을 만듦 
	b_rotation = 0;  //회전은 0번으로 가져옴 

	new_block_on = 0; //new_block flag를 끔  

	for (i = 0; i < 4; i++) { //게임판 bx, by위치에 블럭생성  
		for (j = 0; j < 4; j++) {
			if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
		}
	}
	for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
				gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
				printf("■");
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
	key = 0; //키값 초기화  

	if (_kbhit()) { //키입력이 있는 경우  
		key = _getch(); //키값을 받음
		if (key == 224) { //방향키인경우 
			do { key = _getch(); } while (key == 224);//방향키지시값을 버림 
			switch (key) {
			case LEFT: //왼쪽키 눌렀을때  
				if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
				break;                            //왼쪽으로 갈 수 있는지 체크 후 가능하면 이동
			case RIGHT: //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨 
				if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
				break;
			case DOWN: //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨 
				if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
				break;
			case UP: //위쪽 방향키 눌렀을때 
				if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
				//회전할 수 있는지 체크 후 가능하면 회전
				else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
			}                    //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)
		}
		else { //방향키가 아닌경우 
			switch (key) {
			case SPACE: //스페이스키 눌렀을때 
				space_key_on = 1; //스페이스키 flag를 띄움 
				while (crush_on == 0) { //바닥에 닿을때까지 이동시킴 
					drop_block();
					score += level; // hard drop 보너스
					gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //점수 표시  
				}
				break;
			case P: //P(대문자) 눌렀을때 
			case p: //p(소문자) 눌렀을때 
				pause(); //일시정지 
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

void drop_block(void) {
	int i, j;

	if (crush_on&&check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //밑이 비어있으면 crush flag 끔 
	if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) { //밑이 비어있지않고 crush flag가 켜저있으면 
		for (i = 0; i < MAIN_Y; i++) { //현재 조작중인 블럭을 굳힘 
			for (j = 0; j < MAIN_X; j++) {
				if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
			}
		}
		crush_on = 0; //flag를 끔 
		new_block_on = 1;
		check_line(); //라인체크를 함 
		 //새로운 블럭생성 flag를 켬    
		return; //함수 종료 
	}
	if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //밑이 비어있으면 밑으로 한칸 이동 
	if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //밑으로 이동이 안되면  crush flag를 켬

	return;
}

int check_crush(int bx, int by, int b_rotation) { //지정된 좌표와 회전값으로 충돌이 있는지 검사 
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) { //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
			if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
		}
	}
	return true; //하나도 안겹치면 true리턴 
}

void move_block(int dir) { //블록을 이동시킴 
	int i, j;

	switch (dir) {
	case LEFT: //왼쪽방향 
		for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
			}
		}
		bx--; //좌표값 이동 
		break;

	case RIGHT:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
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

	case DOWN:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
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

	case UP: //키보드 위쪽 눌렀을때 회전시킴. 
		for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움  
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
			}
		}
		b_rotation = (b_rotation + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림) 
		for (i = 0; i < 4; i++) { //회전된 블록을 찍음 
			for (j = 0; j < 4; j++) {
				if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
			}
		}
		break;

	case 100: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 
			  //이를 동작시키는 특수동작 
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

	int block_amount; //한줄의 블록갯수를 저장하는 변수 
	int combo = 0; //콤보갯수 저장하는 변수 지정및 초기화 

	for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사 
		block_amount = 0; //블록갯수 저장 변수 초기화 
		for (j = 1; j < MAIN_X - 1; j++) { //벽과 벽사이의 블록갯루를 셈 
			if (main_org[i][j] > 0) block_amount++;
		}
		if (block_amount == MAIN_X - 2) { //블록이 가득 찬 경우 
			if (level_up_on == 0) { //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음) 
				score += 100 * level; //점수추가 
				cnt++; //지운 줄 갯수 카운트 증가 
				combo++; //콤보수 증가  
			}
			for (k = i; k > 1; k--) { //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) 
				for (l = 1; l < MAIN_X - 1; l++) {
					if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
					if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
					//윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
				}
			}
		}
		else i--;
	}
	if (combo) { //줄 삭제가 있는 경우 점수와 레벨 목표를 새로 표시함  
		if (combo > 1) { //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움 
			gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
			Sleep(500);
			score += (combo*level * 100);
			reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
			//(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 
		}
		gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
		gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
	}
	return;
}

void check_level_up(void) {
	int i, j;

	if (cnt >= 10) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
		draw_main();
		level_up_on = 1; //레벨업 flag를 띄움 
		level += 1; //레벨을 1 올림 
		cnt = 0; //지운 줄수 초기화   

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
		reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
							//(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 

		for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //레벨업보상으로 각 레벨-1의 수만큼 아랫쪽 줄을 지워줌 
			for (j = 1; j < MAIN_X - 1; j++) {
				main_org[i][j] = INACTIVE_BLOCK; // 줄을 블록으로 모두 채우고 
				gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // 별을 찍어줌.. 이뻐보이게 
				printf("★");
				Sleep(20);
			}
		}
		Sleep(100); //별찍은거 보여주기 위해 delay 
		check_line(); //블록으로 모두 채운것 지우기
//.check_line()함수 내부에서 level up flag가 켜져있는 경우 점수는 없음.         
		switch (level) { //레벨별로 속도를 조절해줌. 
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
		level_up_on = 0; //레벨업 flag꺼줌

		gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //레벨표시 
		gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // 레벨목표 표시 

	}

	return;
}

void check_game_over(void) {
	int i;

	int x = 5;
	int y = 5;

	for (i = 1; i < MAIN_X - 2; i++) {
		if (main_org[3][i] > 0) { //천장(위에서 세번째 줄)에 inactive가 생성되면 게임 오버 
			gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //게임오버 메세지 
			gotoxy(x, y + 1); printf("▤                              ▤");
			gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
			gotoxy(x, y + 3); printf("▤  |  G A M E  O V E R..   |   ▤");
			gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
			gotoxy(x, y + 5); printf("▤   YOUR SCORE: %6d         ▤", score);
			gotoxy(x, y + 6); printf("▤                              ▤");
			gotoxy(x, y + 7); printf("▤  Press any key to restart..  ▤");
			gotoxy(x, y + 8); printf("▤                              ▤");
			gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
			last_score = score; //게임점수를 옮김 

			if (score > best_score) { //최고기록 갱신시 
				FILE* file;
				fopen_s(&file, "score.dat", "wt"); //score.dat에 점수 저장                

				gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

				if (file == 0) { //파일 에러메세지  
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

void pause(void) { //게임 일시정지 함수 
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
	reset_main_cpy();
	draw_main();
	draw_map();

	for (i = 1; i < 3; i++) { // 다음블록 그림 
		for (j = 0; j < 4; j++) {
			if (blocks[b_type_next][0][i][j] == 1) {
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
