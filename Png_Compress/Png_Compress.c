//18011092 Arda Kasikci
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct pgm {
 	char type[5];
    int n;
    int m;
    int max;
	int** data;
}PGM;
typedef struct Node{
	int renk;
	int adet;
	struct Node *next;
	struct Node *prev;
}NODE;
NODE *head;
NODE* createnode(int renk,int adet){
	NODE *p;
	p=(NODE*)calloc(1,sizeof(NODE));
	if(p==NULL){
		printf("Yer Yok.\n");
		exit(0);
	}
	p->adet=adet;
	p->renk=renk;
	p->next=NULL;
	p->prev=NULL;
	return p;
}
void insertAtEnd(NODE *p){
	if(head==NULL){
		head=p;
	}else{
		NODE *tmp;
		for(tmp=head;tmp->next!=NULL;tmp=tmp->next){}
		tmp->next=p;
		p->prev=tmp;
	}
}
int readPgm(PGM* p){
	FILE *fp;
	int i,j;
	fp=fopen("input.pgm","r");
	if(!fp){
		printf("'input.pgm' isimli dosya bulunmuyor.\n");
        return 0;
	}
	fscanf(fp,"%s\n",p->type);
	fscanf(fp,"%d %d\n",&p->m,&p->n);
	fscanf(fp,"%d\n",&p->max);
	p->data=(int**)malloc((p->n)*sizeof(int*));
	if(p->data == NULL) {
		printf("Can not allocate memory for the array...\n");
		return 0;
	}
	for(i=0;i<(p->n);i++){
		p->data[i]=(int*)malloc((p->m)*sizeof(int));
	}
	for(i=0;i<(p->n);i++){
		for(j=0;j<(p->m);j++){
			if(j!=(p->m)-1){
				fscanf(fp,"%d ",&p->data[i][j]);
			}else{
				fscanf(fp,"%d",&p->data[i][j]);
			}
		}
		fscanf(fp,"\n");
	}
	fclose(fp);
	return 1;
}
void CompressPgm(PGM *p){
	int i,j;
	FILE *fp=fopen("test_encoded.txt","w");
	if(!fp){
		printf("Dosya olusturulamadi.\n");
        return;
	}
	fprintf(fp,"%d %d",p->n,p->m);
	printf("Encoded:\n");
	printf("%d %d",p->n,p->m);
	int tmp=p->data[0][0],count=0;//Ýlk kontrol için ilk elemaný tmpye attým.
	for(i=0;i<p->n;i++){
		for(j=0;j<p->m;j++){
			if(tmp==p->data[i][j]){
				count++;
			}else{
				fprintf(fp," %d %d",count,tmp);//Kendisinden farklý ilk renk kodu geldiðinde adedini ve renk kodunu dosyaya yazdým.
				printf(" %d %d",count,tmp);
				tmp=p->data[i][j];//Yeni gelen renk kodunu kaydedip countunu 1 yaptým.
				count=1;
			}
		}
	}
	fprintf(fp," %d %d",count,tmp);// Son eleman geldiðinde for döngüsü bittiðinden dolayý son elemaný ayrýca yazdýrdým.
	printf(" %d %d\n",count,tmp);
	fclose(fp);
}
int Compress_Control(FILE* fp){
	int n,m,count=0;
	int adet,renk,pre_color=-1;
	fscanf(fp,"%d %d",&n,&m);
	while(!feof(fp)){
		fscanf(fp," %d %d",&adet,&renk);
		count+=adet;
		if(renk<0 || renk>255){
			printf("Hatali renk kodu tespit edildi.\n");
			return 0;
		}
		if(pre_color==renk){
			printf("Ardisik renk kodu tespit edildi.\n");
			return 0;
		}
		pre_color=renk;
	}
	if(count==(n*m)){
		return 1;
	}
	else{
		printf("Fazla renk tespit edildi.\n");
		return 0;
	}
}
void deCompressPgm(PGM *p){
	FILE *fp=fopen("test_encoded.txt","r");
	if(!fp){
		printf("Dosya bulunamadi.\n");
        return;
	}
 	int flag=Compress_Control(fp);
 	if(!flag){
 		fclose(fp);
 		return;
	}
	rewind(fp);
	int i=0,j=0,k,n,m,adet,renk;
	fscanf(fp,"%d %d",&n,&m);
	FILE* fp1=fopen("test_decoded.pgm","w");
		if(!fp1){
		printf("Dosya olusturulamadi.\n");
        return;
	}
	fprintf(fp1,"%s\n",p->type);
	fprintf(fp1,"%d %d\n",m,n);
	fprintf(fp1,"%d\n",p->max);
	
	while(!feof(fp)){
		fscanf(fp," %d %d",&adet,&renk);
		k=0;
		while(k<adet){
			if(j<m-1){
				fprintf(fp1,"%d ",renk);
				j++;
			}else{
				fprintf(fp1,"%d",renk);
				fprintf(fp1,"\n");
				i++;j=0;
			}
		k++;
		}
	}
 	fclose(fp);
	fclose(fp1);
}

