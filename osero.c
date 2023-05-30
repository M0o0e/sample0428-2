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

bool checkCanPut(int _color, int _x, int _y) {
	return false;
}


int main() {
	int x,y;

//�F���̍폜
	for (y = 0; y < BOARD_HEIGHT; y++) {
		for (x = 0; x < BOARD_WIDTH; x++) {
			cells[y][x] = COLOR_NONE;
		}
	}

//�J�[�\���������ƕ\������������悤�ɖ������[�v
	while (1) {
//��ʂ̃N���A
		system("cls");
//�Ֆʂ̕\��
	for (y = 0; y < BOARD_HEIGHT; y++) {
		for (x = 0; x < BOARD_WIDTH; x++) {
//�J�[�\���̂���ꏊ�����ŕ\���i�����Ȃ��Ƃ���́E�j
			if ((x == cursorX) && (y == cursorY)) {
				printf("��");
			}
			else {
				switch (cells[y][x]){
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
	printf("%s turn.\n", colorNames[turn]);

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
		if (!checkCanPut(turn, cursorX, cursorY)) {
			break;
		}
		cells[cursorY][cursorX] = turn;
//�^�[���̕ύX�i^=�̓r�b�g���Z�q1��������0,0��������1�Ɂj
		turn ^= 1;
			break;
		}

		
	}

	return 0;
}
