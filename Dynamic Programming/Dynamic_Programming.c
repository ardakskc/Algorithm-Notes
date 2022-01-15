//ARDA KASIKCI 18011092
#include<stdio.h>
#include<stdlib.h>
typedef struct reklam{
	int no;
	int StartTime;
	int Duration;
	int Value;
}REKLAM;

REKLAM* readReklam(char filename[], int n){//Dosyadan okuyan fonksiyon
	FILE *fp;
	int i=0;
	fp=fopen(filename,"r");
	if(!fp){
		printf("'%s' isimli dosya bulunmuyor.\n",filename);
        return;
	}
	REKLAM *reklamlar = (REKLAM *)malloc(n*sizeof(REKLAM));//Sizin attiginiz ornek dosyada 7 adetti
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d %d %d\n",&reklamlar[i].StartTime,&reklamlar[i].Duration,&reklamlar[i].Value);//Dosyadan okuma yapip struct dizisini return ediyorum.
		reklamlar[i].no=i+1;
		i++;
	}
	fclose(fp);
	return reklamlar;
}

void merges(REKLAM* A,int p,int q,int r){
	int i,j,k=0;
    int nleft = q - p + 1;//Sol dizinin eleman sayisi
    int nright = r - q;// Sag dizinin eleman sayisi

    REKLAM L[nleft], R[nright];

    for (i = 0; i < nleft; i++)
        L[i] = A[p + i]; //Sol diziyi doldurma
    for (j = 0; j < nright; j++)
        R[j] = A[q + 1 + j];// Sag diziyi doldurma
    
    i = 0;
    j = 0;
    k = p;

    while (i < nleft && j < nright) {//Klasik merge islemi
        if ((L[i].StartTime+L[i].Duration)<= (R[j].StartTime+R[j].Duration)) {//Bitis zamanina gore karsilastirma yaptim.
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < nleft) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < nright) {
        A[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(REKLAM* A,int p,int r){
	if(p<r){//Sirasiz dizide en ufak parcaya kadar gider. Ardýndan sirali sekilde merge eder.
		int q=p+(r-p)/2;
		mergeSort(A,p,q);//Diziyi ortadan bolerek Sol ve sag icin ayni islemi tekrarlar.
		mergeSort(A,q+1,r);
		merges(A,p,q,r);//Bolunen parcalari sýrali sekilde birlestirir.
	}
}

void max_profit(REKLAM* reklamlar,int n){
	int i,j,tmp,stop=0,toplam_val,matris[n+1][5];
	
	int label[n+1];//Bu dizi re-construction isleminde degerin nereden geldigini bulmak icin kullanilmistir.Label 0 ise eski profit & 1 ise yeni profit hesaplanmistir.
	
	for(i=0;i<5;i++){//ILK SATIR 0'LANIR.
		matris[0][i]=0;
	}
	label[0]=1;
	
	for(i=1;i<n+1;i++){
		matris[i][0]=reklamlar[i-1].no;//MATRIS 0.KOLON REKLAM NO
		matris[i][1]=reklamlar[i-1].StartTime;// MATRIS 1. KOLON START TIME
		matris[i][2]=reklamlar[i-1].Duration;// MATRIS 2. KOLON DURATION
		matris[i][3]=reklamlar[i-1].Value;//MATRIS 3. KOLON VALUE
		j=i-1;							  //MATRIS 4.KOLON PROFIT
		stop=0;
		
		while(j>0 && stop==0){//Çakismayan son satirin indisini bulur.
		
			tmp=matris[j][1]+matris[j][2];//Bitis Zamani hesabi
			
			if(matris[i][1]>=tmp){ //Start time ile Son cakismayan reklamýn bitis saatiyle karsilastirma
				stop=1;//Bulunduysa stop flagi kullanilir.
			}else{
				j--;//Bulunmadiysa aramaya devam edilir.
			}
		}
		
		toplam_val=matris[j][4]+matris[i][3];//Son cakismayan satirin profitiyle, yeni satirin value degeri toplanir.
		if(toplam_val>matris[i-1][4]){//Yeni profit eskisinden buyuk mu?
			matris[i][4]=toplam_val;
			label[i]=1;
		}
		else{
			matris[i][4]=matris[i-1][4];//Degilse eski profit gecerli.
			label[i]=0;
		}
		
	}
	printf("\nEn Yuksek Kazanc: %d\n",matris[n][4]);
	int profit=matris[n][4];//Max profit
	i=n;
	printf("En Yuksek Kazanci Verenler: ");
	while(i>0 && profit>0 ){//Re-Construction-Backward
		if(label[i]==1 && profit==matris[i][4]){//Eger profit hesabinda bu satir kullanilmissa ve profit degerleri esit ise
			profit=profit-matris[i][3];//Profitten satir value'su cikarilir.
			printf("%d ",matris[i][0]);//Satirin numarasi yazdirilir.
		}
		i--;//Ýslem profit 0lanana kadar devam eder.
	}
}
int main(){
	int i,n=7,start,val,dur;
	char filename[20]="sample.txt";
	REKLAM* reklamlar=readReklam(filename,n);
	
	
	printf("-Ilk Hali-\n");
	for(i=0;i<n;i++){//Matrisin ilk hali
		printf("%d  %d  %d  %d\n",i+1,reklamlar[i].StartTime,reklamlar[i].Duration,reklamlar[i].Value);
	}
	mergeSort(reklamlar,0,n-1);//Bitis zamanina gore siralama
	printf("\n");
	printf("-Siralanmis Hali-\n");
	for(i=0;i<n;i++){//Siralandiktan sonraki
		printf("%d  %d  %d  %d\n",i+1,reklamlar[i].StartTime,reklamlar[i].Duration,reklamlar[i].Value);
	}
	
	
	max_profit(reklamlar,n);//Profit hesabini yapan fonksiyon
	return 0;
}
