//#include "api.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define MAX 8192
#define mod 10000
// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.

int n_mails, n_queries;



int c2i(char c);
//int hash(const char* s, int len_s);
int hash(char *input, int N);
typedef struct DisjointSet{
    int parent;
    int rank;
    int set_num;
} disjoint_set;

typedef struct hash_chain_node{
    char name[15];//record the name
    int setnum;//record the idx store the name in ds[setnum]
    struct hash_chain_node* next;
} node;

typedef struct hash_index_list{
    int idx;
    node* next_index;
}hash_index;

typedef struct name_{
    char n1[15];
    char n2[15];
}namelist;

disjoint_set ds[10000];//2^24
bool set[10000] ;
hash_index idx[10000];
node* tail[10000]={NULL};

void make_group(char* name_a, char* name_b,hash_index *idx, node** tail);
int find_set(const char* s, hash_index *idx);
void link_set(const char *ra, const char *rb, hash_index *idx);
int number_of_group=0, largest_group_size=0;
int nnum;


void enqueue(hash_index* idx, node** tail,int v, char* str){
    if((*tail) == NULL){
        node* new_node = (node*)malloc(sizeof(node));
        new_node->next = NULL;
        new_node->setnum=v;
        memset(new_node->name,'\0',sizeof(char)*15);
        strcpy(new_node->name, str);
        idx->next_index = new_node;
        (*tail) = new_node;
    }
    else{
        node* new_node = (node*)malloc(sizeof(node));
        new_node->next = NULL;
        new_node->setnum=v;
        strcpy(new_node->name, str);
        (*tail)->next = new_node;
        (*tail) = new_node;
    }
}

void checkPtr(void *ptr, int line)
{
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }
}

void init_free(hash_index* idx){
    //for(int i=0;i<10000;i++){
        printf("%d\n", __LINE__);
         checkPtr(idx,__LINE__);
        if((idx)->next_index != NULL){
            printf("%d\n", __LINE__);
            node *ptr = (idx)->next_index;
            (idx)->next_index = NULL;
            node *ptr2;
            checkPtr(ptr,__LINE__);
            while(ptr->next != NULL){
            printf("%d\n", __LINE__);
                ptr2 = ptr->next;
            printf("%d\n", __LINE__);
            checkPtr(ptr2,__LINE__);
            printf("%d\n", __LINE__);
            checkPtr(ptr,__LINE__);
            printf("%d: ptr=%p\n", __LINE__, ptr);
                free(ptr);
            printf("%d\n", __LINE__);
                ptr=NULL;
            printf("%d\n", __LINE__);
                printf("%d\n", __LINE__);
                ptr=ptr2;
                printf("%d\n", __LINE__);
            ptr++;
            }
            printf("%d\n", __LINE__);
            free(ptr);
            ptr=NULL;
        }
    //}
}

void print_queue(hash_index* idx){
    if(idx->next_index != NULL){
        node *ptr = idx->next_index;
        while(ptr->next != NULL){
            printf("%d(%s)->",ptr->setnum,ptr->name);
            ptr=ptr->next;
        }
        printf("%d(%s)->NULL\n",ptr->setnum,ptr->name);
    }
    else{
        printf("NULL\n");
    }
}

