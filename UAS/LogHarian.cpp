#include <stdio.h>
#include <stdlib.h>

struct data{
	char judul[31];
	char isi[301];
}log[1001];// struct untuk menyimpan log harian

int choose = -1;
int jumlah = 0;
int show = 0;

void readlog(){ //untuk menread semua yang ada di data
	FILE *fp = fopen("log.txt", "r");
	
	int simpan = 0;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "Log Harian %d\n", &simpan);//menscan Log Harian keberapa
		fscanf(fp, "Judul: %[^\n]\n", log[i].judul);//menscan dan menyimpan di struct
		fscanf(fp, "Isi: %[^\n]\n", log[i].isi);//menscan dan menyimpan di struct
		i++;
	}
	jumlah = simpan;
	fclose(fp);
}

void make(){//untuk membuat log harian
	FILE *fp = fopen("log.txt", "a");
	
	printf("Judul: ");getchar();
	scanf("%[^\n]", log[jumlah].judul);//memasukan judul log harian
	printf("Isi: ");getchar();
	scanf("%[^\n]", log[jumlah].isi);//memasukan isi log harian
	
	fprintf(fp, "Log Harian %d\n", jumlah+1);//memprint di file, log harian ke berapa
	fprintf(fp, "Judul: %s\n", log[jumlah].judul);//memprint di file, judul log harian
	fprintf(fp, "Isi: %s\n", log[jumlah].isi);//memprint di file isi log harian
	
	jumlah++;
	fclose(fp);
}

void showjudul(){//menampilkan judul judul log harian
	int i;
	for(i = 0; i < jumlah; i++){
		printf("%d. %s\n", i+1, log[i].judul);
	}
}

void showlog(){//menampilkan judul dan isi yang dipilih user
	int i;
	for(i = 0; i < jumlah; i++){
		if((i+1) == show){
			printf("Judul: %s\n", log[i].judul);
			printf("Isi: %s\n", log[i].isi);
		}
	}
}

int main(){
	while(choose != 3){
		printf("Selamat datang di program Log Harian\n");
		printf("1. Buat Log\n");
		printf("2. Tampilkan Log\n");
		printf("3. Exit\n");
		printf(">> ");
		scanf("%d", &choose);
		
		switch(choose){
			case 1:
			 	readlog();
				make();
				break;
			
			case 2:
				readlog();
				showjudul();
				printf("Log mana yang mau ditampilkan?\n");
				printf(">> ");
				scanf("%d", &show);
				showlog();
				break;
				
			case 3:
				break;
		}
	}
	return 0;
}
