#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>

///盤面の定義
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

///色とそれに対応するデータの設定
enum {
	COLOR_NONE=-1,
	COLOR_BLACK=0,
	COLOR_WHITE=1,
	COLOR_MAX
};
//どちらのターンかを表示するための文字列設定
char colorNames[][5 + 1] = {
	"Black",// COLOR_BLACK
	"White",// COLOR_WHITE
};

//色情報を入れる箱の設定(初期設定は０のため黒設定)
int cells[BOARD_HEIGHT][BOARD_WIDTH];

//カーソルの設定(キーボード操作)・ターンの設定
int cursorX, cursorY;
int turn;

bool checkCanPut(int _color, int _x, int _y) {
	return false;
}


int main() {
	int x,y;

//色情報の削除
	for (y = 0; y < BOARD_HEIGHT; y++) {
		for (x = 0; x < BOARD_WIDTH; x++) {
			cells[y][x] = COLOR_NONE;
		}
	}

//カーソルをずっと表示し動かせるように無限ループ
	while (1) {
//画面のクリア
		system("cls");
//盤面の表示
	for (y = 0; y < BOARD_HEIGHT; y++) {
		for (x = 0; x < BOARD_WIDTH; x++) {
//カーソルのある場所を◎で表示（何もないところは・）
			if ((x == cursorX) && (y == cursorY)) {
				printf("◎");
			}
			else {
				switch (cells[y][x]){
				case COLOR_NONE:	printf("・");	break;
				case COLOR_BLACK:	printf("●");	break;
				case COLOR_WHITE:	printf("〇");	break;
				default:
					break;
				}
			}
		}
		printf("\n");
	}
	printf("%s turn.\n", colorNames[turn]);

//カーソルを動かす（_getchでキーボード入力）
	switch (_getch()) {
//上
	case'w':	cursorY--;	break;
//下
	case's':	cursorY++;	break;
//左
	case'a':	cursorX--;	break;
//右
	case'd':	cursorX++;	break;
//そのほかのキーを押したらそこに石を置く
	default:
		if (!checkCanPut(turn, cursorX, cursorY)) {
			break;
		}
		cells[cursorY][cursorX] = turn;
//ターンの変更（^=はビット演算子1だったら0,0だったら1に）
		turn ^= 1;
			break;
		}

		
	}

	return 0;
}
