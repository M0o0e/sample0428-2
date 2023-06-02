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
///8方向を定義（石が置けるかのチェック用）
enum {
	DIRECTION_UP,
	DIRECTION_UP_LEFT,
	DIRECTION_LEFT,
	DIRECTION_DOWN_LEFT,
	DIRECTION_DOWN,
	DIRECTION_DOWN_RIGHT,
	DIRECTION_RIGHT,
	DIRECTION_UP_RIGHT,
	DIRECTION_MAX
};
int directions[][2] = {
	{0,-1},//DIRECTION_UP
	{-1,-1},//DIRECTION_UP_LEFT
	{-1,0},//DIRECTION_LEFT
	{-1,1},//DIRECTION_DOWN_LEFT
	{0,1},//DIRECTION_DOWN
	{1,1},//DIRECTION_DOWN_RIGHT
	{1,0},//DIRECTION_RIGHT
	{1,-1},//DIRECTION_UP_RIGHT
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

//置けるかどうかの判定とひっくり返しの処理"checkCanPut"
bool checkCanPut(int _color, int _x, int _y,bool _turnOver) {
	if (cells[_y][_x] != COLOR_NONE) {
		return false;
	}
	for (int i = 0; i < DIRECTION_MAX; i++) {
		int x = _x, y = _y;
		x += directions[i][0];
		y += directions[i][1];

//もし見ている位置が相手の色ではなかったらループの最初に戻る(for文)
		if (cells[y][x] != (_color ^ 1))
			continue;

		while (1){
			x += directions[i][0];
			y += directions[i][1];

//盤面からはみ出した時の処理
			if ((x < 0) || (x >= BOARD_WIDTH) || (y < 0) || (y >= BOARD_HEIGHT))
				break;
//隣に石がなかった時の処理
			if (cells[y][x] == COLOR_NONE)
				break;
//自分の色と同じ石があったとき（挟めるとき）checkをtrueで返す
			if (cells[y][x] == _color) {
//ひっくり返しのフラグが立っていないときそのままtrueをかえす
				if(!_turnOver)
					return true;

//ひっくり返す石を表す変数の導入
				int x2 = _x, y2 = _y;
				while (1) {
//ひっくり返すべき場所の石の色を自分の色に変更
					cells[y2][x2] = _color;
//x2,y2を次の場所に進める
					x2 += directions[i][0];
					y2 += directions[i][1];
//x2,y2がx,yの値と同じになったら無限ループを抜ける
					if ((x2 == x) && (y2 == y))
						break;
				}
				break;
			}
		}
	}
	return false;
}

//パスのための処理"checkCanPutAll"
bool checkCanPutAll(int _color) {
	for (int y = 0; y < BOARD_HEIGHT; y++)
		for (int x = 0; x < BOARD_WIDTH; x++)
//すべてのマスをcheckCanPutにいれて、置ける場所があったらtrueを返す
			if (checkCanPut(_color, x, y, false))
				return true;
//if文に引っかからずにfor文を抜けてしまったらfalseを返す（置ける場所がないためパスになる）
	return false;
}

void drawBoard() {
//画面のクリア
	system("cls");
//盤面の表示
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
//カーソルのある場所を◎で表示（何もないところは・）
			if ((x == cursorX) && (y == cursorY)) {
				printf("◎");
			}
			else {
				switch (cells[y][x]) {
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
}

int main() {

//色情報の削除
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			cells[y][x] = COLOR_NONE;
		}
	}
	cells[3][3] = cells[4][4]= COLOR_WHITE;
	cells[3][4] = cells[4][3] = COLOR_BLACK;


	bool cantPut = false;

//カーソルをずっと表示し動かせるように無限ループ
	while (1) {
		drawBoard();


//置けなかったらエラーメッセ、おけたときはターン表示
	if (cantPut) {
		printf("Can't Put!\n");
	}
	else {
		printf("%s turn.\n", colorNames[turn]);
	}
	
//(ターン表示を取り戻すため)(入力があったら)置けなかった記録を削除
	cantPut = false;

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
//おけるかチェックする関数が偽だったら置けなかったという記録を残し、石を置かずに終わる
		if (!checkCanPut(turn, cursorX, cursorY,false)) {
			cantPut = true;
			break;
		}

//ひっくり返す
		checkCanPut(turn, cursorX, cursorY, true);

//石を置く（ターンのほうの石を置く）
		cells[cursorY][cursorX] = turn;
//ターンの変更（^=はビット演算子1だったら0,0だったら1に）
		turn ^= 1;

//ターンを変更した先がパスの場合（置く場所がなかった場合）もう一度ターン変更をする
		if (!checkCanPutAll(turn))
			turn ^= 1;
		break;
		}
	
//どちらも石を置くことができなかった時ゲームの終了（盤面の表示と終了を表示）
		if ((!checkCanPutAll(COLOR_BLACK)) && (!checkCanPutAll(COLOR_WHITE))) {

//お互いの石のカウント
			int count[COLOR_MAX] = {0};
			for (int y = 0; y < BOARD_HEIGHT; y++)
				for (int x = 0; x < BOARD_WIDTH; x++)
					if (cells[y][x] != COLOR_NONE)
							count[cells[y][x]]++;
				
			drawBoard();

//お互いの石の数の表示と勝者または引き分けの表示
			for(int i=0;i<COLOR_MAX;i++)
				printf("%s:%d\n",colorNames[i],count[i]);

			if (count[COLOR_BLACK] == count[COLOR_WHITE])
				printf("Draw\n");
			else {
				if (count[COLOR_BLACK] > count[COLOR_WHITE])
					printf("%s", colorNames[COLOR_BLACK]);
				else
					printf("%s", colorNames[COLOR_WHITE]);

				printf(" Won!\n");
			}
//表示されたら入力待ちになり、入力があったら大元のループを抜けプログラムを終了する
			_getch();
			break;
		}
		
	}
	return 0;
}
