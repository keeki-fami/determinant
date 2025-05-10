#include<stdio.h>
#pragma warning(disable:4996)

double sarrus(double a[][100]);//三次行列式
double two(double a[][100]);  //二次行列式
double gyouretu(double a[][100],int num,double sub);//4次以上

int main(void)
{
	int i, j, cont, flag,num;
	double ans;
	int kakeru = 1;
	double dummy;
	double a[100][100];
	printf("/*行列式を求める*/\n\n");
	flag = 0;
	ans = 0;
	while (flag == 0) {

		printf("何次式ですか？\n");
		printf("number?-->");
		scanf("%d", &num);
		printf("\n%d次式の行列式を入力してください。\n",num);

		//入力例
		printf("入力例：1 2 3\n");
		printf("        4 5 6\n");
		printf("        7 8 9\n\n");


		for (i = 0; i < num; i++) {
			printf("|");
			for (j = 0; j < num; j++) {
				scanf("%lf", &a[i][j]);
			}
		}

		//１次の行列式
		if (num == 1) {
			ans = a[0][0];
		}

		//２次の行列式
		else if (num == 2) {
			ans = two(a);
		}

		//３次の行列式
		else if (num == 3) {
			ans = sarrus(a);
		}

		//４次以上の行列式
		else {
			if (a[0][0] == 0) {
				for (i = 1; i < num; i++) {
					if (a[i][0] != 0) {
						for (j = 0; j < num; j++) {
							dummy = a[i][j];
							a[i][j] = a[0][j];
							a[0][j] = dummy;
						}
						break;
					}
				}
			}
				ans = gyouretu(a, num,a[0][0]);
		}



		printf("行列式の答えは %lf です。\n\n", ans);
		while (1) {
			//終了させるかどうかの選択
			printf("続けますか？（続ける：１　終了：０)\n");
			printf("]");
			scanf("%d", &cont);
			if (cont == 1) {
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
			}
			else if (cont == 0) {
				flag = 1;
				printf("Thank you!!\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
			}
			else {
				printf("不正な入力を検知しました。０か１を入力してください。\n");
			}
		}

	}

	return 0;
}

//２次の行列式
double two(double a[][100])
{
	double ans,x,y;
	x = a[0][0] * a[1][1];
	y = a[0][1] * a[1][0];
	ans = x - y;
	return ans;
}

//３次の行列式
double sarrus(double a[][100]) {
	double h, i, j, k, l, m;
	double ans;

	h = a[0][0] * a[1][1] * a[2][2];
	i = a[1][0] * a[2][1] * a[0][2];
	j = a[2][0] * a[0][1] * a[1][2];

	k = a[0][2] * a[1][1] * a[2][0];
	l = a[0][0] * a[1][2] * a[2][1];
	m = a[2][2] * a[0][1] * a[1][0];

	ans = (h + i + j) - (k + l + m);


	return ans;
}

//4次以上の行列式
//３字になるまで余因子展開をする
double gyouretu(double a[][100], int num,double sub)
{
	int i, j;
	double dummy = 0;;
	double b[100][100]; //くくった数字
	int x, y;
	double sigh = 0;
	x = 0; y = 0;

	printf("\n%d次の行列\n", num);

	for (i = 0; i < num; i++) {
		printf("|");
		for (j = 0; j < num; j++) {
			printf("%d ",(int)a[i][j]);
		}
		printf("\n");
	}

	if (num == 3) {
		return sarrus(a);
	}
	
	//☆最初に０行０列目を０以外の数字にする

	//①　０行目を０行０列目の数字でくくる
	//②　０行目とその他の行に対し、行基本変形を施す
	//③　再帰させる（くくった行とnum-1次正方行列の行列式をを返す)

	else {

		//①０行０列目を１にする
		for (j = 0; j < num; j++) {
			a[0][j] = a[0][j] / sub;
		}

		//②と③行基本変形を施す。
		for (i = 1; i < num; i++) {
			for (j = 1; j < num; j++) {
				b[x][y] = a[i][j] - (a[0][j] * a[i][0]);
				y++;
			}
			x++; y = 0;
		}
		
		printf("最初にくくった数字は %lf 。\n", sub);
		
		//③再帰関数
		if (a[0][0] == 0) {
			for (i = 1; i < num; i++) {
				if (a[i][0] != 0) {
					for (j = 0; j < num; j++) {
						dummy = a[i][j];
						a[i][j] = a[0][j];
						a[0][j] = dummy;
					}
				}
			}
		}
			return sub*(gyouretu(b, num - 1,a[0][0]));
	}
}