int main(void){

    namelist nam[22];
    /*
    char str01[10]={"Clark"};char str02[10]={"Beata"};
    char str11[10]={"Olina"};char str12[10]={"Ted"};
    char str21[10]={"Cole"};char str22[10]={"Chloe"};
    char str31[10]={"Bess"};char str32[10]={"Winnie"};
    nam[0].n1={"Clark"};
    */
    strcpy(nam[0].n1, "Dennis");//6207
    strcpy(nam[0].n2, "Judith");//2383

    strcpy(nam[1].n1, "Bess");//8133
    strcpy(nam[1].n2, "Shirley");//4125

    strcpy(nam[2].n1, "Sandra");//3816**
    strcpy(nam[2].n2, "Alfred");//5405

    strcpy(nam[3].n1, "Daisy");//3816**
    strcpy(nam[3].n2, "Caroline");//4837

    strcpy(nam[4].n1, "Sue");
    strcpy(nam[4].n2, "Philomena");

    strcpy(nam[5].n1, "Tonya");
    strcpy(nam[5].n2, "Jean");

    strcpy(nam[6].n1, "Kenny");
    strcpy(nam[6].n2, "Richie");

    strcpy(nam[7].n1, "Amy");
    strcpy(nam[7].n2, "Jill");
    //OK
    strcpy(nam[8].n1, "Leonard");
    strcpy(nam[8].n2, "Pamela");

    strcpy(nam[9].n1, "Terence");
    strcpy(nam[9].n2, "Donald");

    strcpy(nam[10].n1, "Angel");
    strcpy(nam[10].n2, "Adam");

    strcpy(nam[11].n1, "Evan");
    strcpy(nam[11].n2, "Lisa");
    //OK
    strcpy(nam[12].n1, "Ignativs");
    strcpy(nam[12].n2, "Haley");

    strcpy(nam[13].n1, "Sheila");
    strcpy(nam[13].n2, "Phoebe");

    strcpy(nam[14].n1, "Carmen");
    strcpy(nam[14].n2, "Ariel");

    strcpy(nam[15].n1, "Rowan");
    strcpy(nam[15].n2, "Jacqueline");

    strcpy(nam[16].n1, "Bella");
    strcpy(nam[16].n2, "Garfield");

    strcpy(nam[17].n1, "Kate");
    strcpy(nam[17].n2, "Flta");

    strcpy(nam[18].n1, "Lynn");
    strcpy(nam[18].n2, "Edward");
//OK
    strcpy(nam[19].n1, "Henna");
    strcpy(nam[19].n2, "Wendy");

    strcpy(nam[20].n1, "Ellen");
    strcpy(nam[20].n2, "Anne");

    strcpy(nam[21].n1, "Adelaide");
    strcpy(nam[21].n2, "Hayden");
    //strcpy(nam[4].n1, "Lora");
    //strcpy(nam[4].n2, "Bess");
	//for(int i = 0; i < n_queries; i++){


            //int* subset = queries[i].data.group_analyse_data.mids;//subset of mails ID
            //int subset_num = queries[i].data.group_analyse_data.len;//num of mails in subset
            number_of_group = 0;
            largest_group_size = 0;
            int ng, lg;

            hash_index idx[10000];
            node* tail[10000]={NULL};

            for(int i=0;i<10000;i++){
                ds[i].rank=1;
                ds[i].parent=-1;
                ds[i].set_num = i;
                set[i]=0;

            }
            printf("==0==\n");
            for(int j=0;j<10000;j++){
                init_free(&idx[j]);
            }
            printf("==1==\n");
            nnum=0;
            for(int k = 0; k < 22; k++){
                //reading all the mails in subset, make group of 'from'&'to'
                make_group(nam[k].n1, nam[k].n2, idx, tail);//把2個人名分別做成set

                link_set(nam[k].n1, nam[k].n2, idx);//union 2 個人
                printf("%d %s %s\n",k,nam[k].n1,nam[k].n2);
                printf("====\n");
            }
            ng = number_of_group;
            lg = largest_group_size;
            int answer[3];
            answer[0]=ng;
            answer[1]=lg;
            printf("ng:, %d; lg: %d\n",ng,lg);

            printf("====\n");
            for(int j=0;j<10000;j++){
                init_free(idx);
            }

          printf("==2==\n");
            for(int j=0;j<10000;j++){
                print_queue(&idx[j]);
            }
            //api.answer(queries[i].id, answer, 2);
            //for(int j=0;j<10000;j++){
              //  printf("%d: ",j);
                //print_queue(&idx[6207]);
            //}
    //}
  return 0;
}

int check_name(hash_index* idx, char* na){//see if name already in idx
    if(idx->next_index != NULL){
        node *ptr = idx->next_index;
        while(ptr->next != NULL){
            int a = strcmp(na, ptr->name);
            if(a==0){
                return 1;
            }
            ptr=ptr->next;
        }
        int a = strcmp(na, ptr->name);
        if(a==0){
            return 1;
        }
    }
    return 0;


}

