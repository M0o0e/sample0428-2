
#include <stdio.h>
int main(void) {
    int a, b, i, j, x, y;
    char banmen[4][4];

    for (j = 0; j <= 3; j++) {
        for (i = 0; i <= 3; i++) {
            banmen[j][i] = "-";
        }
        i = 0;
    }

    printf("\t1\t2\t3\n");

    for (i = 1; i <= 4; i++) {
        printf("%d|\t-\t-\t-\n", i);
    }

    for (i = 1; i <= 4; i++) {

///1�l��

    A:

        printf("1�l�ڂ����͂��Ă�������\n");

        printf("�c����w�肵�Ă�������\n");
        scanf("%d", &y);

        printf("������w�肵�Ă�������\n");
        scanf("%d", &x);

        if (banmen[x][y] == '-') {
            banmen[x][y] = "��";

///����̊m�F

            for (j = 0; j <= 3; j++) {
                for (i = 0; i <= 3; i++) {
                    if (banmen[i][j] != "��") {
                        i = 5;
                    }
                }
                if (i == 4) {
                    printf("���Ȃ��̏����ł�\n");
                    break;
                }

                else {
                    i = 0;
                }
            }

///�c��̊m�F
            for (i = 0; i <= 3; i++) {
                for (j = 0; j <= 3; j++) {
                    if (banmen[i][j] != "��") {
                        j = 5;
                    }
                }
                if (j == 4) {
                    printf("���Ȃ��̏����ł�\n");
                    break;
                }

                else {
                    j = 0;
                }
            }
        }

///�������͂���Ă����ꍇ
        else {
            printf("�����͂��łɓ��͂���Ă��܂�\n");
            printf("�ʂ̏ꏊ��I�����Ă�������\n");
            goto A;
        }

///�Ֆʂ̕\��
        ///

///2�l��

    B:

        printf("�Q�l�ڂ����͂��Ă�������\n");

        printf("�c����w�肵�Ă�������\n");
        scanf("%d", &y);

        printf("������w�肵�Ă�������\n");
        scanf("%d", &x);

        if (banmen[x][y] == "-") {
            banmen[x][y] = "�~";
        }
        else {
            printf("�����͂��łɓ��͂���Ă��܂�\n");
            printf("�ʂ̏ꏊ��I�����Ă�������\n");
            goto B;
        }
    }

    return 0;
}
