//Arda Kasikci 18011092
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
typedef struct node{
	char kelime[MAX];
	int count;
	struct node *next;
}NODE;
typedef struct graph{
	int numVertices;
	NODE **adjLists;
}GRAPH;
NODE* createNode(char k[],int adet){
	NODE* tmp=malloc(sizeof(NODE));
	strcpy(tmp->kelime,k);
	tmp->count=adet;
	tmp->next=NULL;
	return tmp;
}
GRAPH* createGraph(int vertices){
	GRAPH* graph=malloc(sizeof(GRAPH));
	graph->numVertices=vertices;
	graph->adjLists=malloc(vertices*sizeof(NODE*));
	int i;
	for(i=0;i<vertices;i++){
		graph->adjLists[i]=NULL;
	}
	return graph;
}
int searchindex(GRAPH* graph, char k[]){
	int i;
	for(i=0;i<graph->numVertices;i++){
		NODE* tmp=graph->adjLists[i];
		if(!strcmp(tmp->kelime,k)){
			return i;
		}
	}
	return -1;
}
void addEdge(GRAPH* graph,int src,int dest){
	NODE* source=createNode(graph->adjLists[src]->kelime,graph->adjLists[src]->count);
	NODE* destination=createNode(graph->adjLists[dest]->kelime,graph->adjLists[dest]->count);
	
	destination->next=graph->adjLists[src]->next;
	graph->adjLists[src]->next=destination;
	
	source->next=graph->adjLists[dest]->next;
	graph->adjLists[dest]->next=source;
	
}
void encokaranan3(NODE* tmp){
	NODE* tmp1=tmp,*tmp2=tmp;
	int bir=0,iki=0,uc=0,sayac=0;
	
	while(tmp1!=NULL){
		sayac++;
		tmp1=tmp1->next;
	}
	if(sayac<=3){
		while(tmp!=NULL){
			puts(tmp->kelime);
			tmp=tmp->next;
		}
	}else{
		while(tmp2!=NULL){
			if(tmp2->count>bir){
				uc=iki;
				iki=bir;
				bir=tmp2->count;
			}
			else if(tmp2->count>iki){
				uc=iki;
				iki=tmp2->count;
			}
			else if(tmp2->count>uc){
				uc=tmp2->count;
			}
			tmp2=tmp2->next;
		}
		sayac=0;
		while(tmp!=NULL && sayac<3){
			if(tmp->count==bir || tmp->count==iki || tmp->count==uc){
				puts(tmp->kelime);
				sayac++;
			}
			tmp=tmp->next;
		}
	}
}
void kelimesorgu(char k[],GRAPH* graph){
	int i=0,index;
	index=searchindex(graph,k);
	if(index!=-1){
		NODE* tmp=graph->adjLists[index];
		tmp->count++;
		tmp=tmp->next;
		encokaranan3(tmp);
	}else{
		printf("Aranan kelimeye ait veri bulunamadi.\n");
	}
}
GRAPH* mergeet(GRAPH* graph1,GRAPH* graph2){
	int i,j;
	int count=0;
	NODE* list[10];
	//ORTAK ELEMAN KONTROLU
	for(i=0;i<graph1->numVertices;i++){
		for(j=0;j<graph2->numVertices;j++){
			if(!strcmp(graph1->adjLists[i]->kelime,graph2->adjLists[j]->kelime)){
				list[count]=graph2->adjLists[j];
				count++;
			}
		}
	}
	if(count==0){
		printf("Merge Edilecek Eleman Yok.\n");
		return NULL;
	}else{
		int k=0,kontrol=0;
		int v=(graph1->numVertices+graph2->numVertices)-count;
		GRAPH* merged=graph1;
		merged->numVertices=v;
		for(j=0;j<graph2->numVertices;j++){
			kontrol=0;
			for(k=0;k<count;k++){
				if(!strcmp(graph2->adjLists[j]->kelime,list[k]->kelime)){
					kontrol=1;
				}
			}
			if(kontrol!=1){
				merged->adjLists[i]=graph2->adjLists[j];
				i++;
			}
		}
		return merged;
	}
}
int main(){
	int v1=4,v2=5,i,adet;
	char k[MAX],junk;
	printf("KOD VERILEN ORNEK UZERINE TASARLANMISTIR.\n\n\n");
	//------------------------------------Ýlk Graph
	printf("-----------------ILK GRAPH------------------------\n\n\n");
	GRAPH* graph1=createGraph(v1);
	for(i=0;i<v1;i++){
		printf("Kelime giriniz.\n");
		gets(k);
		printf("Sorgulanma Adedi Giriniz.\n");
		scanf("%d",&adet);scanf("%c",&junk);
		NODE* node1=createNode(k,adet);
		graph1->adjLists[i]=node1;
	}
	addEdge(graph1,0,1);
	addEdge(graph1,0,2);
	addEdge(graph1,0,3);
	printf("Kelime onerisi istediginiz kelimeyi giriniz\n");
	gets(k);printf("\n");
	printf("En cok arananan ilk 3 benzer kelimeler:\n");
	kelimesorgu(k,graph1);
	//------------------------------------- Ýkinci Graph
	printf("-----------------IKINCI GRAPH------------------------\n\n\n");
	GRAPH* graph2=createGraph(v2);
	for(i=0;i<v2;i++){
		printf("Kelime giriniz.\n");
		gets(k);
		printf("Sorgulanma Adedi Giriniz.\n");
		scanf("%d",&adet);scanf("%c",&junk);
		NODE* node1=createNode(k,adet);
		graph2->adjLists[i]=node1;
	}
	addEdge(graph2,0,1);
	addEdge(graph2,0,2);
	addEdge(graph2,0,3);
	addEdge(graph2,0,4);
	printf("Kelime onerisi istediginiz kelimeyi giriniz\n");
	gets(k);printf("\n");
	printf("En cok arananan ilk 3 benzer kelimeler:\n");
	kelimesorgu(k,graph2);
	//----------------------------------------Ýki Graphýn Merge Edilmis Hali
	printf("-----------------MERGED GRAPH------------------------\n\n\n");
	GRAPH* merged=mergeet(graph1,graph2);
	if(merged!=NULL){
		printf("Kelime onerisi istediginiz kelimeyi giriniz\n");
		gets(k);printf("\n");
		printf("En cok arananan ilk 3 benzer kelimeler:\n");
		kelimesorgu(k,merged);
	}
	return 0;
}
