#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Ang Wilson Alexander - 2502003674

struct data{
	char nama[30];
	int win;
	int lose;
	int draw;
	int point;
}game[15], temp;

char home[100];
char away[100];
int skor, pts;

int jumlah = 8;
int choose = -1;
int in = -1, in2 = -1;

void read(){//read data dari file bola.txt
	FILE *fp = fopen("bola.txt", "r");
	
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%[^\n]\n", game[i].nama);
		fscanf(fp, "win = %d\n", &game[i].win);
		fscanf(fp, "lose = %d\n", &game[i].lose);
		fscanf(fp, "draw = %d\n", &game[i].draw);
		fscanf(fp, "point = %d\n", &game[i].point);
		i++;
	}
	fclose(fp);
}

void score(){//menambahkan hasil pertandingan
	read();
	printf("Home team: ");
	scanf(" %[^\n]", home);getchar();
	printf("Score Home: ");
	scanf("%d", &skor);getchar();
			
	printf("Away team: ");
	scanf(" %[^\n]", away);getchar();
	printf("Score Away: ");
	scanf("%d", &pts);getchar();
	
	linear_search(home);
	if(in != -1){
		if(skor > pts){
		game[in].win += 1;
		game[in].point += 3;
	}else if(skor < pts){
		game[in].lose += 1;
		game[in].point += 0;
	}else if(skor == pts){
		game[in].draw += 1;
		game[in].point += 1;
	}
	}else{
		printf("\nClub %s tidak ditemukan! Tekan ENTER untuk melanjutkan", home);getch();
	}
	
	linear_search2(away);
	if(in2 != -1){
		if(skor > pts){
		game[in2].lose += 1;
		game[in2].point += 0;
	}else if(skor < pts){
		game[in2].win += 1;
		game[in2].point += 3;
	}else if(skor == pts){
		game[in2].draw += 1;
		game[in2].point += 1;
	}
	}else{
		printf("\nClub %s tidak ditemukan! Tekan ENTER untuk melanjutkan", away);getch();
	}
}

void update(){//update klasemen
	FILE *fp = fopen("bola.txt", "w");
	
	int i;
	for(i = 0; i < jumlah; i++){
		fprintf(fp, "%s\n", game[i].nama);
		fprintf(fp, "win = %d\n", game[i].win);
		fprintf(fp, "lose = %d\n", game[i].lose);
		fprintf(fp, "draw = %d\n", game[i].draw);
		fprintf(fp, "point = %d\n", game[i].point);
	}
	fclose(fp);
}

void sort(){//sorting data
	int a, b;
	for(a = 0;a < jumlah-1; a++){
            for(b = 0; b < (jumlah-1-a); b++){
                if(strcmp(game[b].nama, game[b+1].nama) < 0){
                    temp = game[b];
                    game[b] = game[b+1];
                    game[b+1] = temp;
                }
            }
        }
	
	int x, y;
	for(x = 0;x < jumlah-1; x++){
            for(y = 0; y < (jumlah-1-x); y++){
                if(game[y].point < game[y+1].point){
                    temp = game[y];
                    game[y] = game[y+1];
                    game[y+1] = temp;
                }
            }
        }
}

void show(){//menampilkan semua nama club
	int i;
	for(i = 1; i <= 8; i++){
		printf("%d. %s\n", i, game[i-1].nama);
	}
}

void klasemen(){//menampilkan klasemen sekarang
	printf("==================================================\n");
	printf("=================== Klasemen =====================\n");
	printf("==================================================\n");
	printf("| NO |     NAME      | Win | Lose | Draw | Point |\n");
	int i;
	for(i = 1; i <= jumlah; i++){
		printf("| %d  |%-15s| %-3d | %-4d | %-4d | %-5d |\n", i, game[i-1].nama, game[i-1].win, game[i-1].lose, game[i-1].draw, game[i-1].point);
	}
	printf("==================================================\n");
}

int linear_search(char key[]){//linear search
	int i;
	for(i = 0; i < jumlah; i++){
		if(strcmp(game[i].nama, key) == 0){
			in = i;
			return in;
		}
	}
	return -1;
}

int linear_search2(char key[]){//linear search
	int i;
	for(i = 0; i < jumlah; i++){
		if(strcmp(game[i].nama, key) == 0){
			in2 = i;
			return in2;
		}
	}
	return -1;
}

int main(){
	while(choose != 3){
		printf("1. Menambahkan Hasil Pertandingan\n");
		printf("2. Menampilkan Klasemen\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &choose);getchar();
		
		switch(choose){
			case 1:
				read();
				show();
				score();
				update();
				break;
			case 2:
				read();
				sort();
				klasemen();
				break;
			case 3:
				break;
		}
	}
}
