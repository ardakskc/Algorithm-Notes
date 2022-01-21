#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<locale.h>
#include <time.h>
#include <windows.h>
#define KAYITLI 1
#define BIRAKTI 0
#define SILINDI -1
typedef struct teacher {
int teacher_id;
char teacher_ad[15];
char teacher_soyad[15];
char teacher_unvan[15];
} TEACHER;
typedef struct student {
int student_no;
char student_ad[15];
char student_soyad[15];
int ders_sayi;
int ders_kredi;
} STUDENT;
typedef struct course {
int course_kod;
char course_ad[20];
int course_kredi;
int course_kont;
int veren;
} COURSE;
typedef struct ders_kayit {
int id;
int st_id;
int ders_kod;
char kayit_tarih[25];
int durum;
}DERS_KAYIT;
void sil_course();//Ogretim Uyesi Silme Ýsleminde kullandýðým için yukarýda tanýmladým.
void ekle_teacher(){
	TEACHER tc,tc1;
	FILE *fp;
	int tmp=0;
	printf("Ogretim Uyesi ID'si: ");scanf("%d",&tc.teacher_id);
	fp=fopen("teacher.txt","r");
	do{
		rewind(fp);
		tmp=0;
		while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc1.teacher_id,tc1.teacher_ad,tc1.teacher_soyad,tc1.teacher_unvan);
			if(tc.teacher_id==tc1.teacher_id){
				tmp++;
			}
		}
		if(tmp!=0){
			printf("Belittiginiz ID ile eslesen bir ogretim gorevlisi zaten var.Lutfen tekrar giriniz.\n");
			printf("Ogretim Uyesi ID'si: ");scanf("%d",&tc.teacher_id);
		}
	}while(tmp!=0);
	fclose(fp);
	printf("Ogretim Uyesi Adi ve Soyadi: ");scanf("%s %s",tc.teacher_ad,tc.teacher_soyad);
	printf("Ogretim Uyesi Unvani: ");scanf("%s",tc.teacher_unvan);
	fp=fopen("teacher.txt","a");
	fprintf(fp,"%d	%s %s	%s\n",tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
	fclose(fp);
	printf("\nOgretim Uyesi Eklenmistir...\n");
}
void gunc_teacher(){
	TEACHER *tc;
	int id,tmp=0,i,j=0;
	FILE *fp;
	fp=fopen("teacher.txt","r");
	tc=(TEACHER *)malloc(sizeof(TEACHER));
	printf("-Ogretim Uyesi Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc[j].teacher_id,tc[j].teacher_ad,tc[j].teacher_soyad,tc[j].teacher_unvan);
			printf("ID: %d	Ad Soyad: %s %s Unvan: %s\n",tc[j].teacher_id,tc[j].teacher_ad,tc[j].teacher_soyad,tc[j].teacher_unvan);
	}
	rewind(fp);
	printf("\nBilgilerini Guncellemek Istediginiz Ogretim Uyesinin ID'sini Giriniz: ");scanf("%d",&id);
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%s\n",&tc[j].teacher_id,tc[j].teacher_ad,tc[j].teacher_soyad,tc[j].teacher_unvan);
		if(id==tc[j].teacher_id){
			tmp=1;
		}
		tc=(TEACHER *)realloc(tc,(j+2)*sizeof(TEACHER));
		j++;
	}
	if(tmp==0){
		printf("\nBelittiginiz ID ile eslesen ogretim gorevlisi bulunamadi...\n");
		fclose(fp);
		free(tc);
		return;
	}
	fclose(fp);
	fp=fopen("teacher.txt","w");
	for(i=0;i<j;i++){
		if(id==tc[i].teacher_id){
			printf("Eski Ogretim Uyesi Adi ve Soyadi: %s %s\n",tc[i].teacher_ad,tc[i].teacher_soyad);
			printf("Yeni Ogretim Uyesi Adi ve Soyadi: ");scanf("%s %s",tc[i].teacher_ad,tc[i].teacher_soyad);
			printf("Eski Ogretim Unvani: %s\n",tc[i].teacher_unvan);
			printf("Yeni Ogretim Uyesi Unvani: ");scanf("%s",tc[i].teacher_unvan);
			fprintf(fp,"%d	%s %s	%s\n",tc[i].teacher_id,tc[i].teacher_ad,tc[i].teacher_soyad,tc[i].teacher_unvan);
		}
		else{
			fprintf(fp,"%d	%s %s	%s\n",tc[i].teacher_id,tc[i].teacher_ad,tc[i].teacher_soyad,tc[i].teacher_unvan);
		}
	}
	printf("\nOgretim Uyesi Bilgileri Guncellenmistir.\n");
	fclose(fp);
	free(tc);
}
void sil_teacher(){
	TEACHER *tc;
	COURSE cs;
	int id,tmp=0,i,j=0,secim;
	FILE *fp;
	fp=fopen("teacher.txt","r");
	tc=(TEACHER *)malloc(sizeof(TEACHER));
	printf("-Ogretim Uyesi Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc[j].teacher_id,tc[j].teacher_ad,tc[j].teacher_soyad,tc[j].teacher_unvan);
			printf("ID: %d	Ad Soyad: %s %s Unvan: %s\n",tc[j].teacher_id,tc[j].teacher_ad,tc[j].teacher_soyad,tc[j].teacher_unvan);
	}
	rewind(fp);
	printf("\nSilmek Istediginiz Ogretim Uyesinin ID'sini Giriniz: ");scanf("%d",&id);
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%s\n",&tc[j].teacher_id,tc[j].teacher_ad,tc[j].teacher_soyad,tc[j].teacher_unvan);
		if(id==tc[j].teacher_id){
			tmp=1;
		}
		tc=(TEACHER *)realloc(tc,(j+2)*sizeof(TEACHER));
		j++;
	}
	if(tmp==0){
		printf("\nBelittiginiz ID ile eslesen ogretim gorevlisi bulunamadi...\n");
		fclose(fp);
		free(tc);
		return;
	}
	fclose(fp);
	tmp=0;
	fp=fopen("course.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
		if(id==cs.veren){
			tmp=1;
		}
	}
	if(tmp==1){
		printf("\nID'sini Girdiginiz Ogretim Uyesi Suan Aktif Olarak Bir Ders Vermektedir.\nOgretim Uyesini Silmek Icin Lutfen Oncelikle Verdigi Dersi Siliniz...\n");
		printf("Dersi Silmek Istiyorsanýz 1'e (Ders silindikten sonra ogretim uyesi otomatik olarak silinecektir.)\nIstemiyorsaniz 0'a basiniz\n");
		scanf("%d",&secim);
		if(secim==1){
			sil_course();
		}
		else{
			fclose(fp);
			free(tc);
			return;
		}
	}
	fclose(fp);
	fp=fopen("teacher.txt","w");
	for(i=0;i<j;i++){
		if(id!=tc[i].teacher_id){
			fprintf(fp,"%d	%s %s	%s\n",tc[i].teacher_id,tc[i].teacher_ad,tc[i].teacher_soyad,tc[i].teacher_unvan);
		}
		else{
			printf("\nOgretim Uyesi Silinmistir...\n");
		}
	}
	fclose(fp);
	free(tc);
}
void ekle_course(){
	COURSE cs,cs1;
	TEACHER tc;
	FILE *fp;
	int tmp=0;
	printf("Ders Kodu: ");scanf("%d",&cs.course_kod);
	fp=fopen("course.txt","r");
	do{
		rewind(fp);
		tmp=0;
		while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs1.course_kod,cs1.course_ad,&cs1.course_kredi,&cs1.course_kont,&cs1.veren);
			if(cs.course_kod==cs1.course_kod){
				tmp++;
			}
		}
		if(tmp!=0){
			printf("Belittiginiz Kod ile eslesen bir ders zaten var.Lutfen tekrar giriniz.\n");
			printf("Ders Kodu: ");scanf("%d",&cs.course_kod);
		}
	}while(tmp!=0);
	fclose(fp);
	fflush(stdin);
	printf("Ders Adi: ");gets(cs.course_ad);
	printf("Ders Kredisi: ");scanf("%d",&cs.course_kredi);
	printf("Ders Kontenjani: ");scanf("%d",&cs.course_kont);
	
	tmp=0;
	fp=fopen("teacher.txt","r");
	printf("-Ogretim Uyesi Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
			printf("ID: %d	Ad Soyad: %s %s Unvan: %s\n",tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
	}
	rewind(fp);
	printf("Dersi Veren Ogretim Uyesi ID'si:");scanf("%d",&cs.veren);
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
			if(cs.veren==tc.teacher_id){
				tmp=1;
			}
	}
	if(tmp==0){
			printf("\nBelittiginiz ID ile eslesen ogretim gorevlisi bulunamadi...\n");
			fclose(fp);
			return;
	}
	fclose(fp);
	fp=fopen("course.txt","a");
	fprintf(fp,"%d	%s	%d	%d - %d\n",cs.course_kod,cs.course_ad,cs.course_kredi,cs.course_kont,cs.veren);
	fclose(fp);
	printf("\nDers Eklenmistir...\n");
}
void gunc_course(){
	COURSE *cs;
	TEACHER tc;
	DERS_KAYIT kyt;
	STUDENT *st;
	int kod,tmp=0,i,j=0,kredi;
	FILE *fp,*fp1;
	st=(STUDENT *)malloc(sizeof(STUDENT));
	cs=(COURSE *)malloc(sizeof(COURSE));
	fp=fopen("course.txt","r");
	printf("-Ders Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[j].course_kod,cs[j].course_ad,&cs[j].course_kredi,&cs[j].course_kont,&cs[j].veren);
			printf("Kodu: %d	Adi: %s  Kredisi: %d Kontenjani: %d Dersi Veren Ogr.Uyesi ID'si: %d\n\n",cs[j].course_kod,cs[j].course_ad,cs[j].course_kredi,cs[j].course_kont,cs[j].veren);
	}
	rewind(fp);
	printf("Bilgilerini Guncellemek Istediginiz Dersin Kodunu Giriniz: ");scanf("%d",&kod);
	while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[j].course_kod,cs[j].course_ad,&cs[j].course_kredi,&cs[j].course_kont,&cs[j].veren);
			if(kod==cs[j].course_kod){
				tmp=1;
			}
			cs=(COURSE *)realloc(cs,(j+2)*sizeof(COURSE));
			j++;
	}
	if(tmp==0){
			printf("\nBelittiginiz Kod ile eslesen ders bulunamadi...\n");
			fclose(fp);
			free(cs);
			free(st);
			return;
	}
	fclose(fp);
	fp=fopen("course.txt","w");
	for(i=0;i<j;i++){
		if(cs[i].course_kod==kod){
			printf("Eski Ders Adi: %s\n",cs[i].course_ad);
			fflush(stdin);
			printf("Yeni Ders Adi: ");gets(cs[i].course_ad);
			printf("Eski Ders Kredisi: %d\n",cs[i].course_kredi);
			kredi=cs[i].course_kredi;
			printf("Yeni Ders Kredisi: ");scanf("%d",&cs[i].course_kredi);
			kredi=cs[i].course_kredi-kredi;//Ogrencilerin aldýðý kredileri arttýrýp azaltmak icin
			printf("Eski Ders Kalan Kontenjani: %d\n",cs[i].course_kont);
			printf("Yeni Ders Kalan Kontenjani: ");scanf("%d",&cs[i].course_kont);
			while(cs[i].course_kont<0){
				printf("\nKontenjan Negatif Bir Deger Alamaz.Lutfen Tekrar Giriniz...\n");
				printf("Yeni Ders Kalan Kontenjani: ");scanf("%d",&cs[i].course_kont);
			}
			printf("Eski Ders Veren Ogretim Uyesi ID'si: %d",cs[i].veren);
			tmp=0;
			fp1=fopen("teacher.txt","r");
			printf("\n-Ogretim Uyesi Listesi-\n\n");
			while(!feof(fp1)){
					fscanf(fp1,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
					printf("ID: %d	Ad Soyad: %s %s Unvan: %s\n",tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
			}
			rewind(fp1);
			printf("Yeni Dersi Veren Ogretim Uyesi ID'si:");scanf("%d",&cs[i].veren);
			while(tmp==0){
				rewind(fp1);
				while(!feof(fp1)){
						fscanf(fp1,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
						if(cs[i].veren==tc.teacher_id){
							tmp=1;
						}
				}
				if(tmp==0){
					printf("\nBelittiginiz ID ile eslesen ogretim gorevlisi bulunamadi.Lutfen tekrar giriniz.\n");
					printf("Yeni Dersi Veren Ogretim Uyesi ID'si:");scanf("%d",&cs[i].veren);
				}
			}
			fclose(fp1);
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
		}
		else{
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
		}
	}
	fclose(fp);
	free(cs);
	j=0;
	//Dersi Alan Ogrencilerin Kredilerini Degistirme.
	fp=fopen("student.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
		st=(STUDENT *)realloc(st,(j+2)*sizeof(STUDENT));
		j++;
	}
	fclose(fp);
	fp=fopen("ders_kayit.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt.id,&kyt.st_id,&kyt.ders_kod,kyt.kayit_tarih,&kyt.durum);
		if(kyt.ders_kod==kod && kyt.durum!=-1){
			for(i=0;i<j;i++){
				if(kyt.st_id==st[i].student_no){
					st[i].ders_kredi+=kredi;
				}
			}
		}
	}
	fclose(fp);
	fp=fopen("student.txt","w");
	for(i=0;i<j;i++){
		fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
	}
	fclose(fp);
	free(st);
	printf("\nDers Bilgileri Guncellenmistir.\n");
}
void sil_course(){
	COURSE *cs;
	DERS_KAYIT *kyt;
	STUDENT *st;
	int kod,tmp=0,i,j=0,kredi,n,m,k,sayac=0;
	FILE *fp;
	kyt=(DERS_KAYIT *)malloc(sizeof(DERS_KAYIT));
	st=(STUDENT *)malloc(sizeof(STUDENT));
	cs=(COURSE *)malloc(sizeof(COURSE));
	fp=fopen("course.txt","r");
	printf("-Ders Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[j].course_kod,cs[j].course_ad,&cs[j].course_kredi,&cs[j].course_kont,&cs[j].veren);
			printf("Kodu: %d	Adi: %s  Kredisi: %d Kontenjani: %d Dersi Veren Ogr.Uyesi ID'si: %d\n\n",cs[j].course_kod,cs[j].course_ad,cs[j].course_kredi,cs[j].course_kont,cs[j].veren);
	}
	rewind(fp);
	printf("Silmek Istediginiz Dersin Kodunu Giriniz: ");scanf("%d",&kod);
	while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[j].course_kod,cs[j].course_ad,&cs[j].course_kredi,&cs[j].course_kont,&cs[j].veren);
			if(kod==cs[j].course_kod){
				tmp=1;
				kredi=cs[j].course_kredi;
			}
			cs=(COURSE *)realloc(cs,(j+2)*sizeof(COURSE));
			j++;
	}
	if(tmp==0){
			printf("\nBelittiginiz Kod ile eslesen ders bulunamadi...\n");
			fclose(fp);
			free(cs);
			free(st);
			free(kyt);
			return;
	}
	fclose(fp);
	n=j;
	j=0;
	fp=fopen("ders_kayit.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt[j].id,&kyt[j].st_id,&kyt[j].ders_kod,kyt[j].kayit_tarih,&kyt[j].durum);
		if(kyt[j].ders_kod==kod && kyt[j].durum!=-1){
			sayac++;
		}
		kyt=(DERS_KAYIT *)realloc(kyt,(j+2)*sizeof(DERS_KAYIT));
		j++;
	}
	fclose(fp);
	if(sayac==0){//Dersi Alan Ogrenci Yoksa Direkt Ciksin Diye
		fp=fopen("course.txt","w");
		for(i=0;i<n;i++){
			if(cs[i].course_kod!=kod){
				fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
			}
			else{
				printf("\nDers Basariyla Silinmistir...\n");
			}
		}
		fclose(fp);
		free(cs);
		free(st);
		free(kyt);
		return;
	}
	m=j;
	j=0;
	fp=fopen("student.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
		st=(STUDENT *)realloc(st,(j+2)*sizeof(STUDENT));
		j++;
	}
	fclose(fp);
	for(i=0;i<m;i++){
		if(kod==kyt[i].ders_kod && kyt[i].durum!=-1){
			for(k=0;k<j;k++){
				if(kyt[i].st_id==st[k].student_no){
					st[k].ders_kredi-=kredi;
					st[k].ders_sayi--;
				}
			}
			kyt[i].durum=-1;
		}
	}
	fp=fopen("student.txt","w");
	for(i=0;i<j;i++){
		fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
	}
	fclose(fp);
	fp=fopen("ders_kayit.txt","w");
	for(i=0;i<m;i++){
		fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt[i].id,kyt[i].st_id,kyt[i].ders_kod,kyt[i].kayit_tarih,kyt[i].durum);
	}
	fclose(fp);
	fp=fopen("course.txt","w");
	for(i=0;i<n;i++){
		if(cs[i].course_kod!=kod){
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
		}
		else{
			printf("\nGirdiginiz Koda ait ders silinmistir...\n");
			printf("Ilgili ders kayitlari ve dersi alan ogrenci kredileri de düzeltilmistir...\n");
		}
	}
	fclose(fp);
	free(cs);
	free(st);
	free(kyt);
}
void ekle_student(){
	STUDENT st,st1;
	FILE *fp;
	int tmp=0;
	printf("Ogrenci Numarasi: ");scanf("%d",&st.student_no);
	fp=fopen("student.txt","r");
	do{
		rewind(fp);
		tmp=0;
		while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st1.student_no,st1.student_ad,st1.student_soyad,&st1.ders_sayi,&st1.ders_kredi);
			if(st.student_no==st1.student_no){
				tmp++;
			}
		}
		if(tmp!=0){
			printf("Belittiginiz Numara ile eslesen bir ogrenci zaten var.Lutfen tekrar giriniz.\n");
			printf("Ogrenci Numarasi: ");scanf("%d",&st.student_no);
		}
	}while(tmp!=0);
	fclose(fp);
	fflush(stdin);
	printf("Ogrenci Adi ve Soyadi: ");scanf("%s %s",st.student_ad,st.student_soyad);
	st.ders_sayi=0;st.ders_kredi=0;
	fp=fopen("student.txt","a");
	fprintf(fp,"%d	%s %s	%d	%d\n",st.student_no,st.student_ad,st.student_soyad,st.ders_sayi,st.ders_kredi);
	
	fclose(fp);
	printf("\nOgrenci Eklenmistir...");
}
void sil_student(){
	STUDENT *st;
	COURSE *cs;
	DERS_KAYIT *kyt;
	int no,tmp=0,i,j=0,n,m,k,sayac=0;
	FILE *fp;
	kyt=(DERS_KAYIT *)malloc(sizeof(DERS_KAYIT));
	st=(STUDENT *)malloc(sizeof(STUDENT));
	cs=(COURSE *)malloc(sizeof(COURSE));
	fp=fopen("student.txt","r");
	printf("-Ogrenci Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
			printf("No: %d	Ad Soyad: %s %s \n\n",st[j].student_no,st[j].student_ad,st[j].student_soyad);
	}
	rewind(fp);
	printf("\nSilmek Istediginiz Ogrenci Numarasini Giriniz: ");scanf("%d",&no);
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
			if(no==st[j].student_no){
				tmp=1;
			}
			st=(STUDENT *)realloc(st,(j+2)*sizeof(STUDENT));
			j++;
	}
	if(tmp==0){
		printf("\nBelittiginiz Numara ile eslesen ogrenci bulunamadi...\n");
		free(st);
		free(cs);
		free(kyt);
		fclose(fp);
		return;
	}
	fclose(fp);
	n=j;
	j=0;
	fp=fopen("ders_kayit.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt[j].id,&kyt[j].st_id,&kyt[j].ders_kod,kyt[j].kayit_tarih,&kyt[j].durum);
		if(kyt[j].st_id==no && kyt[j].durum!=-1){
			sayac++;
		}
		kyt=(DERS_KAYIT *)realloc(kyt,(j+2)*sizeof(DERS_KAYIT));
		j++;
	}
	fclose(fp);
	if(sayac==0){//Ogrenci Ders Almiyorsa Direkt Ciksin Diye
		fp=fopen("student.txt","w");
		for(i=0;i<n;i++){
			if(st[i].student_no!=no){
				fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
			}
			else{
				printf("\nGirdiginiz Numaralý Ogrenci Silinmistir...\n");
			}
		}
		fclose(fp);
		free(cs);
		free(st);
		free(kyt);
		return;
	}
	m=j;
	j=0;
	fp=fopen("course.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[j].course_kod,cs[j].course_ad,&cs[j].course_kredi,&cs[j].course_kont,&cs[j].veren);
		cs=(COURSE *)realloc(cs,(j+2)*sizeof(COURSE));
		j++;
	}
	fclose(fp);
	for(i=0;i<m;i++){
		if(no==kyt[i].st_id && kyt[i].durum!=-1){
			for(k=0;k<j;k++){
				if(kyt[i].ders_kod==cs[k].course_kod){
					cs[k].course_kont++;
				}
			}
			kyt[i].durum=-1;
		}
	}
	fp=fopen("course.txt","w");
	for(i=0;i<j;i++){
		fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
	}
	fclose(fp);
	fp=fopen("ders_kayit.txt","w");
	for(i=0;i<m;i++){
		fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt[i].id,kyt[i].st_id,kyt[i].ders_kod,kyt[i].kayit_tarih,kyt[i].durum);
	}
	fclose(fp);
	fp=fopen("student.txt","w");
	for(i=0;i<n;i++){
		if(st[i].student_no!=no){
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
		else{
			printf("\nGirdiginiz Numaralý Ogrenci Silinmistir...\n");
			printf("Ilgili ders kayitlari ve ders kontenjani da düzeltilmistir...\n");
		}
	}
	fclose(fp);
	free(cs);
	free(st);
	free(kyt);
}
void gunc_student(){
	STUDENT *st;
	int no,tmp=0,i,j=0;
	FILE *fp;
	st=(STUDENT *)malloc(sizeof(STUDENT));
	fp=fopen("student.txt","r");
	printf("-Ogrenci Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
			printf("No: %d	Ad Soyad: %s %s \n\n",st[j].student_no,st[j].student_ad,st[j].student_soyad);
	}
	rewind(fp);
	printf("\nBilgilerini Guncellemek Istediginiz Ogrenci Numarasini Giriniz: ");scanf("%d",&no);
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
			if(no==st[j].student_no){
				tmp=1;
			}
			st=(STUDENT *)realloc(st,(j+2)*sizeof(STUDENT));
			j++;
	}
	if(tmp==0){
		printf("\nBelittiginiz Numara ile eslesen ogrenci bulunamadi...\n");
		free(st);
		fclose(fp);
		return;
	}
	fclose(fp);
	fp=fopen("student.txt","w");
	for(i=0;i<j;i++){
		if(st[i].student_no==no){
			printf("Eski Ogrenci Adi Soyadi: %s %s\n",st[i].student_ad,st[i].student_soyad);
			printf("Yeni Ogrenci Adi Soyadi: ");scanf("%s %s",st[i].student_ad,st[i].student_soyad);
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
		else{
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
	}
	printf("Girdiginiz Numaralý Ogrenci Bilgileri Guncellenmistir...\n");
	fclose(fp);
	free(st);
}
void derskayit(int max_kredi,int max_ders){
	DERS_KAYIT kyt,kyt1;
	STUDENT *st;
	COURSE *cs;
	int tmp=0,i,j=0,a,b=0,kredi,kontenjan,ders_sayac,kredi_sayac;
	char gun[25],ay[5],yil[5];
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	sprintf(gun, "%d",tm.tm_mday);
  	sprintf(ay, "%d",tm.tm_mon + 1);
  	sprintf(yil, "%d",tm.tm_year + 1900);
  	strcat(gun,"/");strcat(gun,ay);strcat(gun,"/");strcat(gun,yil);
	printf("Ders Almak Isteyen Ogrenci Numarasini Giriniz: ");scanf("%d",&kyt.st_id);
	FILE *fp;
	st=(STUDENT *)malloc(sizeof(STUDENT));
	cs=(COURSE *)malloc(sizeof(COURSE));
	fp=fopen("student.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
		if(kyt.st_id==st[j].student_no){
			tmp=1;
			ders_sayac=st[j].ders_sayi;
			kredi_sayac=st[j].ders_kredi;
		}
		st=(STUDENT *)realloc(st,(j+2)*sizeof(STUDENT));
		j++;
	}
	if(tmp==0){
		printf("\nBelittiginiz Numara ile eslesen ogrenci bulunamadi...\n");
		fclose(fp);
		free(st);
		free(cs);
		return;
	}
	fclose(fp);
	tmp=0;
	printf("\n-Dersler-\n");
	fp=fopen("course.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[b].course_kod,cs[b].course_ad,&cs[b].course_kredi,&cs[b].course_kont,&cs[b].veren);
		printf("Kodu: %d Adi: %s Kredisi: %d Kontenjani: %d\n",cs[b].course_kod,cs[b].course_ad,cs[b].course_kredi,cs[b].course_kont);
	}
	rewind(fp);
	printf("Ogrencinin Almak Istedigi Dersin Kodunu Giriniz: ");scanf("%d",&kyt.ders_kod);
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[b].course_kod,cs[b].course_ad,&cs[b].course_kredi,&cs[b].course_kont,&cs[b].veren);
		if(kyt.ders_kod==cs[b].course_kod){
			tmp=1;
			kredi=cs[b].course_kredi;
			kontenjan=cs[b].course_kont;
		}
		cs=(COURSE *)realloc(cs,(b+2)*sizeof(COURSE));
		b++;
	}
	if(tmp==0 || kontenjan==0){
		if(tmp==0){
		printf("\nBelittiginiz Kod ile eslesen ders bulunamadi...\n");}
		else{
		printf("\nGirdiginiz Kod ile eslesen dersin kontenjani doludur...\n");}
		fclose(fp);
		free(st);
		free(cs);
		return;
	}
	fclose(fp);
	tmp=0;
	fp=fopen("ders_kayit.txt","r");
	fseek(fp,0,SEEK_END);
	tmp=ftell(fp);
	rewind(fp);
	if(tmp!=0){
		while(!feof(fp)){
			fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt1.id,&kyt1.st_id,&kyt1.ders_kod,kyt1.kayit_tarih,&kyt1.durum);
			if(kyt.ders_kod==kyt1.ders_kod && kyt.st_id==kyt1.st_id && kyt1.durum!=-1){
				printf("\nOgrenci Bu Dersi Zaten Almis...\n");
				fclose(fp);
				free(st);
				free(cs);
				return;
			}
			kyt.id=kyt1.id;
		}
		kyt.id++;
	}		
	else{
		kyt.id=1;
	}
	fclose(fp);
	ders_sayac++;kredi_sayac+=kredi;
	if(ders_sayac>max_ders || kredi_sayac>max_kredi){
		if(ders_sayac>max_ders){
			printf("\nOgrenci Alabilecegi Max Ders Sayisini Asmistir.Islem Gerceklestirilemiyor...\n");}
		else{
			printf("\nOgrenci Alabilecegi Max Kredi Sayisi: %d\nOgrencinin Aldigi Kredi Sayisi: %d\nIslem Gerceklestirilemiyor...\n",max_kredi,kredi_sayac);}
		free(st);
		free(cs);
		return;
	}
	fp=fopen("student.txt","w");
	for(i=0;i<j;i++){
		if(st[i].student_no==kyt.st_id){
			st[i].ders_sayi++;st[i].ders_kredi+=kredi;
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
		else{
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
	}
	fclose(fp);
	fp=fopen("course.txt","w");
	for(a=0;a<b;a++){
		if(kyt.ders_kod==cs[a].course_kod){
			cs[a].course_kont--;
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[a].course_kod,cs[a].course_ad,cs[a].course_kredi,cs[a].course_kont,cs[a].veren);
		}
		else{
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[a].course_kod,cs[a].course_ad,cs[a].course_kredi,cs[a].course_kont,cs[a].veren);
		}
	}
	fclose(fp);
	kyt.durum=KAYITLI;
	strcpy(kyt.kayit_tarih,gun);
	fp=fopen("ders_kayit.txt","a");
	fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt.id,kyt.st_id,kyt.ders_kod,kyt.kayit_tarih,kyt.durum);
	fclose(fp);
	free(st);
	printf("Ogrenci Dersi Almistir.\n");
}
void sil_derskayit(){
	DERS_KAYIT *kyt;
	STUDENT *st;
	COURSE *cs;
	int id,tmp=0,i,j=0,n,m,st_id,kredi,ders_kod,durum;
	char gun[25],ay[5],yil[5];
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	sprintf(gun, "%d",tm.tm_mday);
  	sprintf(ay, "%d",tm.tm_mon + 1);
  	sprintf(yil, "%d",tm.tm_year + 1900);
  	strcat(gun,"/");strcat(gun,ay);strcat(gun,"/");strcat(gun,yil);
	FILE *fp;
	kyt=(DERS_KAYIT *)malloc(sizeof(DERS_KAYIT));
	st=(STUDENT *)malloc(sizeof(STUDENT));
	cs=(COURSE *)malloc(sizeof(COURSE));
	fp=fopen("ders_kayit.txt","r");
	printf("- Ogrenci-Ders Listesi -\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt[j].id,&kyt[j].st_id,&kyt[j].ders_kod,kyt[j].kayit_tarih,&kyt[j].durum);
			printf("%d)	Ogrenci NO: %d Ders KOD: %d Durum: %d\n",kyt[j].id,kyt[j].st_id,kyt[j].ders_kod,kyt[j].durum);
	}
	rewind(fp);
	printf("Silmek Istediginiz Ogrenci-Ders Iliskisi Numarasini Giriniz: ");scanf("%d",&id);
	while(!feof(fp)){
		fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt[j].id,&kyt[j].st_id,&kyt[j].ders_kod,kyt[j].kayit_tarih,&kyt[j].durum);
		if(id==kyt[j].id){
			tmp=1;
			st_id=kyt[j].st_id;
			ders_kod=kyt[j].ders_kod;
			durum=kyt[j].durum;
		}
		kyt=(DERS_KAYIT *)realloc(kyt,(j+2)*sizeof(DERS_KAYIT));
		j++;
	}
	n=j;
	j=0;
	if(tmp==0 || durum==-1){
		if(tmp==0){
		printf("\nBelirttiginiz numara ile eslesen Ogrenci-Ders verisi bulunamadi...\n");}
		else if(durum==-1){
		printf("\nBelittiginiz numara ile eslesen Ogrenci-Ders verisi zaten silinmistir...\n");
		}
		fclose(fp);
		free(kyt);
		free(cs);
		free(st);
		return;
	}
	fclose(fp);
	fp=fopen("course.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs[j].course_kod,cs[j].course_ad,&cs[j].course_kredi,&cs[j].course_kont,&cs[j].veren);
		if(ders_kod==cs[j].course_kod){
			kredi=cs[j].course_kredi;
		}
		cs=(COURSE *)realloc(cs,(j+2)*sizeof(COURSE));
		j++;
	}
	m=j;
	j=0;
	fclose(fp);
	fp=fopen("course.txt","w");
	for(i=0;i<m;i++){
		if(ders_kod==cs[i].course_kod){
			cs[i].course_kont++;
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
		}
		else{
			fprintf(fp,"%d	%s	%d	%d - %d\n",cs[i].course_kod,cs[i].course_ad,cs[i].course_kredi,cs[i].course_kont,cs[i].veren);
		}
	}
	fclose(fp);
	fp=fopen("student.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%d	%d\n",&st[j].student_no,st[j].student_ad,st[j].student_soyad,&st[j].ders_sayi,&st[j].ders_kredi);
		st=(STUDENT *)realloc(st,(j+2)*sizeof(STUDENT));
		j++;
	}
	fclose(fp);
	fp=fopen("student.txt","w");
	for(i=0;i<j;i++){
		if(st[i].student_no==st_id){
			st[i].ders_sayi--;st[i].ders_kredi-=kredi;
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
		else{
			fprintf(fp,"%d	%s %s	%d	%d\n",st[i].student_no,st[i].student_ad,st[i].student_soyad,st[i].ders_sayi,st[i].ders_kredi);
		}
	}
	fclose(fp);
	fp=fopen("ders_kayit.txt","w");
	for(i=0;i<n;i++){
		if(kyt[i].id==id){
			kyt[i].durum=SILINDI;
			strcpy(kyt[i].kayit_tarih,gun);
			fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt[i].id,kyt[i].st_id,kyt[i].ders_kod,kyt[i].kayit_tarih,kyt[i].durum);
		}
		else{
			fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt[i].id,kyt[i].st_id,kyt[i].ders_kod,kyt[i].kayit_tarih,kyt[i].durum);
		}
	}
	printf("\nGirdiginiz Ogrenci-Ders Iliskisi Silinmistir...\n");
	fclose(fp);
	free(kyt);
	free(cs);
	free(st);
}
void gunc_derskayit(){
	DERS_KAYIT *kyt;
	int id,tmp=0,i,j=0,durum;
	char gun[25],ay[5],yil[5];
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	sprintf(gun, "%d",tm.tm_mday);
  	sprintf(ay, "%d",tm.tm_mon + 1);
  	sprintf(yil, "%d",tm.tm_year + 1900);
  	strcat(gun,"/");strcat(gun,ay);strcat(gun,"/");strcat(gun,yil);
	FILE *fp;
	kyt=(DERS_KAYIT *)malloc(sizeof(DERS_KAYIT));
	fp=fopen("ders_kayit.txt","r");
	printf("- Ogrenci-Ders Listesi -\n\n");
	while(!feof(fp)){
		fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt[j].id,&kyt[j].st_id,&kyt[j].ders_kod,kyt[j].kayit_tarih,&kyt[j].durum);
		printf("%d)	Ogrenci NO: %d Ders KOD: %d Durum: %d\n",kyt[j].id,kyt[j].st_id,kyt[j].ders_kod,kyt[j].durum);
	}
	rewind(fp);
	printf("\nKayit Durumunu Guncellemek Istediginiz Ogrenci-Ders Iliskisi Numarasini Giriniz: ");scanf("%d",&id);
	while(!feof(fp)){
		fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt[j].id,&kyt[j].st_id,&kyt[j].ders_kod,kyt[j].kayit_tarih,&kyt[j].durum);
		if(id==kyt[j].id){
			tmp=1;
			durum=kyt[j].durum;
		}
		kyt=(DERS_KAYIT *)realloc(kyt,(j+2)*sizeof(DERS_KAYIT));
		j++;
	}
	if(tmp==0 || durum==0){
		if(tmp==0){
		printf("\nBelittiginiz numara ile eslesen Ogrenci-Ders verisi bulunamadi...\n");}
		else{
		printf("\nBelittiginiz numara ile eslesen Ogrenci-Ders verisi zaten birakilmis durumdadir...\n");
		}
		fclose(fp);
		free(kyt);
		return;
	}
	fclose(fp);
	fp=fopen("ders_kayit.txt","w");
	for(i=0;i<j;i++){
		if(kyt[i].id==id){
			kyt[i].durum=BIRAKTI;
			strcpy(kyt[i].kayit_tarih,gun);
			fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt[i].id,kyt[i].st_id,kyt[i].ders_kod,kyt[i].kayit_tarih,kyt[i].durum);
		}
		else{
			fprintf(fp,"%d)	%d - %d	%s - %d\n",kyt[i].id,kyt[i].st_id,kyt[i].ders_kod,kyt[i].kayit_tarih,kyt[i].durum);
		}
	}
	printf("Girdiginiz Ogrenci-Ders Durumu Guncellenmistir...\n");
	fclose(fp);
	free(kyt);
}
void teacher_courses(){
	TEACHER tc;
	COURSE cs;
	int id,tmp=0;
	FILE *fp;
	fp=fopen("teacher.txt","r");
	printf("-Ogretim Uyesi Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
			printf("ID: %d	Ad Soyad: %s %s Unvan: %s\n",tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
	}
	rewind(fp);
	printf("\nVerdigi Dersleri Gormek Istediginiz Ogretim Uyesinin ID'sini Giriniz: ");scanf("%d",&id);
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
			if(id==tc.teacher_id){
				tmp=1;
			}
	}
	if(tmp==0){
		printf("\nGirdiginiz ID ile eslesen Ogretim Uyesi Bulunamadý...\n");
		fclose(fp);
		return;
	}
	fclose(fp);
	fp=fopen("course.txt","r");
	printf("\n-Ogretim Uyesinin Verdigi Dersler-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
			if(cs.veren==id){
				printf("Dersin Kodu: %d Adi: %s Kredisi: %d Kontenjani: %d\n",cs.course_kod,cs.course_ad,cs.course_kredi,cs.course_kont);
			}
	}
	fclose(fp);
}
void course_students(){
	COURSE cs;
	DERS_KAYIT kyt;
	STUDENT st;
	FILE *fp,*fp1;
	int tmp=0,kod;
	fp=fopen("course.txt","r");
	printf("-Ders Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
			printf("Ders Kodu: %d	Adi: %s  Kredisi: %d Kontenjani: %d Dersi Veren Ogr.Uyesi ID'si: %d\n",cs.course_kod,cs.course_ad,cs.course_kredi,cs.course_kont,cs.veren);
	}
	rewind(fp);
	printf("Ogrencilerini Gormek Istediginiz Dersin Kodunu Giriniz: ");scanf("%d",&kod);
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
		if(kod==cs.course_kod){
				tmp=1;
		}
	}
	if(tmp==0){
		printf("\nBelittiginiz Kod ile eslesen ders bulunamadi...\n");
		fclose(fp);
		return;
	}
	fclose(fp);
	printf("\n-Dersi Alan Ogrenci Listesi-\n");
	fp=fopen("ders_kayit.txt","r");
	fp1=fopen("student.txt","r");
	while(!feof(fp)){
			fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt.id,&kyt.st_id,&kyt.ders_kod,kyt.kayit_tarih,&kyt.durum);
			if(kyt.ders_kod==kod && kyt.durum!=-1){
				while(!feof(fp1)){
					fscanf(fp1,"%d	%s %s	%d	%d\n",&st.student_no,st.student_ad,st.student_soyad,&st.ders_sayi,&st.ders_kredi);
					if(kyt.st_id==st.student_no){
						printf("\nOgrenci No: %d	Ad Soyad: %s %s \n",st.student_no,st.student_ad,st.student_soyad);
					}
				}
				rewind(fp1);
			}
	}
	fclose(fp1);
	fclose(fp);
}
void student_courses(){
	COURSE cs;
	DERS_KAYIT kyt;
	STUDENT st;
	FILE *fp,*fp1;
	int tmp=0,no;
	fp=fopen("student.txt","r");
	printf("-Ogrenci Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st.student_no,st.student_ad,st.student_soyad,&st.ders_sayi,&st.ders_kredi);
			printf("\nOgrenci No: %d	Ad Soyad: %s %s \n",st.student_no,st.student_ad,st.student_soyad);
	}
	rewind(fp);
	printf("Derslerini Gormek Istediginiz Ogrencinin Numarasini Giriniz: ");scanf("%d",&no);
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%d	%d\n",&st.student_no,st.student_ad,st.student_soyad,&st.ders_sayi,&st.ders_kredi);
			if(no==st.student_no){
				tmp=1;
			}
	}
	if(tmp==0){
		printf("\nBelittiginiz Numara ile eslesen ogrenci bulunamadi...\n");
		fclose(fp);
		return;
	}
	fclose(fp);
	printf("\n-Ogrencinin Ders Listesi-\n");
	fp=fopen("ders_kayit.txt","r");
	fp1=fopen("course.txt","r");
	while(!feof(fp)){
			fscanf(fp,"%d)	%d - %d	%s - %d\n",&kyt.id,&kyt.st_id,&kyt.ders_kod,kyt.kayit_tarih,&kyt.durum);
			if(kyt.st_id==no && kyt.durum!=-1){
				while(!feof(fp1)){
					fscanf(fp1,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
					if(kyt.ders_kod==cs.course_kod){
						printf("\nDers Kodu: %d	Adi: %s  Kredisi: %d Kontenjani: %d\n",cs.course_kod,cs.course_ad,cs.course_kredi,cs.course_kont);
					}
				}
				rewind(fp1);
			}
	}
	fclose(fp1);
	fclose(fp);
}
void teacher_students(){
	TEACHER tc;
	COURSE cs;
	DERS_KAYIT kyt;
	STUDENT st;
	FILE *fp,*fp1,*fp2,*fp3;
	int id,tmp=0,kod;
	char isim[20];
	fp=fopen("teacher.txt","r");
	printf("-Ogretim Uyesi Listesi-\n\n");
	while(!feof(fp)){
			fscanf(fp,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
			printf("ID: %d	Ad Soyad: %s %s Unvan: %s\n",tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
	}
	rewind(fp);
	printf("\nOgrencilerini Gormek Istediginiz Ogretim Uyesinin ID'sini Giriniz: ");scanf("%d",&id);
	while(!feof(fp)){
		fscanf(fp,"%d	%s %s	%s\n",&tc.teacher_id,tc.teacher_ad,tc.teacher_soyad,tc.teacher_unvan);
		if(id==tc.teacher_id){
			tmp=1;
		}
	}
	if(tmp==0){
		printf("\nBelittiginiz ID ile eslesen ogretim gorevlisi bulunamadi...\n");
		fclose(fp);
		return;
	}
	fclose(fp);
	tmp=0;
	fp=fopen("course.txt","r");
	printf("\n-Ogretim Uyesinin Verdigi Dersler-\n\n");
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
		if(cs.veren==id){
			printf("Dersin Kodu: %d Adi: %s Kredisi: %d Kontenjani: %d\n",cs.course_kod,cs.course_ad,cs.course_kredi,cs.course_kont);
		}
	}
	printf("\nOgrencilerini Gormek Istediginiz Ogretim Uyesinin Verdiði Dersin Kodunu Giriniz: ");scanf("%d",&kod);
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
		if(kod==cs.course_kod){
			tmp=1;
		}
	}
	if(tmp==0){
		printf("\nBelittiginiz Kod ile eslesen ders bulunamadi...\n");
		fclose(fp);
		return;
	}
	fclose(fp);
	sprintf(isim, "%d", kod);
	strcat(isim,"_SINIFLISTESI.txt");
	fp=fopen("course.txt","r");
	fp1=fopen("ders_kayit.txt","r");
	fp2=fopen("student.txt","r");
	fp3=fopen(isim,"w");
	while(!feof(fp)){
		fscanf(fp,"%d	%s	%d	%d - %d\n",&cs.course_kod,cs.course_ad,&cs.course_kredi,&cs.course_kont,&cs.veren);
		if(kod==cs.course_kod && id==cs.veren){
			rewind(fp1);
			while(!feof(fp1)){
				fscanf(fp1,"%d)	%d - %d	%s - %d\n",&kyt.id,&kyt.st_id,&kyt.ders_kod,kyt.kayit_tarih,&kyt.durum);
				if(kyt.ders_kod==cs.course_kod && kyt.durum!=-1){
					rewind(fp2);
					while(!feof(fp2)){
						fscanf(fp2,"%d	%s %s	%d	%d\n",&st.student_no,st.student_ad,st.student_soyad,&st.ders_sayi,&st.ders_kredi);
						if(kyt.st_id==st.student_no){
							fprintf(fp3,"%d %s	-	%d %s %s\n",cs.course_kod,cs.course_ad,st.student_no,st.student_ad,st.student_soyad);
						}
					}
				}
			}
		}
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	printf("\nSinif Listesi Dosyasi Olusturulmustur...\n");
}
int main(){
	setlocale(LC_ALL,"Turkish");
	int max_ders=6,max_kredi=40,tmp=1,cursor;
	FILE *fp;
	printf("Ogrencilerin Alabileceði Maksimum Ders Sayýsýný Giriniz: ");scanf("%d",&max_ders);
	printf("Ogrencilerin Alabileceði Maksimum Kredi Sayýsýný Giriniz: ");scanf("%d",&max_kredi);
	system("cls");
	fp=fopen("teacher.txt","r");
	if(!fp){
		printf("Dosya Açýlamadý");
		return 0;
	}
	fclose(fp);
	fp=fopen("student.txt","r");
	if(!fp){
		printf("Dosya Açýlamadý");
		return 0;
	}
	fclose(fp);
	fp=fopen("course.txt","r");
	if(!fp){
		printf("Dosya Açýlamadý");
		return 0;
	}
	fclose(fp);
	fp=fopen("ders_kayit.txt","r");
	if(!fp){
		printf("Dosya Açýlamadý");
		return 0;
	}
	fclose(fp);
	char secim,secim2;
	while(tmp==1){
		printf("\n\t\t\t\t\t**********HOSGELDINIZ**********\n\n\t\t\t\t\t------DERS KAYIT SISTEMI------\n\n");
		printf("\n\t\t\t\t1) Ogrenci Ekle/Sil/Guncelleme Islemleri\n");
		printf("\n\t\t\t\t2) Ogretim Uyesi Ekle/Sil/Guncelleme Islemleri\n");
		printf("\n\t\t\t\t3) Ders Ekle/Sil/Guncelleme Islemleri\n");
		printf("\n\t\t\t\t4) Derse Kayit/Kayit Silme/Kayit Guncelleme Islemleri\n");
		printf("\n\t\t\t\t5) ID'si Verilen Ogretim Uyesinin Dersleri\n");
		printf("\n\t\t\t\t6) Kodu Verilen Dersin Ogrencileri\n");
		printf("\n\t\t\t\t7) Numarasi Verilen Ogrencinin Aldigi Dersler\n");
		printf("\n\t\t\t\t8) ID'si Verilen Ogretim Uyesinin Bir Dersini Alan Ogrenciler\n");
		printf("\n\t\t\t\t0) ÇIKIÞ\n");
		secim=getch();
		switch(secim){
			case '1':
				system("cls");
				printf("\n\t\t\t\t\t-----Ogrenci Ýslemleri-----\n\n");
				printf("\n\t\t\t\t1)Ogrenci Ekle\n");
				printf("\n\t\t\t\t2)Ogrenci Sil\n");
				printf("\n\t\t\t\t3)Ogrenci Bilgi Güncelle\n");
				secim2=getch();
				switch(secim2){
					case '1':
						system("cls");
						ekle_student();
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
					case '2':
						system("cls");
						fp=fopen("student.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tOgrenci Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
						sil_student();
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						}
						break;
					case '3':
						system("cls");
						fp=fopen("student.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tOgrenci Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							gunc_student();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					default:
						system("cls");
						printf("\n\t\t\t\t\tHatalý Giriþ Yaptýnýz...\n");
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
				}
				break;
			case '2':
				system("cls");
				printf("\n\t\t\t\t\t-----Ogretim Uyesi Ýslemleri-----\n\n");
				printf("\n\t\t\t\t1)Ogretim Uyesi Ekle\n");
				printf("\n\t\t\t\t2)Ogretim Uyesi Sil\n");
				printf("\n\t\t\t\t3)Ogretim Uyesi Bilgi Güncelle\n");
				secim2=getch();
				switch(secim2){
					case '1':
						system("cls");
						ekle_teacher();
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
					case '2':
						system("cls");
						fp=fopen("teacher.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tOgretim Uyesi Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							sil_teacher();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					case '3':
						system("cls");
						fp=fopen("teacher.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tOgretim Uyesi Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							gunc_teacher();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					default:
						system("cls");
						printf("\n\t\t\t\t\tHatalý Giriþ Yaptýnýz...\n");
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
				}
				break;
			case '3':
				system("cls");
				printf("\n\t\t\t\t\t-----Ders Ýslemleri-----\n\n");
				printf("\n\t\t\t\t1)Ders Ekle\n");
				printf("\n\t\t\t\t2)Ders Sil\n");
				printf("\n\t\t\t\t3)Ders Bilgi Güncelle\n");
				secim2=getch();
				switch(secim2){
					case '1':
						system("cls");
						ekle_course();
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
					case '2':
						system("cls");
						fp=fopen("course.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tDers Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							sil_course();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					case '3':
						system("cls");
						fp=fopen("course.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tDers Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							gunc_course();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					default:
						system("cls");
						printf("\n\t\t\t\t\tHatalý Giriþ Yaptýnýz...\n");
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
				}
				break;
			case '4':
				system("cls");
				printf("\n\t\t\t\t\t-----Ders Kayýt Ýslemleri-----\n\n");
				printf("\n\t\t\t\t1)Ders Kayýt\n");
				printf("\n\t\t\t\t2)Ders Kayýt Sil\n");
				printf("\n\t\t\t\t3)Ders Kayýt Güncelle\n");
				secim2=getch();
				switch(secim2){
					case '1':
						system("cls");
						derskayit(max_kredi,max_ders);
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
					case '2':
						system("cls");
						fp=fopen("ders_kayit.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tDers Kaydý Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							sil_derskayit();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					case '3':
						system("cls");
						fp=fopen("ders_kayit.txt","r");
						fseek(fp,0,SEEK_END);
						cursor=ftell(fp);
						fclose(fp);
						if(cursor==0){
							printf("\n\t\t\t\t\tDers Kaydý Dosyanýz Boþ\n");
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						else{
							gunc_derskayit();
							printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
							getch();
							system("cls");
						}
						break;
					default:
						system("cls");
						printf("\n\t\t\t\t\tHatalý Giriþ Yaptýnýz...\n");
						printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
						getch();
						system("cls");
						break;
				}
				break;
			case '5':
				system("cls");
				printf("\n\t\t\t\t\t-ID'si Verilen Ogretim Uyesinin Dersleri-\n");
				fp=fopen("teacher.txt","r");
				fseek(fp,0,SEEK_END);
				cursor=ftell(fp);
				fclose(fp);
				if(cursor==0){
					printf("\n\t\t\t\t\tOgretim Uyesi Dosyanýz Boþ\n");
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				else{
					teacher_courses();
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				break;
			case '6':
				system("cls");
				printf("\n\t\t\t\t\t-Kodu Verilen Dersin Ogrencileri-\n");
				fp=fopen("course.txt","r");
				fseek(fp,0,SEEK_END);
				cursor=ftell(fp);
				fclose(fp);
				if(cursor==0){
					printf("\n\t\t\t\t\tDers Dosyanýz Boþ\n");
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				else{
					course_students();
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				break;
			case '7':
				system("cls");
				printf("\n\t\t\t\t\t-Numarasi Verilen Ogrencinin Aldigi Dersler-\n");
				fp=fopen("student.txt","r");
				fseek(fp,0,SEEK_END);
				cursor=ftell(fp);
				fclose(fp);
				if(cursor==0){
					printf("\n\t\t\t\t\tOgrenci Dosyanýz Boþ\n");
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				else{
					student_courses();
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				break;
			case '8':
				system("cls");
				printf("\n\t\t\t\t\t-ID'si Verilen Ogretim Uyesinin Bir Dersini Alan Ogrenciler-\n");
				fp=fopen("teacher.txt","r");
				fseek(fp,0,SEEK_END);
				cursor=ftell(fp);
				fclose(fp);
				if(cursor==0){
					printf("\n\t\t\t\t\tOgretim Uyesi Dosyanýz Boþ\n");
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				else{
					teacher_students();
					printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
					getch();
					system("cls");
				}
				break;
			case '0':
				system("cls");
				printf("\n\t\t\t\t\tÇIKIÞ YAPILIYOR...\n");
				tmp=0;
				break;
			default:
				system("cls");
				printf("\n\t\t\t\t\tHatalý Giriþ Yaptýnýz...\n");
				printf("\n\t\t\t\t\tMenüye Dönmek Ýçin Bir Tuþa Basýnýz...\n");
				getch();
				system("cls");
				break;
		}
	}
	return 0;
}
