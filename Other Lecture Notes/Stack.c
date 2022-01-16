#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define SIZE 50
typedef struct Node{
	char name[SIZE];
	struct Node *parent;
	struct Node *firstchild;
	struct Node *nextsibling;
}NODE;
NODE* createNode(char name[]){
	NODE *q=(NODE *)malloc(sizeof(NODE));
	strcpy(q->name,name);
	q->parent=NULL;
	q->firstchild=NULL;
	q->nextsibling=NULL;
	return q;
}
void mkdir(NODE *current,char name[]){
	if(current->firstchild==NULL){
		NODE *q=createNode(name);
		current->firstchild=q;
		q->parent=current;
		return;
		
	}else{
		NODE *tmp=current->firstchild;
		NODE *prev;
		while(tmp!=NULL && strcmp(tmp->name,name)!=0){
			prev=tmp;
			tmp=tmp->nextsibling;
		}
		if(tmp==NULL){
			NODE *q=createNode(name);
			strcpy(q->name,name);
			q->parent=current;
			prev->nextsibling=q;
			return;
		}else{
			printf("Ayni isimde directory zaten var islem gerceklestirilemiyor.\n");
			return;
		}
	}
}
NODE* chdir(NODE *current,char name[]){
	if(strcmp("..",name)==0){
		if(current->parent==NULL){
			printf("Ust kutuphane bulunamiyor.\n");
		}else{
			current=current->parent;
		}
	}else{
		NODE *tmp=current->firstchild;
		while(tmp!=NULL && strcmp(tmp->name,name)!=0){
			tmp=tmp->nextsibling;
		}
		if(tmp==NULL){
			printf("Bu isimde bir kutuphane bulunamadi.\n");
		}else{
			current=tmp;
		}
	}
	return current;	
}
void rmdir(NODE *current,char name[]){
	NODE *tmp=current->firstchild;
	NODE *prev=NULL;
	while(tmp!=NULL && strcmp(tmp->name,name)!=0){
		prev=tmp;
		tmp=tmp->nextsibling;
	}
	if(tmp==NULL){
		printf("Bu isimde bir kutuphane bulunamadi.\n");
		return;
	}else{
		if(tmp->firstchild==NULL){
			if(current->firstchild==tmp){
					current->firstchild=tmp->nextsibling;
					free(tmp);
					return;
			}else{
				prev->nextsibling=tmp->nextsibling;
				free(tmp);
				return;
			}
		}
		else{
			printf("Silme islemi gerceklesmedi.Kutuphane bos degil.\n");
			return;
			}
	}	
}
void dir(NODE *current){
	NODE *tmp=current->firstchild;
	if(tmp==NULL){
		printf("Alt kutuphane yok.\n");
	}else{
		while(tmp!=NULL){
			puts(tmp->name);
			tmp=tmp->nextsibling;
		}
	}
}
void count(NODE *current){
	NODE *tmp=current->firstchild;
	int count=0;
	while(tmp!=NULL){
		count++;
		tmp=tmp->nextsibling;
	}
	printf("%d\n",count);
}
int main(){
	NODE *root=createNode("root");
	NODE *current=root;
	int cikis=0,n,i,j;
	char input[SIZE],komut[10],name[SIZE];
	printf("----------Directory---------------------------------------------------\n");
	printf("    Cikis icin 0 tuslayiniz  \n");
	printf("Komutu yazip bir bosluk birakip istediginiz karakter dizisini giriniz.\n");
	printf("----------------------------------------------------------------------\n");
	printf("----------Komutlar----------------------------------------------------\n");
	printf(">mkdir >chdir >rmdir >dir >count\n");
	printf("--------------------------------\n");
	while(cikis==0){
		printf(">");gets(input);
		if(!strcmp(input,"0")){
			cikis++;
		}
		else{
			i=0;
			n=strlen(input);
			while(i<n && input[i]!=' '){
				komut[i]=input[i];
				i++;
			}
			komut[i]='\0';
			if(i==n && strcmp(komut,"dir")!=0 && strcmp(komut,"count")!=0){
				printf("Hatali kodlama lutfen tekrar deneyiniz.\n");
			}
			else{
				i++;
				j=0;
				while(i<=n){
					name[j]=input[i];
					i++;j++;
				}
				if(!strcmp(komut,"mkdir")){
					mkdir(current,name);
				}else if(!strcmp(komut,"chdir")){
					current=chdir(current,name);
				}else if(!strcmp(komut,"rmdir")){
					rmdir(current,name);
				}else if(!strcmp(komut,"dir")){
					dir(current);
				}else if(!strcmp(komut,"count")){
					count(current);
				}else{
					printf("Hatali kodlama lutfen tekrar deneyiniz.\n");
				}
				
			}
		}
	}
	return 0;
}
