#include"function.h"


int main() {
	int i;

	srand((unsigned)time(NULL)); //난수표생성 
	setcursortype(NOCURSOR); //커서 없앰 
	title(); //메인타이틀 호출 
	reset(); //게임판 리셋 

	while (1) {
		for (i = 0; i < 5; i++) { //블록이 한칸떨어지는동안 5번 키입력받을 수 있음 
			check_key(); //키입력확인 
			draw_main(); //화면을 그림 
			Sleep(speed); //게임속도조절 
			if (crush_on&&check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
			//블록이 충돌중인경우 추가로 이동및 회전할 시간을 갖음 
			if (space_key_on == 1) { //스페이스바를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
				space_key_on = 0;
				break;
			}
		}
		drop_block(); // 블록을 한칸 내림 
		check_level_up(); // 레벨업을 체크 
		check_game_over(); //게임오버를 체크 
		if (new_block_on == 1) new_block(); // 뉴 블럭 flag가 있는 경우 새로운 블럭 생성 
	}
}