void hist(PGM* p){
	FILE *fp=fopen("test_encoded.txt","r");
	if(!fp){
		printf("Dosya bulunamadi.\n");
        return;
	}
	int a,b;
	fscanf(fp,"%d %d",&a,&b);
	int n=p->max+1,adet,renk,i;
	int* histogram=(int*)calloc(n,sizeof(int));
	while(!feof(fp)){
		fscanf(fp," %d %d",&adet,&renk);
		histogram[renk]+=adet;
	}
	for(i=0;i<n;i++){
		if(histogram[i]!=0){
			printf("Renk Kodu: %d Kullanim Adedi: %d\n",i,histogram[i]);
		}
	}
	fclose(fp);
}

void changeColor(PGM* p){
	NODE *tmp,*sil;
	if(head==NULL){
		FILE *fp=fopen("test_encoded.txt","r");
		if(!fp){
			printf("Dosya bulunamadi.\n");
	        return;
		}
		int adet,renk,n,m;
		fscanf(fp,"%d %d",&n,&m);
		while(!feof(fp)){
			fscanf(fp," %d %d",&adet,&renk);
			tmp=createnode(renk,adet);
			insertAtEnd(tmp);
		}
		fclose(fp);
	}
	int source,change,kontrol=0;;
	printf("Degistirelecek renk kodu:\n");scanf("%d",&source);
	if(source>p->max){
		printf("Hatalý renk kodu girildi. Bu renk kodu bulunmuyor.\n");
		return;
	}
	printf("Yeni renk kodu (0-255) \n");scanf("%d",&change);
	if(change<0 || change>255){
		printf("Hatalý renk kodu girildi.\n");
		return;
	}
	for(tmp=head;tmp!=NULL;tmp=tmp->next){//Encode edilmiþ görüntü içeriðini double linked liste alarak iþlem yaptým.
		if(tmp->renk==source){
			kontrol=1;
			tmp->renk=change;
			if(tmp->prev!=NULL && tmp->prev->renk==change){//Renk degistikten sonra onceki renk koduyla ayný mý kontrolu
				tmp->adet+=tmp->prev->adet;
				if(tmp->prev!=head){
					sil=tmp->prev;
					tmp->prev=tmp->prev->prev;
					tmp->prev->next=tmp;
				}else{
					sil=tmp->prev;
					tmp->prev=NULL;
					head=tmp;
				}
				free(sil);
			}
			if(tmp->next!=NULL && tmp->next->renk==change){//Renk degistikten sonra sonraki renk koduyla ayný mý kontrolu
				tmp->adet+=tmp->next->adet;
				sil=tmp->next;
				tmp->next=tmp->next->next;
				if(tmp->next!=NULL){
					tmp->next->prev=tmp;
				}
				free(sil);
			}
		}
	}
	if(kontrol && change>p->max){
		p->max=change;
	}
	if(!kontrol){
		printf("Giris yaptiginiz renk kodu dosyada bulunamadi.\n");
		return;
	}
	FILE* fp=fopen("test_encoded.txt","w");
	if(!fp){
		printf("Dosya olusturulamadi.\n");
        return;
	}
	fprintf(fp,"%d %d",p->n,p->m);
	printf("Renk Degisiminden Sonra Encoded:\n");
	printf("%d %d",p->n,p->m);
	for(tmp=head;tmp!=NULL;tmp=tmp->next){
		fprintf(fp," %d %d",tmp->adet,tmp->renk);
		printf(" %d %d",tmp->adet,tmp->renk);
	}
	fclose(fp);
}

