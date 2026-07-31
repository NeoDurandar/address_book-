#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct load{
	char name[50];
	char phone[50];//原来的代码这里的数字填的是多少，重加载这里也得填多少！！ 
	struct load *next;
	struct load *prev;
}load;

typedef struct Alist {
	char name[50];//柔性数组只能有一个且必须放在结构体最后，所以这两个数组必须指定大小 
	char phone[50];
	struct Alist* prev;
	struct Alist* next;
}Alist;

Alist *load_list(const char*filename){
	FILE*Load=fopen("通讯录.bin","rb");
	if(Load==NULL){
		printf("error");
		return NULL;
	}
	
	load *L=malloc(sizeof(load));
	L->next=NULL;
	L->prev=NULL;
	load *tail=L;
	
	char temp_name[50];
	char temp_phone[50];
	while(fread(temp_name/*读到哪里去*/,sizeof(char)/*每个多大*/,50/*一次读几个字节，按着原代码 [] 里的填*/,Load/*从哪里读*/)>0){
		if(fread(temp_phone,sizeof(char),50,Load)<=0){
			break;
		}
		load *s=malloc(sizeof(load));
		strcpy(s->name,temp_name);
		strcpy(s->phone,temp_phone);
		s->next=tail->next;
		s->prev=tail;
		tail->next=s;
		tail=s; 
	}
	load *p=L->next;
	for(p=L->next;p!=NULL;p=p->next){
		printf("%s\n",p->name);
		printf("%s\n",p->phone);
    }
	fclose(Load);
	return L;
}
