#ifndef _DISP_H
#define _DISP_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
//#pragma warning(disable:4996)

#define false 0
#define true 1

<<<<<<< HEAD
typedef enum {
	LEFT = 75, //좌로 이동
	RIGHT = 77,	//우로 이동
	UP = 72,		//회전
	DOWN = 80,	//soft drop
	SPACE = 32,	//hard drop
	p = 112,		//일시정지 
	P = 80,		//일시정지
	ESC = 27		//게임종료 
} KEYCODE; //키보드값들


typedef enum {
	ACTIVE_BLOCK = -2,	// 게임판배열에 저장될 블록의 상태들 
	CEILLING = -1,		// 블록이 이동할 수 있는 공간은 0 또는 음의 정수료 표현 
	EMPTY = 0,
	WALL = 1,			// 블록이 이동할 수 없는 공간은 양수로 표현 
	INACTIVE_BLOCK = 2	// 이동이 완료된 블록값
}BLOCK_STATUS;	//BLOCK 상태값들

typedef enum {
	MAIN_X = 11,	//게임판 가로크기
	MAIN_Y = 23,	//게임판 세로크기
	MAIN_X_ADJ = 3,	//게임판 위치조정
	MAIN_Y_ADJ = 1	//게임판 위치조정
}MAP_SIZE;


=======
typedef enum
{
	LEFT = 75,  //醫뚮줈 �씠�룞
	RIGHT = 77, //�슦濡� �씠�룞
	UP = 72,    //�쉶�쟾
	DOWN = 80,  //soft drop
	SPACE = 32, //hard drop
	p = 112,    //�씪�떆�젙吏�
	P = 80,	//�씪�떆�젙吏�
	ESC = 27    //寃뚯엫醫낅즺
} KEYCODE;	  //�궎蹂대뱶媛믩뱾

typedef enum
{
	ACTIVE_BLOCK = -2, // 寃뚯엫�뙋諛곗뿴�뿉 ����옣�맆 釉붾줉�쓽 �긽�깭�뱾
	CEILLING = -1,	// 釉붾줉�씠 �씠�룞�븷 �닔 �엳�뒗 怨듦컙��� 0 �삉�뒗 �쓬�쓽 �젙�닔猷� �몴�쁽
	EMPTY = 0,
	WALL = 1,		    // 釉붾줉�씠 �씠�룞�븷 �닔 �뾾�뒗 怨듦컙��� �뼇�닔濡� �몴�쁽
	INACTIVE_BLOCK = 2 // �씠�룞�씠 �셿猷뚮맂 釉붾줉媛�
} BLOCK_STATUS;	    //BLOCK �긽�깭媛믩뱾

typedef enum
{
	MAIN_X = 11,    //寃뚯엫�뙋 媛�濡쒗겕湲�
	MAIN_Y = 23,    //寃뚯엫�뙋 �꽭濡쒗겕湲�
	MAIN_X_ADJ = 3, //寃뚯엫�뙋 �쐞移섏“�젙
	MAIN_Y_ADJ = 1  //寃뚯엫�뙋 �쐞移섏“�젙
} MAP_SIZE;
>>>>>>> add

typedef enum
{
	NOCURSOR,
	SOLIDCURSOR,
	NORMALCURSOR
} CURSOR_TYPE; //而ㅼ꽌�닲湲곕뒗 �븿�닔�뿉 �궗�슜�릺�뒗 �뿴嫄고삎

int blocks[7][4][4][4] = {
<<<<<<< HEAD
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}
}; //블록모양 저장 4*4공간에 블록을 표현 blcoks[b_type][b_rotation][i][j]로 사용 

//구조체
typedef struct _UI_Info {
	int STATUS_Y_GOAL; //GOAL 정보표시위치Y 좌표 저장 
	int STATUS_Y_LEVEL; //LEVEL 정보표시위치Y 좌표 저장
	int STATUS_Y_SCORE; //SCORE 정보표시위치Y 좌표 저장

}UI_Info;
//구조체
typedef struct _Block_Info {
	int b_type; //블록 종류를 저장 
	int b_rotation; //블록 회전값 저장 
	int b_type_next; //다음 블록값 저장 
	int bx, by; //이동중인 블록의 게임판상의 x,y좌표를 저장 

}Block_Info;

typedef struct _Game_Info {
	int key; //키보드로 입력받은 키값을 저장 

	int speed; //게임진행속도 
	int level; //현재 level 
	int level_goal; //다음레벨로 넘어가기 위한 목표점수 
	int cnt; //현재 레벨에서 제거한 줄 수를 저장 
	int score; //현재 점수 
	int last_score; //마지막게임점수 
	int best_score; //최고게임점수 

	int new_block_on; //새로운 블럭이 필요함을 알리는 flag 
	int crush_on; //현재 이동중인 블록이 충돌상태인지 알려주는 flag 
	int level_up_on; //다음레벨로 진행(현재 레벨목표가 완료되었음을) 알리는 flag 
	int space_key_on; //hard drop상태임을 알려주는 flag 

	FILE *file; //file 변수 게임 rest과 gameover에서 사용

}Game_Info;

