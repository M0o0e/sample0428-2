
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

///1人目

    A:

        printf("1人目が入力してください\n");

        printf("縦列を指定してください\n");
        scanf("%d", &y);

        printf("横列を指定してください\n");
        scanf("%d", &x);

        if (banmen[x][y] == '-') {
            banmen[x][y] = "○";

///横列の確認

            for (j = 0; j <= 3; j++) {
                for (i = 0; i <= 3; i++) {
                    if (banmen[i][j] != "○") {
                        i = 5;
                    }
                }
                if (i == 4) {
                    printf("あなたの勝利です\n");
                    break;
                }

                else {
                    i = 0;
                }
            }

///縦列の確認
            for (i = 0; i <= 3; i++) {
                for (j = 0; j <= 3; j++) {
                    if (banmen[i][j] != "○") {
                        j = 5;
                    }
                }
                if (j == 4) {
                    printf("あなたの勝利です\n");
                    break;
                }

                else {
                    j = 0;
                }
            }
        }

///何か入力されていた場合
        else {
            printf("そこはすでに入力されています\n");
            printf("別の場所を選択してください\n");
            goto A;
        }

///盤面の表示
        ///

///2人目

    B:

        printf("２人目が入力してください\n");

        printf("縦列を指定してください\n");
        scanf("%d", &y);

        printf("横列を指定してください\n");
        scanf("%d", &x);

        if (banmen[x][y] == "-") {
            banmen[x][y] = "×";
        }
        else {
            printf("そこはすでに入力されています\n");
            printf("別の場所を選択してください\n");
            goto B;
        }
    }

    return 0;
}