void make_group(char* name_a, char* name_b,hash_index *idx, node** tail){
    //  Initialize a set seperatively
    //make set a :
    int len_a = strlen(name_a);
    int i = hash(name_a, len_a);

    int j=i%10000;
    int check = check_name(idx+j, name_a);//檢查是否已經在j的格子中
    printf("i: %d, check: %d\n",i,check);
    if(check == 0){//不在裡面，做加入
        //printf("===\n");
        enqueue(idx+j, tail+j, nnum, name_a);

        print_queue(&idx[j]);
        if (!set[nnum]) {
            ds[nnum].parent = -1;
            ds[nnum].set_num = nnum;
            ds[nnum].rank= 1;
            set[nnum]=1;
        }
        nnum++;//ds在nnum的位子現在有人了，換下一格
    }

    //make set b :
    int len_b = strlen(name_b);
    int p = hash(name_b, len_b);
    //printf("p: %d\n",p);
    int k=p%10000;
    check = check_name(idx+k, name_b);//檢查是否已經在j的格子中
    printf("p: %d, check: %d\n",p,check);
    if(check == 0){//不在裡面，做加入
        enqueue(idx+k, tail+k, nnum, name_b);
        print_queue(&idx[k]);
        if (!set[nnum]) {
            ds[nnum].parent = -1;
            ds[nnum].set_num = nnum;
            ds[nnum].rank= 1;
            set[nnum]=1;
        }
        nnum++;//ds在nnum的位子現在有人了，換下一格
    }

    //printf("i:%d j:%d\n");
    //Then union name_a & name_b :

}

int c2i(char c) {
    //if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'z') return c - 'a' ;
    else if ('A' <= c && c <= 'Z') return c - 'A';
    return -1;
}

int AtoI(char x)
{
	if(x >= 'a' && x <= 'z')
		return x - 'a' + 10;
	else if (x >= 'A' && x <= 'Z')
		return x - 'A' + 10;
	else if (x >= '0' && x <= '9')
		return x - '0';
	else
		return -1;
}
/*
int hash(const char* s, int len_s) {
    int ret = 0;
    for (int i = 0; i < len_s; ++i)
        ret = (ret << 2) | c2i(s[i]);
    return ret;
}
*/
int hash(char *input, int N)
{
	unsigned long sum = 5381;
	for(int i=0; i < N; i++){
		int c = AtoI(input[i]);
		if(c < 0){
			printf("Something Wrong\n");
			return -1;
		}
		else{
			sum = ((sum << 5) + sum) + c;
		}
	}
	return sum&(MAX-1);
}


int find_set(const char* s, hash_index *idx) {
    int len = strlen(s);
    int i = hash(s, len);
    int k=i%10000;
    //找出姓名s放在ds中的哪一格i
    if((idx+k)->next_index != NULL){
        node *ptr = (idx+k)->next_index;
        while(strcmp(s, ptr->name) != 0){//找到chain中的姓名s在哪
            ptr=ptr->next;
        }
        i = ptr->setnum;
    }

    //find set algorithm
    while( ds[i].parent != -1){
        int r = i;
        i = ds[i].parent;
        if(ds[i].parent != -1){//path compression
            ds[r].parent = ds[i].parent;
        }
    }
    return i;//i is ds[i].set_num, root of s
}

void link_set(const char *ra, const char *rb, hash_index *idx) {
    //union algorithm
    int a = find_set(ra, idx), b = find_set(rb, idx);
    if(a != b){// calculate number_of_group
        if(ds[a].rank==1 && ds[b].rank==1){
            number_of_group++;
        }
        else if(ds[a].rank>1 && ds[b].rank>1){
            number_of_group--;
        }

    }
    if(a != b){//implement union
        if( ds[a].rank >= ds[b].rank ){//b->a
            ds[b].parent = a;
            ds[a].rank = ds[a].rank + ds[b].rank;
            if(ds[a].rank > largest_group_size){
                largest_group_size = ds[a].rank;
            }
        }
        else{//a->b
            ds[a].parent = b;
            ds[b].rank = ds[b].rank + ds[a].rank;
            if(ds[b].rank > largest_group_size){
                largest_group_size = ds[b].rank;
            }
        }
    }
}


