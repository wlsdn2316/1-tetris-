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

	srand((unsigned)time(NULL)); //난수표생성 
	setcursortype(NOCURSOR); //커서 없앰 
	title(); //메인타이틀 호출 
	reset(&game_info, &block_info, &ui_info, &map_info); //게임판 리셋 

	while (1) {
		for (i = 0; i < 5; i++) { //블록이 한칸떨어지는동안 5번 키입력받을 수 있음 
			check_key(&game_info,&block_info,&ui_info,&map_info); //키입력확인 
			draw_main(&map_info); //화면을 그림 
			Sleep(game_info.speed); //게임속도조절 
			if (game_info.crush_on&&check_crush(block_info.bx, block_info.by + 1, block_info.b_rotation,block_info.b_type,&map_info) == false) Sleep(100);
			//블록이 충돌중인경우 추가로 이동및 회전할 시간을 갖음 
			if (game_info.space_key_on == 1) { //스페이스바를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
				game_info.space_key_on = 0;
				break;
			}
		}
		drop_block(&game_info,&block_info,&map_info,&ui_info); // 블록을 한칸 내림 
		check_level_up(&game_info,&map_info,&ui_info,&block_info); // 레벨업을 체크 
		check_game_over(&game_info,&map_info,&block_info,&ui_info); //게임오버를 체크 
		if (game_info.new_block_on == 1) new_block(&block_info,&game_info,&map_info); // 뉴 블럭 flag가 있는 경우 새로운 블럭 생성 
	}
}

