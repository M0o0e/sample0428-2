#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>

///�Ֆʂ̒�`
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

///�F�Ƃ���ɑΉ�����f�[�^�̐ݒ�
enum {
	COLOR_NONE=-1,
	COLOR_BLACK=0,
	COLOR_WHITE=1,
	COLOR_MAX
};
///8�������`�i�΂��u���邩�̃`�F�b�N�p�j
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
//�ǂ���̃^�[������\�����邽�߂̕�����ݒ�
char colorNames[][5 + 1] = {
	"Black",// COLOR_BLACK
	"White",// COLOR_WHITE
};

//�F�������锠�̐ݒ�(�����ݒ�͂O�̂��ߍ��ݒ�)
int cells[BOARD_HEIGHT][BOARD_WIDTH];

//�J�[�\���̐ݒ�(�L�[�{�[�h����)�E�^�[���̐ݒ�
int cursorX, cursorY;
int turn;

//�u���邩�ǂ����̔���ƂЂ�����Ԃ��̏���"checkCanPut"
bool checkCanPut(int _color, int _x, int _y,bool _turnOver) {
	if (cells[_y][_x] != COLOR_NONE) {
		return false;
	}
	for (int i = 0; i < DIRECTION_MAX; i++) {
		int x = _x, y = _y;
		x += directions[i][0];
		y += directions[i][1];

//�������Ă���ʒu������̐F�ł͂Ȃ������烋�[�v�̍ŏ��ɖ߂�(for��)
		if (cells[y][x] != (_color ^ 1))
			continue;

		while (1){
			x += directions[i][0];
			y += directions[i][1];

//�Ֆʂ���͂ݏo�������̏���
			if ((x < 0) || (x >= BOARD_WIDTH) || (y < 0) || (y >= BOARD_HEIGHT))
				break;
//�ׂɐ΂��Ȃ��������̏���
			if (cells[y][x] == COLOR_NONE)
				break;
//�����̐F�Ɠ����΂��������Ƃ��i���߂�Ƃ��jcheck��true�ŕԂ�
			if (cells[y][x] == _color) {
//�Ђ�����Ԃ��̃t���O�������Ă��Ȃ��Ƃ����̂܂�true��������
				if(!_turnOver)
					return true;

//�Ђ�����Ԃ��΂�\���ϐ��̓���
				int x2 = _x, y2 = _y;
				while (1) {
//�Ђ�����Ԃ��ׂ��ꏊ�̐΂̐F�������̐F�ɕύX
					cells[y2][x2] = _color;
//x2,y2�����̏ꏊ�ɐi�߂�
					x2 += directions[i][0];
					y2 += directions[i][1];
//x2,y2��x,y�̒l�Ɠ����ɂȂ����疳�����[�v�𔲂���
					if ((x2 == x) && (y2 == y))
						break;
				}
				break;
			}
		}
	}
	return false;
}

//�p�X�̂��߂̏���"checkCanPutAll"
bool checkCanPutAll(int _color) {
	for (int y = 0; y < BOARD_HEIGHT; y++)
		for (int x = 0; x < BOARD_WIDTH; x++)
//���ׂẴ}�X��checkCanPut�ɂ���āA�u����ꏊ����������true��Ԃ�
			if (checkCanPut(_color, x, y, false))
				return true;
//if���Ɉ��������炸��for���𔲂��Ă��܂�����false��Ԃ��i�u����ꏊ���Ȃ����߃p�X�ɂȂ�j
	return false;
}

void drawBoard() {
//��ʂ̃N���A
	system("cls");
//�Ֆʂ̕\��
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
//�J�[�\���̂���ꏊ�����ŕ\���i�����Ȃ��Ƃ���́E�j
			if ((x == cursorX) && (y == cursorY)) {
				printf("��");
			}
			else {
				switch (cells[y][x]) {
				case COLOR_NONE:	printf("�E");	break;
				case COLOR_BLACK:	printf("��");	break;
				case COLOR_WHITE:	printf("�Z");	break;
				default:
					break;
				}
			}
		}
		printf("\n");
	}
}

int main() {

//�F���̍폜
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			cells[y][x] = COLOR_NONE;
		}
	}
	cells[3][3] = cells[4][4]= COLOR_WHITE;
	cells[3][4] = cells[4][3] = COLOR_BLACK;


	bool cantPut = false;

//�J�[�\���������ƕ\������������悤�ɖ������[�v
	while (1) {
		drawBoard();


//�u���Ȃ�������G���[���b�Z�A�������Ƃ��̓^�[���\��
	if (cantPut) {
		printf("Can't Put!\n");
	}
	else {
		printf("%s turn.\n", colorNames[turn]);
	}
	
//(�^�[���\�������߂�����)(���͂���������)�u���Ȃ������L�^���폜
	cantPut = false;

//�J�[�\���𓮂����i_getch�ŃL�[�{�[�h���́j
		switch (_getch()) {
//��
	case'w':	cursorY--;	break;
//��
	case's':	cursorY++;	break;
//��
	case'a':	cursorX--;	break;
//�E
	case'd':	cursorX++;	break;
//���̂ق��̃L�[���������炻���ɐ΂�u��
	default:
//�����邩�`�F�b�N����֐����U��������u���Ȃ������Ƃ����L�^���c���A�΂�u�����ɏI���
		if (!checkCanPut(turn, cursorX, cursorY,false)) {
			cantPut = true;
			break;
		}

//�Ђ�����Ԃ�
		checkCanPut(turn, cursorX, cursorY, true);

//�΂�u���i�^�[���̂ق��̐΂�u���j
		cells[cursorY][cursorX] = turn;
//�^�[���̕ύX�i^=�̓r�b�g���Z�q1��������0,0��������1�Ɂj
		turn ^= 1;

//�^�[����ύX�����悪�p�X�̏ꍇ�i�u���ꏊ���Ȃ������ꍇ�j������x�^�[���ύX������
		if (!checkCanPutAll(turn))
			turn ^= 1;
		break;
		}
	
//�ǂ�����΂�u�����Ƃ��ł��Ȃ��������Q�[���̏I���i�Ֆʂ̕\���ƏI����\���j
		if ((!checkCanPutAll(COLOR_BLACK)) && (!checkCanPutAll(COLOR_WHITE))) {

//���݂��̐΂̃J�E���g
			int count[COLOR_MAX] = {0};
			for (int y = 0; y < BOARD_HEIGHT; y++)
				for (int x = 0; x < BOARD_WIDTH; x++)
					if (cells[y][x] != COLOR_NONE)
							count[cells[y][x]]++;
				
			drawBoard();

//���݂��̐΂̐��̕\���Ə��҂܂��͈��������̕\��
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
//�\�����ꂽ����͑҂��ɂȂ�A���͂���������匳�̃��[�v�𔲂��v���O�������I������
			_getch();
			break;
		}
		
	}
	return 0;
}