void coordinateColor(PGM* p){
	
	NODE *tmp,*pre=NULL,*nxt=NULL,*cur,*sil;
	if(head==NULL){
		FILE *fp=fopen("test_encoded.txt","r");
		if(!fp){
			printf("Dosya bulunamadi.\n");
	        return;
		}
		int adet,renk,n,m;
		fscanf(fp,"%d %d",&n,&m);
		while(!feof(fp)){
			fscanf(fp," %d %d",&adet,&renk);
			tmp=createnode(renk,adet);
			insertAtEnd(tmp);
		}
	fclose(fp);
	}
	int yer,satir,sutun,change;
	printf("Degistirmek istediginiz rengin kordinatlarini giriniz.(Ilk satir ve sutun indexi '0'dir)\n");
	printf("Satir numarasi: ");scanf("%d",&satir);
	if(satir<0 || satir>=p->n){
		printf("Yanlis kordinat girisi yapildi.\n");
		return;
	}
	printf("Sutun numarasi: ");scanf("%d",&sutun);
	if(sutun<0 || sutun>=p->m){
		printf("Yanlis kordinat girisi yapildi.\n");
		return;
	}
	printf("Yeni renk kodu (0-255): ");scanf("%d",&change);
	if(change<0 || change>255){
		printf("Hatalý renk kodu girildi.\n");
		return;
	}
	yer=(satir*p->m)+(sutun+1);
	tmp=head;
	while(tmp!=NULL && yer>tmp->adet){
		yer-=tmp->adet;
		tmp=tmp->next;
	}
	if(change==tmp->renk){
		printf("Girdiginiz renk koduyla koordinatlardaki renk kodu zaten ayni.\n");
		return;
	}
	if(change>p->max){
		p->max=change;
	}
	
	//Bulunan nodu 3 parçaya böldüm.Kordinatýn adedin ortasýndan gelme ihtimaline karþýlýk.
	cur=createnode(change,1);
	if(yer-1!=0){
		pre=createnode(tmp->renk,(yer-1));
	}
	if(tmp->adet-yer!=0){
		nxt=createnode(tmp->renk,(tmp->adet-yer));
	}
	if(pre!=NULL && nxt!=NULL){//Aradaki bir rengin kodunun degistirilmesi
		//Nodelarý birbirine baðladým.
		cur->prev=pre;pre->next=cur;
		cur->next=nxt;nxt->prev=cur;
		//Nodelarý listeye ekleyelim;
		if(tmp!=head){
			tmp->prev->next=pre;pre->prev=tmp->prev;
		}else{
			head=pre;
		}
		if(tmp->next!=NULL){
			nxt->next=tmp->next;tmp->next->prev=nxt;
		}
		free(tmp);
	}
	else if(nxt!=NULL){//bastaki bir rengin kodunun degistirilmesi
		//Nodelarý birbirine baðladým.
		cur->next=nxt;nxt->prev=cur;
		//Nodelarý listeye ekleyelim;
		nxt->next=tmp->next;tmp->next->prev=nxt;
		//Ardisik Renk kodu kontrolu
		if(tmp!=head){
			pre=tmp->prev;
			if(pre->renk!=cur->renk){
				pre->next=cur;cur->prev=pre;
			}else{
				cur->adet+=pre->adet;
				if(pre!=head){
					pre->prev->next=cur;
					cur->prev=pre->prev;
				}else{
					head=cur;
				}
				free(pre);
			}
		}else{
			head=cur;
		}
		free(tmp);
	}else if(pre!=NULL){//Sondaki bir rengin kodunun degistirilmesi
		//Nodelarý birbirine baðladým.
		cur->prev=pre;pre->next=cur;
		//Nodelarý listeye ekleyelim;
		if(tmp!=head){
			tmp->prev->next=pre;pre->prev=tmp->prev;
		}else{
			head=pre;
		}
		//Ardisik Renk Kontrolu
		nxt=tmp->next;
		if(nxt!=NULL){
			if(nxt->renk!=cur->renk){
				nxt->prev=cur;cur->next=nxt;
			}else{
				cur->adet+=nxt->adet;
				cur->next=nxt->next;
				if(nxt->next!=NULL){
					nxt->next->prev=cur;
				}
				free(nxt);
			}
		}
		free(tmp);
	}else{//Rengin tek adet olmasý ihtimali
		tmp->renk=change;
		//Ardisik Renk Kontrolu
		if(tmp->prev!=NULL && tmp->prev->renk==change){//Renk degistikten sonra onceki renk koduyla ayný mý kontrolu
			tmp->adet+=tmp->prev->adet;
			if(tmp->prev!=head){
				sil=tmp->prev;
				tmp->prev=tmp->prev->prev;
				tmp->prev->next=tmp;
			}else{
				sil=tmp->prev;
				tmp->prev=NULL;
				head=tmp;
			}
			free(sil);
		}
		if(tmp->next!=NULL && tmp->next->renk==change){//Renk degistikten sonra sonraki renk koduyla ayný mý kontrolu
			tmp->adet+=tmp->next->adet;
			sil=tmp->next;
			tmp->next=tmp->next->next;
			if(tmp->next!=NULL){
				tmp->next->prev=tmp;
			}
			free(sil);
		}
		
	}
	FILE* fp=fopen("test_encoded.txt","w");
	if(!fp){
		printf("Dosya Olusturulamadi.\n");
        return;
	}
	fprintf(fp,"%d %d",p->n,p->m);
	printf("Renk Degisiminden Sonra Encoded:\n");
	printf("%d %d",p->n,p->m);
	for(tmp=head;tmp!=NULL;tmp=tmp->next){
		fprintf(fp," %d %d",tmp->adet,tmp->renk);
		printf(" %d %d",tmp->adet,tmp->renk);
	}
	fclose(fp);
}

 int main(){
 	head=NULL;
 	PGM* pgm=(PGM*)malloc(sizeof(PGM));
 	printf("Programin calismasi icin lutfen okuyacaginiz dosyanin isminin 'input.pgm' oldugundan emin olunuz aksi halde kod calismaz\n");
 	printf("						Gecmek icin enter'a basiniz													 \n");
 	getch();
 	if(!readPgm(pgm)){
 		return 0;
	}
	printf("						Dosya okundu.\n");
	system("cls");
	CompressPgm(pgm);printf("\n");
	int cikis=0;
	char secim;
	while(!cikis){
		printf("\n*********************Dosya Islemleri******************\n");
		printf("                     1)Decode Islemi                  \n");
		printf("                     2)Renk Degisimi                  \n");
		printf("                     3)Piksel Degisimi                \n");
		printf("                     4)Histogram                      \n");
		printf("                     0)Cikis                          \n");
		printf("******************************************************\n");
		secim=getch();
		switch(secim){
			case '1':
				deCompressPgm(pgm);
				printf("Decode islemi gerceklesti.\n");
				break;
			case '2':
				changeColor(pgm);
				break;
			case '3':
				coordinateColor(pgm);
				break;
			case '4':
				hist(pgm);
				break;
			case '0':
				cikis=1;
				break;
			default:
				printf("Hatali giris yapildi.Tekrar deneyiniz.\n\n");
				break;
		}
	}
 	return 0;
 }
