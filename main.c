#include"function.h"


int main() {

	//게임에 필요한 구조체 선언
	UI_Info ui_info;
	Block_Info block_info;
	Game_Info game_info;
	Map_Info map_info;

	/*memeset 함수는 어떤 메모리의 시작점 부터 연속된 범위를 어떤 값(byte단위)으로 
	모두 지정하고 싶을 때 사용 됩니다. 현재 코드에서는 초기화를 시키기위해 사용됐습니다.*/
	memset(&ui_info, 0, sizeof(UI_Info));
	memset(&game_info, 0, sizeof(Game_Info));
	memset(&block_info, 0, sizeof(Block_Info));
	memset(&map_info, 0, sizeof(Map_Info));

	int i;

	srand((unsigned)time(NULL)); //난수표생성 
	Setcursortype(NOCURSOR); //커서 없앰 
	Title(); //메인타이틀 호출 
	Reset(&game_info, &block_info, &ui_info, &map_info); //게임판 리셋 

	while (1) {
		for (i = 0; i < 5; i++) { //블록이 한칸떨어지는동안 5번 키입력받을 수 있음 

			Check_Key(&game_info, &block_info, &ui_info, &map_info); //키입력확인 
			Draw_Main(&map_info); //화면을 그림 
			Sleep(game_info.speed); //게임속도조절 
			if (game_info.crush_on 
				&& Non_Crush(block_info.bx, block_info.by + 1, block_info.b_rotation, block_info.b_type, &map_info) == false) Sleep(100);
			//블록이 충돌중인경우 추가로 이동및 회전할 시간을 갖음 
			if (game_info.space_key_on == 1) { //스페이스바를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
				game_info.space_key_on = 0;
				break;
			}
		}

		Drop_Block(&game_info, &block_info, &map_info, &ui_info); // 블록을 한칸 내림 
		Check_Level_Up(&game_info, &map_info, &ui_info, &block_info); // 레벨업을 체크 
		Check_Game_Over(&game_info, &map_info, &block_info, &ui_info); //게임오버를 체크 
		if (game_info.new_block_on == 1) New_Block(&block_info, &game_info, &map_info); // 뉴 블럭 flag가 있는 경우 새로운 블럭 생성 

	}
}