typedef struct _Map_Info {
	int main_org[MAIN_Y][MAIN_X]; //게임판의 정보를 저장하는 배열 모니터에 표시후에 main_cpy로 복사됨 
	int main_cpy[MAIN_Y][MAIN_X]; //즉 maincpy는 게임판이 모니터에 표시되기 전의 정보를 가지고 있음 
								  //main의 전체를 계속 모니터에 표시하지 않고(이렇게 하면 모니터가 깜빡거림) 
								  //main_cpy와 배열을 비교해서 값이 달라진 곳만 모니터에 고침 
}Map_Info;


=======
    {{0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}},
    {{0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0}},
    {{0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}},
    {{0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0}},
    {{0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0}},
    {{0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0}}}; //釉붾줉紐⑥뼇 ����옣 4*4怨듦컙�뿉 釉붾줉�쓣 �몴�쁽 blcoks[b_type][b_rotation][i][j]濡� �궗�슜

//援ъ“泥�
typedef struct _UI_Info
{
	int STATUS_Y_GOAL;  //GOAL �젙蹂댄몴�떆�쐞移쁚 醫뚰몴 ����옣
	int STATUS_Y_LEVEL; //LEVEL �젙蹂댄몴�떆�쐞移쁚 醫뚰몴 ����옣
	int STATUS_Y_SCORE; //SCORE �젙蹂댄몴�떆�쐞移쁚 醫뚰몴 ����옣

} UI_Info;
//援ъ“泥�
typedef struct _Block_Info
{
	int b_type;	 //釉붾줉 醫낅쪟瑜� ����옣
	int b_rotation;  //釉붾줉 �쉶�쟾媛� ����옣
	int b_type_next; //�떎�쓬 釉붾줉媛� ����옣
	int bx, by;	 //�씠�룞以묒씤 釉붾줉�쓽 寃뚯엫�뙋�긽�쓽 x,y醫뚰몴瑜� ����옣

} Block_Info;

typedef struct _Game_Info
{
	int key; //�궎蹂대뱶濡� �엯�젰諛쏆�� �궎媛믪쓣 ����옣

	int speed;	 //寃뚯엫吏꾪뻾�냽�룄
	int level;	 //�쁽�옱 level
	int level_goal; //�떎�쓬�젅踰⑤줈 �꽆�뼱媛�湲� �쐞�븳 紐⑺몴�젏�닔
	int cnt;		 //�쁽�옱 �젅踰⑥뿉�꽌 �젣嫄고븳 以� �닔瑜� ����옣
	int score;	 //�쁽�옱 �젏�닔
	int last_score; //留덉��留됯쾶�엫�젏�닔
	int best_score; //理쒓퀬寃뚯엫�젏�닔

	int new_block_on; //�깉濡쒖슫 釉붾윮�씠 �븘�슂�븿�쓣 �븣由щ뒗 flag
	int crush_on;	//�쁽�옱 �씠�룞以묒씤 釉붾줉�씠 異⑸룎�긽�깭�씤吏� �븣�젮二쇰뒗 flag
	int level_up_on;  //�떎�쓬�젅踰⑤줈 吏꾪뻾(�쁽�옱 �젅踰⑤ぉ�몴媛� �셿猷뚮릺�뿀�쓬�쓣) �븣由щ뒗 flag
	int space_key_on; //hard drop�긽�깭�엫�쓣 �븣�젮二쇰뒗 flag

	FILE *file; //file 蹂��닔 寃뚯엫 rest怨� gameover�뿉�꽌 �궗�슜

} Game_Info;

typedef struct _Map_Info
{
	int main_org[MAIN_Y][MAIN_X]; //寃뚯엫�뙋�쓽 �젙蹂대�� ����옣�븯�뒗 諛곗뿴 紐⑤땲�꽣�뿉 �몴�떆�썑�뿉 main_cpy濡� 蹂듭궗�맖
	int main_cpy[MAIN_Y][MAIN_X]; //利� maincpy�뒗 寃뚯엫�뙋�씠 紐⑤땲�꽣�뿉 �몴�떆�릺湲� �쟾�쓽 �젙蹂대�� 媛�吏�怨� �엳�쓬
							//main�쓽 �쟾泥대�� 怨꾩냽 紐⑤땲�꽣�뿉 �몴�떆�븯吏� �븡怨�(�씠�젃寃� �븯硫� 紐⑤땲�꽣媛� 源쒕묀嫄곕┝)
							//main_cpy��� 諛곗뿴�쓣 鍮꾧탳�빐�꽌 媛믪씠 �떖�씪吏� 怨노쭔 紐⑤땲�꽣�뿉 怨좎묠
} Map_Info;
>>>>>>> add

#endif