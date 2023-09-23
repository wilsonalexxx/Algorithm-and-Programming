#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//variabel declaration
long int jumlah = 0;
long int ch, nomor = 1, i = 0, ch2, ulg = 0;
char name[50], npw[50], cnpw[50], pw[50];
struct data{
	char judul[20];
	char diary[10000];
}gue[100];

// partially done
void delay(unsigned seconds){
    int ms = 1000 * seconds;
    clock_t start = clock();
    while (clock() < start + ms);
}

//bikin akun
void bikin_akun(){
    int ulang = 0, percobaan = 3;
    printf("Masukkan nama anda: ");
    scanf("%[^\n]", name);
    getchar();
    FILE *hah = fopen("Diaryku.txt", "w");
    fprintf(hah, "%s\n", name);
    printf("Masukkan password baru: ");
    scanf("%[^\n]", &npw);
    getchar();
    while(ulang != 1){
        printf("Konfirmasi password: ");
        scanf("%[^\n]", &cnpw);
        getchar();
        if(strcmp(npw,cnpw) == 0){
            strcpy(pw,npw);
            break;
        }
        printf("Password salah, %dx percobaan lagi!\n", percobaan);
        percobaan--;
        if(percobaan == -1){
            printf("Jalankan program kembali!\n");
            exit(0);
        }
    }
    fprintf(hah, "%s\n", pw);
    fclose(hah);
    printf("Akun berhasil dibuat!\n");
}

//login
void login(){
    int temp;
    FILE *hah = fopen("Diaryku.txt", "r");
    fscanf(hah, "%[^\n]\n", name);
    fscanf(hah, "%[^\n]\n", pw);
    fclose(hah);
    printf("Selamat datang kembali %s!\n",name);
    int percobaan = 3, ulang = 0;
    while(ulang != 1){
        printf("Masukkan password: ");
        scanf("%[^\n]", &cnpw);
        getchar();
        if(strcmp(pw,cnpw) == 0){
            break;
        }
        printf("Password salah, %dx percobaan lagi!\n", percobaan);
        percobaan--;
        if(percobaan == -1){
            printf("Jalankan program kembali!\n");
            exit(0);
        }
    }
    printf("Anda berhasil Login!\n");
    delay(1);
}

//display awal
void display_menu(){
	system("cls");
    printf("MAIN MENU\n");
    printf("1. Add diary\n");
    printf("2. Show diary\n");
    printf("3. Delete diary\n");
    printf("4. Exit\n");
    printf("Menu yang ingin dipilih: ");
}

// delete diary
void dele(int delet){
	system("cls");
	FILE *hah = fopen("Diaryku.txt", "r");
	FILE *temp_hah = fopen("temp_diary.txt", "a");
	
	int simpan = 0;
	int z = 1;
	while(!feof(hah)){
		if(simpan == 0){
			fscanf(hah, "%[^\n]\n", name);
			fscanf(hah, "%[^\n]\n", pw);
			fprintf(temp_hah, "%s\n", name);
			fprintf(temp_hah, "%s\n", pw);
		}
		fscanf(hah, "Diary %d\n", &simpan);
		fscanf(hah, "Judul\t: %[^\n]\n", gue[z-1].judul);
		fscanf(hah, "isi\t: %[^\n]\n", gue[z-1].diary);
		if(z != delet){
			fprintf(temp_hah, "Diary %d\n", z);
			fprintf(temp_hah, "Judul\t: %s\n", gue[z-1].judul);
			fprintf(temp_hah, "isi\t: %s\n", gue[z-1].diary);
			z++;
		}else{
			delet = 0;
		}
	}
	fclose(hah);
	fclose(temp_hah);
	remove("Diaryku.txt");
	rename("temp_diary.txt", "Diaryku.txt");
}

//show judul
void show_dia(){
	system("cls");
	
	FILE *hah = fopen("Diaryku.txt", "r");
	
	int simpan = 0;
	int z = 1;
	while(!feof(hah)){
		if(z == 1){
			fscanf(hah, "%[^\n]\n", name);
			fscanf(hah, "%[^\n]\n", pw);
		}
		fscanf(hah, "Diary %d\n", &simpan);
		fscanf(hah, "Judul\t: %[^\n]\n", gue[z-1].judul);
		fscanf(hah, "isi\t: %[^\n]\n", gue[z-1].diary);
		
		if(ch != 1){
			printf("%d. %s\n", z, gue[z-1].judul);
		}
		z++;
		jumlah = simpan;
	}
	fclose(hah);
}

//add new diary
void bikin_diary(){
	system("cls");
	show_dia();
	FILE *hah = fopen("Diaryku.txt", "a");
	printf("Judul\t: ");
	scanf(" %[^\n]", gue[jumlah].judul);
	fprintf(hah, "Diary %d\nJudul\t: ", jumlah+1);
	fprintf(hah, "%s\n", gue[jumlah].judul);
	printf("Isi\t: ");
	scanf(" %[^\n]", gue[jumlah].diary);
	fprintf(hah, "isi\t: %s\n", gue[jumlah].diary);
//	i++;
	fclose(hah);
}

//show judul & isi
void showall(){
	FILE *hah = fopen("Diaryku.txt", "r");
	int a;
	printf("Diary mana yang ingin ditampilkan?\nDiary ke-");
	scanf("%d", &a);
	
	int simpan = 0;
	int z = 1;
	while(!feof(hah)){
		if(z == 1){
			fscanf(hah, "%[^\n]\n", name);
			fscanf(hah, "%[^\n]\n", pw);
		}
		fscanf(hah, "Diary %d\n", &simpan);
		fscanf(hah, "Judul\t: %[^\n]\n", gue[z-1].judul);
		fscanf(hah, "isi\t: %[^\n]\n", gue[z-1].diary);
		
		if(a == simpan){
			printf("Judul\t: %s\n", gue[a-1].judul);
			printf("Isi\t: %s\n", gue[a-1].diary);
		}
		z++;
	}
	fclose(hah);
}

// main program
int main(){
    system("cls");
    FILE *cek = fopen("Diaryku.txt", "r");
    if(cek == NULL){
        printf("Nampaknya anda belum mempunyai akun atau data error\n");
        printf("Silahkan buat akun baru\n\n");
        bikin_akun();
    }
    else{
        login();
    }
    fclose(cek);
    printf("Selamat datang di program Personal Electronic Diary");
    while(ch != 4){
        display_menu();
        scanf("%ld", &ch);
        if(ch == 1){
        	bikin_diary();
        	printf("Diary berhasil ditambahkan! Press ENTER to continue.");getch();
        }
        else if(ch == 2){
				show_dia();
				showall();
				printf("Press ENTER to continue.");getch();
        }
        else if(ch == 3){
			int hapus;
			show_dia();
			printf("Diary mana yang ingin dihapus?\n");
			printf("Diary ke ");
			scanf("%d", &hapus);
			printf("Diary berhasil dihapus! Press ENTER to continue.");getch();
			dele(hapus);
        }
    }
}
