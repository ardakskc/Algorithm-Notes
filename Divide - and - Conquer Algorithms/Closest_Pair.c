//ARDA KASIKCI 18011092
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct coordinate {// Kordinatlar icin bir struct tanimladim.
 	int x;
 	int y;
}CRD;


CRD* readCoordinate(char filename[]){//Dosyadan kordinatlari okuyan fonksiyon
	FILE *fp;
	int i=0;
	fp=fopen(filename,"r");
	if(!fp){
		printf("'%s' isimli dosya bulunmuyor.\n",filename);
        return;
	}
	
	CRD *coordinate=(CRD *)malloc(10*sizeof(CRD));//Size örnek dosyada 10 adetti
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d %d\n",&coordinate[i].x,&coordinate[i].y);//Dosyadan okuma yapip struct dizisini return ediyorum.
		i++;
	}
	fclose(fp);
	return coordinate;
	
}


float mesafe(CRD a,CRD b){ //Ýki koordinat arasindaki mesafeyi bulan fonksiyon
	float sonuc= sqrt(((a.x-b.x)*(a.x-b.x))+((a.y-b.y)*(a.y-b.y)));
	return sonuc;
}


float medyanBul(CRD* A,int l,int r){//Sinirlari verilen dizinin medyanini bulma
	int n=r-l+1;
	int orta=n/2;//Dizinin orta elemani
	float medyan;
	if(n%2==0){
		medyan=(A[l+orta].x+A[l+orta-1].x)/2.0;//Çift sayida eleman var ise medyan orta iki sayinin ortalamasidir.
	}else{
		medyan=A[l+orta].x;
	}
	return medyan;
}


float MinMesafe(CRD *A,int left,int right,CRD* min1,CRD* min2){//Kordinat dizisini sol elemani ve sag elemani alir.Minimum mesafeli kordinatlarý kaydetmesi icin min1 min2
	int i,j;
	int n=(right-left+1);//Eleman sayisi
	float tmp,min=9999;// Minimum degeri tutucak degisken
	if(n>=2 && n<=3){//Dosyda belirtilen uzere eleman sayisi az ise brute force uyguladim.Recursive fonksiyonun stop conditionu.
		for(i=left;i<right;i++){
			for(j=i+1;j<=right;j++){ //Elemanlarin her biri arasindaki mesafenin en kucugunu hesaplar.
				tmp=mesafe(A[i],A[j]);
				if(min>tmp){
					min=tmp;
					min1->x=A[i].x;min1->y=A[i].y;
					min2->x=A[j].x;min2->y=A[j].y;
				}
			}
		}
		return min;
	}
	else if(n>3){//	Rekürsif cagirma kismi
		float minSol,minSag;//Bolunen parcalardan donen min degerleri icin
		int orta=left+n/2;//Medyanin indisi icin
		
		//Fonksiyon medyanin solu ve sagi icin kendini tekrar cagirir.
		//Soldan ve sagdan gelen minimum mesafeli koordinatlarýn adresleri icin degiskenler olusturdum.
		CRD minSol1,minSol2;
		minSol=MinMesafe(A,left,orta,&minSol1,&minSol2);
		CRD minSag1,minSag2;
		minSag=MinMesafe(A,orta+1,right,&minSag1,&minSag2);
		
		//Donen degerler arasýndan en kucugu alinir.
		if(minSol<minSag){
			min=minSol;
			min1->x=minSol1.x;min1->y=minSol1.y;
			min2->x=minSol2.x;min2->y=minSol2.y;
		}else{
			min=minSag;
			min1->x=minSag1.x;min1->y=minSag1.y;
			min2->x=minSag2.x;min2->y=minSag2.y;
		}
		
		//Bu kisimda medyana yakin olan noktalar(sagindakiler ve solundakiler) belirlenir ve aralarindaki mesafe hesaplanir.
		float medyan=medyanBul(A,left,right);
		CRD* B=(CRD*)malloc(6*sizeof(CRD));//Medyana yakýn olan noktalarý tutacak dizi
		j=0;
		for(i=left;i<=right;i++){
			if(abs(A[i].x-medyan)<min){
				B[j]=A[i];
				j++;
			}
		}
		
		CRD minMedyan1,minMedyan2;//Medyandan gelenen minimum uzaklýklý noktalarýn deðerleri.
		tmp=MinMesafe(B,0,j-1,&minMedyan1,&minMedyan2);// Medyana yakin degerler icin mesafe bulur.
		if(min>tmp){
			min=tmp;
			min1->x=minMedyan1.x;min1->y=minMedyan1.y;
			min2->x=minMedyan2.x;min2->y=minMedyan2.y;
		}
		return min;
	}
}


void merges(CRD* A,int p,int q,int r){
	int i,j,k=0;
    int nleft = q - p + 1;//Sol dizinin eleman sayisi
    int nright = r - q;// Sag dizinin eleman sayisi

    CRD L[nleft], R[nright];

    for (i = 0; i < nleft; i++)
        L[i] = A[p + i]; //Sol diziyi doldurma
    for (j = 0; j < nright; j++)
        R[j] = A[q + 1 + j];// Sag diziyi doldurma
    
    i = 0;
    j = 0;
    k = p;

    while (i < nleft && j < nright) {//Klasik merge islemi
        if (L[i].x <= R[j].x) {
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
void mergeSort(CRD* A,int p,int r){
	if(p<r){//Sirasiz dizide en ufak parcaya kadar gider. Ardýndan sirali sekilde merge eder.
		int q=p+(r-p)/2;
		mergeSort(A,p,q);//Diziyi ortadan bolerek Sol ve sag icin ayni islemi tekrarlar.
		mergeSort(A,q+1,r);
		merges(A,p,q,r);//Bolunen parcalari sýrali sekilde birlestirir.
	}
}


int main(){
	char filename[20]="sample.txt";
	int i,size=10;
	CRD min1,min2;//Birbirine en yakin iki koordinatin degerlerini almak icin kullanilacak.
	CRD* coordinates=readCoordinate(filename);
	mergeSort(coordinates,0,size-1);
	printf("---KOORDINATLAR---\n");
	for(i=0;i<10;i++){
		printf("      %d %d\n",coordinates[i].x,coordinates[i].y);
	}
	printf("---Medyan Degeri---\n");
	printf("      %.2f\n",medyanBul(coordinates,0,size-1));
	printf("---Minimum Mesafe---\n");
	printf("      %.2f\n",MinMesafe(coordinates,0,size-1,&min1,&min2));
	printf("---Min Mesafeli Koordinatlar---\n");
	printf("     1-(%d , %d )\n",min1.x,min1.y);
	printf("     2-(%d , %d )\n",min2.x,min2.y);
	
	return 0;
}
