#include<stdio.h>
#include<stdlib.h>
#include<time.h>/*rand ve getch fonksiyonu için kütüphaneler*/
#include <conio.h>
#include <string.h>/* Yazýnýn Renklendirilmesi Ýçin 2 farklý kütüphane*/
#include <windows.h>
int main(){
	HANDLE  hConsole;/*Yazý Rengini Kýrmýzý yapan kod satýrý*/
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	srand(time(0));
	char zorluk;
	int n,m;
	int enyuksekpuan;/*highscore için deðiþken*/
	enyuksekpuan=0;
	bas:
	zorluk='2';
	n=17;m=8;
	printf("		******************************************************\n");
	printf("		******************************************************\n");
	printf("		* ******** ******  ******** ******     **    ******* *\n");
	printf("		*    **    **         **    *     *    **    **      *\n");
	printf("		*    **    **         **    *     *    **    **      *\n");
	printf("		*    **    *****      **    * * *      **    ******* *\n");
	printf("		*    **    **         **    *   *      **         ** *\n");
	printf("		*    **    **         **    *    *     **         ** *\n");
	printf("		*    **    ******     **    *     *    **    ******* *\n");
	printf("		******************************************************\n");
	printf("		******************************************************\n");
	printf("		********************by ARDA KASIKCI*******************\n");
	printf("\n");printf("\n");printf("\n");
	printf("		                       1-BASLA						  \n");
	printf("		                    2-ZORLUK SECIMI	                  \n");
	printf("		                       3-CIKIS						  \n");
	printf(" 	  Oyunda Kordinat Girerken Sol veya Sol Ust Noktaya Gore Islem Yapiniz. \n");
	printf("  Her satir silinme islemi 100 puan,yerlesen sekillerin kare sayisi basina 1 puan eklenir.\n");
	char menu;
	menu=getch();
	while(menu!='1'&& menu!='2' && menu!='3'){
		printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
		menu=getch();
	}
	if(menu=='3'){
		system("cls");
		goto son;}
	system("cls");
	if(menu=='2'){
	while(menu=='2'){
		printf("		******************************************************\n");
		printf("		******************************************************\n");
		printf("		* ******** ******  ******** ******     **    ******* *\n");
		printf("		*    **    **         **    *     *    **    **      *\n");
		printf("		*    **    **         **    *     *    **    **      *\n");
		printf("		*    **    *****      **    * * *      **    ******* *\n");
		printf("		*    **    **         **    *   *      **         ** *\n");
		printf("		*    **    **         **    *    *     **         ** *\n");
		printf("		*    **    ******     **    *     *    **    ******* *\n");
		printf("		******************************************************\n");
		printf("		******************************************************\n");
		printf("		********************by ARDA KASIKCI*******************\n");
		printf("\n");printf("\n");printf("\n");
		printf("		                        1-Kolay						  \n");
		printf("		                        2-Normal						  \n");
		printf("		                        3-Zor						      \n");
		zorluk=getch();
		while(zorluk!='1'&& zorluk!='2' && zorluk!='3'){
		printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
		zorluk=getch();
		}
		if(zorluk=='1'){
			n=13;m=6;}
		if(zorluk=='2'){
			n=17;m=8;}
		if(zorluk=='3'){
			n=21;m=10;}
		system("cls");
		printf("		******************************************************\n");
		printf("		******************************************************\n");
		printf("		* ******** ******  ******** ******     **    ******* *\n");
		printf("		*    **    **         **    *     *    **    **      *\n");
		printf("		*    **    **         **    *     *    **    **      *\n");
		printf("		*    **    *****      **    * * *      **    ******* *\n");
		printf("		*    **    **         **    *   *      **         ** *\n");
		printf("		*    **    **         **    *    *     **         ** *\n");
		printf("		*    **    ******     **    *     *    **    ******* *\n");
		printf("		******************************************************\n");
		printf("		******************************************************\n");
		printf("		********************by ARDA KASIKCI*******************\n");
		printf("\n");printf("\n");printf("\n");
		printf("		                       1-BASLA						  \n");
		printf("		                    2-ZORLUK SECIMI	                  \n");
		printf("		                       3-CIKIS						  \n");
		printf(" 	  Oyunda Kordinat Girerken Sol veya Sol Ust Noktaya Gore Islem Yapiniz. \n");
		menu=getch();
		while(menu!='1'&& menu!='2' && menu!='3'){
		printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
		menu=getch();
		}
		system("cls");
		if(menu=='3'){
			goto son;}
			}
		}
	int i,k,j,A[50][25],B[50][25];
	for(i=1;i<n;i++){                            /*Tetris Alanýný Oluþturdum*/
		for(j=1;j<m;j++){
			A[i][j]=0;
			B[i][j]=0;
		}
	}
	for(j=0;j<m;j++){                              /*Tetris Alanýnda 0. Satýr ve 0. Sütün Elemanlarýný Kordinat Haline Çevirdim*/
		A[0][j]=j;
		B[0][j]=j;
	}
	for(i=0;i<n;i++){
		A[i][0]=i;
		B[i][0]=i;
	}
	int sayac=0;               /*Oyunun Bitmesini Saðlayacak Sayac*/
	for(j=0;j<m;j++){
		sayac=sayac+A[1][j];
	}
	k=0;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(i>=0 && i<=9){
				if(j==0){                       /*Tetris Alanýný Yazdýrýrken Kayma Olmasýn Diye 0-9 Arasýný Bir Boþluk Býrakarak Bastým.(Kordinatlarý aldýktan sonra x+1 ve y+1 için iþlem yap!!)*/
				printf(" %d  |",A[i][j]);}
				else{
					if(i==0){
						printf(" %d  ",A[i][j]);}
					else{
					printf("[%d] ",A[i][j]);}
				}
				}
			else{
				if(j==0){
					printf(" %d |",A[i][j]);}
				else{
				printf("[%d] ",A[i][j]);}
		    }
		}printf("\n");
		if(i==0){
			if(zorluk=='2'){
			printf(" _______________________________\n");}
			if(zorluk=='3'){
			printf(" _______________________________________\n");}
			if(zorluk=='1'){
			printf(" _______________________\n");}
		}
	}
	
	int kare[2][2],dik2[2][1],yatay2[1][2],tek[1],yatay3[1][3],dik3[3][1],x,y,z[2][3];          /*Þekilleri Tanýmladým*/
	int ustz[3][2],L[3][2],solL[2][3],ustL[3][2],sagL[2][3];
	tek[0]=1;
	for(i=0;i<2;i++){
		dik2[i][0]=1;
		for(j=0;j<2;j++){
			kare[i][j]=1;
		}
	}
	for(j=0;j<2;j++){
		yatay2[0][j]=1;
	}
	for(j=0;j<3;j++){
		yatay3[0][j]=1;
	}
	for(i=0;i<3;i++){
		dik3[i][0]=1;
	}
	z[0][0]=0;z[0][1]=1;z[0][2]=1;z[1][0]=1;z[1][1]=1;z[1][2]=0;/*Þekilleri z'ye kadar tanýmladým L'nin rotate'i için birçok case olduðundan printf ile göstermeyi tercih ettim.*/
	
	int puan;/*Puanlama Sistemi için Deðiþken*/
	puan=0;
	
	while(sayac==1){
	printf("\n");
	int tmp;                      /* 8 þekil için rand fonksiyonu kullanýp farklý deðerler için farklý deðerleri aldým*/
	tmp=(rand()%8)+1;
	printf("Siradaki Sekil: \n");
	switch(tmp){
		char rotate;
		case 1: for(i=0;i<2;i++){
			        for(j=0;j<2;j++){
			        	printf("[%d]",kare[i][j]);
					}printf("\n");
		       }
		    puan=puan+4;
		    printf("\n");
		    printf("Kordinatini Giriniz:\n");
		    scanf("%d",&x);scanf("%d",&y);
		    if(x==0 || y==0){ /*Kullanýcýnýn her adýmda çýkýþ yapabilmesi için kontrol*/
		    	goto cikis;}
		    while(x>n || y>m-1){
		    	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
		    while(A[x][y]!=0 || A[x][y+1]!=0 || A[x+1][y]!=0 || A[x+1][y+1]!=0){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
			i=2;
			while(A[i][y]==0 && A[i][y+1]==0 && i<=16){        /*Her case için farklý olan ,þeklin dolu olan yerin üstüne konumlanmasýný saðlayan döngü*/
				i=i+1;}
			A[i-2][y]=1;A[i-2][y+1]=1;A[i-1][y]=1;A[i-1][y+1]=1;
			break;
		case 2: printf("[%d]\n",tek[0]);
				puan=puan+1;
		        printf("Kordinatini Giriniz:\n");
		        scanf("%d",&x);scanf("%d",&y);
		        if(x==0 || y==0){
		    	goto cikis;}
		        while(x>n-1 || y>m-1){
		    	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				while(A[x][y]!=0){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				i=2;
				while(A[i][y]==0 && i<=n-1){
				i=i+1;}
		        A[i-1][y]=1;
			break;
		case 3: for(i=0;i<2;i++){
			       printf("[%d]\n",dik2[i][0]);}
			    puan=puan+2;
		    	printf("Cevirmek Istiyorsaniz 'w' , Istemiyorsaniz 's' Tusuna Basiniz:\n");/*Þekillerin çevirilmesi için rotate deðiþkenini kullandým*/
		    	rotate=getch();
		    	while(rotate!='w'&& rotate!='s'){
				printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
				rotate=getch();}
		    	if(rotate=='w'){
					printf("Siradaki Sekil: \n");
		    		for(j=0;j<2;j++){
		        	printf("[%d]",yatay2[0][j]);
	        		}printf("\n");
	        		printf("Kordinatini Giriniz:\n");
		       		scanf("%d",&x);scanf("%d",&y);
		       		if(x==0 || y==0){
		    		goto cikis;}
		       		while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x][y+1]!=0){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && A[i][y+1]==0 && i<=n-1){
					i=i+1;}
		        	A[i-1][y]=1;A[i-1][y+1]=1;
					}
				else{
		        printf("Kordinatini Giriniz:\n");
		        scanf("%d",&x);scanf("%d",&y);
		        if(x==0 || y==0){
		    	goto cikis;}
		        while(x>n-1 || y>m-1){
		    	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				while(A[x][y]!=0 || A[x+1][y]!=0){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				i=2;
				while(A[i][y]==0 && i<=n-1){
					i=i+1;}
		        A[i-2][y]=1;A[i-1][y]=1;}
			break;
		case 4:for(j=0;j<2;j++){
		          printf("[%d]",yatay2[0][j]);
	           	}printf("\n");
	           	puan=puan+2;
	           	printf("Cevirmek Istiyorsaniz 'w' , Istemiyorsaniz 's' Tusuna Basiniz:\n");
		    	rotate=getch();
		    	while(rotate!='w'&& rotate!='s'){
				printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
				rotate=getch();}
		    	if(rotate=='w'){
					printf("Siradaki Sekil: \n");
					for(i=0;i<2;i++){
			       	printf("[%d]\n",dik2[i][0]);}
					printf("Kordinatini Giriniz:\n");
		        	scanf("%d",&x);scanf("%d",&y);
		        	if(x==0 || y==0){
		    		goto cikis;}
		        	while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x+1][y]!=0){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && i<=n-1){
					i=i+1;}
		        	A[i-2][y]=1;A[i-1][y]=1;
				}
				else{
	            printf("Kordinatini Giriniz:\n");
		        scanf("%d",&x);scanf("%d",&y);
		        if(x==0 || y==0){
		    	goto cikis;}
		       	while(x>n-1 || y>m-1){
		    	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				while(A[x][y]!=0 || A[x][y+1]!=0){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				i=2;
				while(A[i][y]==0 && A[i][y+1]==0 && i<=n-1){
					i=i+1;}
		        A[i-1][y]=1;A[i-1][y+1]=1;}
			break;
		case 5:for(j=0;j<3;j++){
		          printf("[%d]",yatay3[0][j]);
	           	}printf("\n");
	           	puan=puan+3;
	           	printf("Cevirmek Istiyorsaniz 'w' , Istemiyorsaniz 's' Tusuna Basiniz:\n");
		    	rotate=getch();
		    	while(rotate!='w'&& rotate!='s'){
				printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
				rotate=getch();}
		    	if(rotate=='w'){
					printf("Siradaki Sekil: \n");
					for(i=0;i<3;i++){
		        	printf("[%d]\n",dik3[i][0]);}
	            	printf("Kordinatini Giriniz:\n");
		        	scanf("%d",&x);scanf("%d",&y);
		        	if(x==0 || y==0){
		    		goto cikis;}
		        	while(x>n-1 || y>m-1){
		        	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
			    	while(A[x][y]!=0 || A[x+1][y]!=0 || A[x+2][y]!=0){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && i<=n-1){
						i=i+1;}
		       		A[i-3][y]=1;A[i-2][y]=1;A[i-1][y]=1;}
	            else{
	            printf("Kordinatini Giriniz:\n");
		        scanf("%d",&x);scanf("%d",&y);
		        if(x==0 || y==0){
		    	goto cikis;}
		       	while(x>n-1 || y>m-1){
		    	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				while(A[x][y]!=0 || A[x][y+1]!=0 || A[x][y+2]!=0){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				i=2;
				while(A[i][y]==0 && A[i][y+1]==0 && A[i][y+2]==0 && i<=n-1){
					i=i+1;}
		        A[i-1][y]=1;A[i-1][y+1]=1;A[i-1][y+2]=1;}
		        printf("\n");
			break;
		case 6:for(i=0;i<3;i++){
		        printf("[%d]\n",dik3[i][0]);}
		        puan=puan+3;
				printf("Cevirmek Istiyorsaniz 'w' , Istemiyorsaniz 's' Tusuna Basiniz:\n");
		    	rotate=getch();
		    	while(rotate!='w'&& rotate!='s'){
				printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
				rotate=getch();}
		    	if(rotate=='w'){
					printf("Siradaki Sekil: \n");
					for(j=0;j<3;j++){
		         	printf("[%d]",yatay3[0][j]);
	           		}printf("\n");
					printf("Kordinatini Giriniz:\n");
		       		scanf("%d",&x);scanf("%d",&y);
		       		if(x==0 || y==0){
		    		goto cikis;}
		       		while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x][y+1]!=0 || A[x][y+2]!=0){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && A[i][y+1]==0 && A[i][y+2]==0 && i<=n-1){
						i=i+1;}
		        	A[i-1][y]=1;A[i-1][y+1]=1;A[i-1][y+2]=1;}
				else{
	            printf("Kordinatini Giriniz:\n");
		        scanf("%d",&x);scanf("%d",&y);
		        if(x==0 || y==0){
		    	goto cikis;}
		        while(x>n-1 || y>m-1){
		        printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
			    while(A[x][y]!=0 || A[x+1][y]!=0 || A[x+2][y]!=0){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				i=2;
				while(A[i][y]==0 && i<=n-1){
					i=i+1;}
		        A[i-3][y]=1;A[i-2][y]=1;A[i-1][y]=1;}
			break;
		case 7:for(i=0;i<2;i++){
				for(j=0;j<3;j++){					
				if(i==0 && j==0|| i==1 && j==2){
					printf("   ");}
					else{
					printf("[%d]",z[i][j]);}
				}printf("\n");}
				puan=puan+4;
				printf("Cevirmek Istiyorsaniz 'w' , Istemiyorsaniz 's' Tusuna Basiniz:\n");
		    	rotate=getch();
		    	while(rotate!='w'&& rotate!='s'){
				printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
				rotate=getch();}
		    	if(rotate=='w'){
					printf("Siradaki Sekil: \n");
					printf("[1]  \n");
					printf("[1][1]\n");
					printf("   [1]\n");
					printf("Kordinatini Giriniz:\n");
		       		scanf("%d",&x);scanf("%d",&y);
		       		if(x==0 || y==0){
		    		goto cikis;}
					while(x>n-1 || y>m-1){
		        	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x+1][y]!=0 || A[x+1][y+1]!=0 || A[x+2][y+1]!=0 ){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && A[i+1][y+1]==0 && i<=n-1){
						i=i+1;}
					A[i][y+1]=1;A[i-1][y+1]=1;A[i-1][y]=1;A[i-2][y]=1;
					}
				else{
				printf("Kordinatini Giriniz:\n");
		        scanf("%d",&x);scanf("%d",&y);
		        if(x==0 || y==0){
		    	goto cikis;}
		        while(x>n-1 || y>m-1){
		    	printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				while(A[x][y]!=0 || A[x][y+1]!=0 || A[x+1][y]!=0 || A[x+1][y-1]!=0 ){
				printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
				scanf("%d",&x);scanf("%d",&y);}
				i=2;
				while(A[i][y]==0 && A[i][y-1]==0 && A[i-1][y+1]==0 && i<=n-1){
					i=i+1;}
				A[i-2][y]=1;A[i-2][y+1]=1;A[i-1][y-1]=1;A[i-1][y]=1;}
			break;
		case 8: printf("[1]\n");
				printf("[1]\n");
				printf("[1][1]\n");
				puan=puan+4;
				printf("180 Derece Cevirmek Icin 'w',90 Derece Sola Cevirmek Icin 'a',Saga Cevirmek Icin 'd',Cevirmek Istemiyorsaniz 's' Tusuna Basiniz:\n");
		    	rotate=getch();
		    	while(rotate!='w'&& rotate!='a' && rotate!='s' && rotate!='d'){
				printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
				rotate=getch();}
		    	switch(rotate){
		    		case 'w':
					printf("Siradaki Sekil: \n");
					printf("[1][1]\n");printf("   [1]\n");printf("   [1]\n");
					printf("Kordinatini Giriniz:\n");
		        	scanf("%d",&x);scanf("%d",&y);
		        	if(x==0 || y==0){
		    		goto cikis;}
		        	while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
		    		while(A[x][y]!=0 || A[x][y+1]!=0 || A[x+1][y+1]!=0 || A[x+2][y+1]!=0 ){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=3;
					while(A[i][y+1]==0 && A[i-2][y]==0 && i<=n-1){
					i=i+1;}
					A[i-1][y+1]=1;A[i-2][y+1]=1;A[i-3][y+1]=1;A[i-3][y]=1;
					break ;
					case 'a':
					printf("Siradaki Sekil: \n");
					printf("[1][1][1]\n");printf("[1]\n");
					printf("Kordinatini Giriniz:\n");
					scanf("%d",&x);scanf("%d",&y);
					if(x==0 || y==0){
		    		goto cikis;}
		        	while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x+1][y]!=0 || A[x][y+1]!=0 || A[x][y+2]!=0 ){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && A[i-1][y+1]==0 && A[i-1][y+2]==0 && i<=n-1){
					i=i+1;}
					A[i-1][y]=1;A[i-2][y]=1;A[i-2][y+1]=1;A[i-2][y+2]=1;
					break ;
					case 'd':
					printf("Siradaki Sekil: \n");
					printf("      [1]\n");printf("[1][1][1]\n");
					printf("Kordinatini Giriniz:\n");
					scanf("%d",&x);scanf("%d",&y);
					if(x==0 || y==0){
		    		goto cikis;}
		        	while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x][y+1]!=0 || A[x][y+2]!=0 ){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && A[i][y+1]==0 && A[i][y+2]==0 && i<=n-1){
					i=i+1;}
					A[i-1][y]=1;A[i-1][y+1]=1;A[i-1][y+2]=1;A[i-2][y+2]=1;
					break ;
					case 's':
					printf("Kordinatini Giriniz:\n");
		        	scanf("%d",&x);scanf("%d",&y);
		        	if(x==0 || y==0){
		    		goto cikis;}
		        	while(x>n-1 || y>m-1){
		    		printf("Kordinat Yanlis. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					while(A[x][y]!=0 || A[x+1][y]!=0 || A[x+2][y]!=0 || A[x+2][y+1]!=0 ){
					printf("Kordinat Dolu. \nTekrar Kordinat Giriniz: \n");
					scanf("%d",&x);scanf("%d",&y);}
					i=2;
					while(A[i][y]==0 && A[i][y+1]==0 && i<=n-1){
						i=i+1;}
					A[i-1][y]=1;A[i-1][y+1]=1;A[i-2][y]=1;A[i-3][y]=1;
					break ;
			break;}
	   }
	    int satirsilme,k; /*Satýr silinmesi için kullandýðým döngü*/
	    for(i=2;i<n;i++){
	    	satirsilme=0;
	    	for(j=1;j<m;j++){
	    		satirsilme=satirsilme+A[i][j];}
			if(satirsilme==m-1){
				puan=puan+100;
				printf("%d. SATIR SILINDI.\n",i);
				for(k=i;k>0;k--){
					for(j=1;j<m;j++){
						if(k==1){
							A[k][j]=0;
						}
						else{
						A[k][j]=A[k-1][j];
					    }
					}
					
				}
			}
		}
		Sleep(1000);
		system("cls");
		k=0;
		printf("	  Onceki Hali\n\n");/*Game boardýn önceki halini göstericek matris*/
		for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(i>=0 && i<=9){
				if(j==0){
				printf(" %d  |",B[i][j]);}
				else{
					if(i==0){
						printf(" %d  ",B[i][j]);}
					else{
					printf("[%d] ",B[i][j]);}
				}
				}
			else{
				if(j==0){
					printf(" %d |",B[i][j]);}
				else{
				printf("[%d] ",B[i][j]);}
		    }
		}printf("\n");
		if(i==0){
			if(zorluk=='2'){
			printf(" _______________________________\n");}
			if(zorluk=='3'){
			printf(" _______________________________________\n");}
			if(zorluk=='1'){
			printf(" _______________________\n");}
		}
		}printf("	  Son Hali\n\n");
		for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(i>=0 && i<=9){
				if(j==0){
				printf(" %d  |",A[i][j]);}
				else{
					if(i==0){
						printf(" %d  ",A[i][j]);}
					else{
					printf("[%d] ",A[i][j]);}
				}
				}
			else{
				if(j==0){
					printf(" %d |",A[i][j]);}
				else{
				printf("[%d] ",A[i][j]);}
		    }
		}printf("\n");
		if(i==0){
			if(zorluk=='2'){
			printf(" _______________________________\n");}
			if(zorluk=='3'){
			printf(" _______________________________________\n");}
			if(zorluk=='1'){
			printf(" _______________________\n");}
		}
	}
	for(i=1;i<n;i++){
		for(j=1;j<m;j++){
			B[i][j]=A[i][j];
		}
		
	}
	printf("Puaniniz: %d 		En Yuksek Puaniniz: %d\n",puan,enyuksekpuan);
	printf("Cikmak Icin x=0,y=0 Giriniz.\n");
	for(j=1;j<m;j++){
		sayac=sayac+A[1][j];
		}
    }
    if(puan>enyuksekpuan){
    	enyuksekpuan=puan;
	}
    printf("OYUN SONU PUANINIZ: %d \n",puan);
    printf("	  GAME OVER			\n");printf("\n");printf("\n");
    cikis:
    printf("TEKRAR OYNAMAK ICIN 1'E CIKMAK ICIN 0'A BASINIZ.\n");
    char tekrar;
    tekrar=getch();
    while(tekrar!='1'&& tekrar!='0'){
	printf("Yanlis Giris Yaptiniz Lutfen Tekrar Giriniz.\n");
	tekrar=getch();
	}
    if(tekrar=='1'){
    	system("cls");
    	goto bas;
	}
	else{
		goto son;
	}
    son:
    system("cls");
    printf("GULE GULE TEKRAR GEL :)");
return 0;
}
