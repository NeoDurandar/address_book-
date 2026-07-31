#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Alist{
	char name[50];//柔性数组只能有一个且必须放在结构体最后，所以这两个数组必须指定大小 
	char phone[50];
	struct Alist *prev;
	struct Alist *next;
}Alist;

Alist* load_list(const char* filename);

Alist* find_nth(Alist *L,int nth){
	if(nth<0){
		printf("error");
		return NULL;
	}
	Alist *p=L->next;
	int cnt=0;
	for(p=L->next;p!=NULL&&cnt<nth;p=p->next){
		cnt++;
	}
	return p;
}

bool insert(Alist *L,int add_point,char name[],char phone[]){
	Alist *added=find_nth(L,add_point-1);
	Alist *add=malloc(sizeof(Alist));
	
	if(add==NULL||added==NULL){
		return false;
	}
	
	strcpy(add->name,name);//字符串只能这样输入赋值 
	strcpy(add->phone,phone);
	
	add->next=added->next;
	add->prev=added;
	if(added->next!=NULL){
		added->next->prev=add;
	}
	added->next=add;
	
	return true;
}

bool censore_fun(Alist *L,int censored_point){
	Alist *censored=find_nth(L,censored_point);
	Alist *censore=find_nth(L,censored_point-1);
	
	if(censore==NULL||censored==NULL){
		return false;
	}
	
	Alist *temp=censored;
	
	censore->next=censored->next;
	if(censored->next!=NULL){
		censored->next->prev=censore;
	}
	free(temp);
	return true;
}

Alist *find_name(Alist *L,char name[]){
	Alist *find=L->next;
	for(find=L->next;find!=NULL;find=find->next){
		if(strcmp(find->name,name)==0){
			return find;
		}
	}
	return NULL;
}

bool update(Alist *L,char ori_name[],char new_name[],char new_phone[]){
	Alist *u=L->next;
	for(u=L->next;u!=NULL;u=u->next){
		if(strcmp(u->name,ori_name)==0){
			strcpy(u->name,new_name);
			strcpy(u->phone,new_phone);
			return true;
		}
	}
	return false;
}

int main(){
	Alist* L=load_list ("通讯录.bin");
	if (L == NULL) {
		L = malloc(sizeof(Alist));
		L->next = NULL;
	}
	Alist *tail=L;
	
	int cnt=0;
	int n=0;
	printf("how many people you wanna record:");
	scanf("%d",&n);
	
	for(cnt=0;cnt<n;cnt++){
		Alist *s=malloc(sizeof(Alist));
		printf("please tell the name:");
		scanf("%s",s->name);
		printf("please tell the phone number:");
		scanf("%s",s->phone);
		
		s->next=tail->next;
		s->prev=tail;
		tail->next=s;
		tail=s;
	}
	
	int choice;
	do{
		printf("1.浏览\n");
		printf("2.添加\n");
		printf("3.删除（按位序）\n");
		printf("4.修改（按名字）\n");
		printf("0.保存\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:{
				Alist *p=L->next;
				for(p=L->next;p!=NULL;p=p->next){
				printf("%s\n",p->name);
				printf("%s\n",p->phone);
			}
				break;
			}
			
			printf("\n");
			
			case 2:{
				int ist_point=0;
				printf("where to insert:");
				scanf("%d",&ist_point);
				char ist_name[20];
				printf("the name is:");
				scanf("%s",ist_name);
				char ist_phone[15];
				printf("the phone number is:");
				scanf("%s",ist_phone);
				insert(L,ist_point,ist_name,ist_phone);
				break;
			}
			
			printf("\n");
			
			case 3:{
				int cen=0;
				printf("which node you wanna delate:");
				scanf("%d",&cen);
				censore_fun(L,cen);
				break;
			}
			
			printf("\n");
			
			case 4:{
				char ori[20];
				printf("who to update:");
				scanf("%s",ori);
				char newn[20];
				printf("the new name:");
				scanf("%s",newn);
				char newp[15];
				printf("the new phone:");
				scanf("%s",newp);
				update(L,ori,newn,newp);
				break;
			}
			
			printf("\n");
			
			case 0:{
				FILE *txl=fopen("通讯录.bin","wb");
				if(txl==NULL){
					printf("error");
					return -1;
				}
				Alist *p3=L->next;
				for(p3=L->next;p3!=NULL;p3=p3->next){
					fwrite(p3->name/*指向数据的指针*/,sizeof(char)/*每个数据大小*/,50/*每次写入多少个字节*/,txl/*写到哪里去*/);//sizeof里面的东西要和重加载程序里的 fread 对齐，所以不要用这里的结构体定义！！！ 
					fwrite(p3->phone,sizeof(char),50,txl);
				}
				fclose(txl);
				printf("Alist saved");
				break;
			}
		}
	}while(choice!=0);
	return 0;
}
