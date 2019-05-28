#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 1
#define OK 0
const int WORD_LENGTH = 25000;//定义单个单词最大长度
typedef int status;

/*
 **定义存储单词及其出现次数的结构体
 */
typedef struct Node{
    char word[WORD_LENGTH];
    int time;
    struct Node *next;
}wordNode;

wordNode *headNode = NULL;//定义链表头指针

/*
 **函数声明
 */
wordNode *wordSearch(char *word,int *num);
status wordCount(char *word,int *num);

void Print(int* num);
void mergeSort(wordNode **head);
void FrontBackSplit(wordNode *head,wordNode **pre,wordNode **next);
void wordJob(char word[]);
wordNode *SortedMerge(wordNode *pre,wordNode *next);
void release();

/*功能1浏览*/ 
void Read(char* s){
	puts(s); 
}


 //将字符串q插入s的n后的位置.  
void Insert(char *s,char *q,int n)  
{
int i;
int lens=strlen(s);
int lenq=strlen(q);
for(i=lens-1;i>n-1;i--){
	s[i+lenq]=s[i];
}
for(i=0;i<lenq;i++){
	s[n+i]=q[i];
}

}

/*功能2复制*/ 
void Copy(char* s){
	int j,k,n;
	//j为复制起始位置（0为第一位），k为字符个数
	printf("请输入复制起始位置（数字表示，0为第一位）：\n");
	scanf("%d",&j);
	printf("请输入复制位数：\n");
	scanf("%d",&k);	
	char dest[2000]={""};
	strncpy(dest,s+j,k);
	int len=strlen(dest);
	dest[len-1]='\0';
	


	int tar=0; 

	while(tar==0){
		printf("请输入粘贴位置：\n");
		scanf("%d",&n);
		Insert(s,dest,n); 
		puts(s);
		printf("是否继续粘贴：0：继续，1：不再继续\n");
		scanf("%d",&tar);
	}
 
}

/*功能3移动*/ 
void Move(char *s){
	int j,k,n,i; 
	printf("请输入移动起始位置（数字表示，0为第一位）：\n");
	scanf("%d",&j);
	printf("请输入移动位数：\n");
	scanf("%d",&k);	
	char dest[2000]={""};
	strncpy(dest,s+j,k);
	printf("请输入移动到的位置：\n");
	scanf("%d",&n);
	Insert(s,dest,n); 
	for(i=j+k-1;i<strlen(s)-1;i++){
		s[i-k]=s[i];
	}
	s[strlen(s)-k]='\0';
	puts(s);
}

/*功能4替换*/ 
void Replace(char *str){
	char oldstr[50];
	char newstr[50];
	printf("请输入要替换的文本：\n");
	fflush(stdin);
	gets(oldstr);
	printf("请输入替换为的文本：\n");
	fflush(stdin);
	gets(newstr);
	char bstr[strlen(str)];//转换缓冲区
    memset(bstr,0,sizeof(bstr));
 
    for(int i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){//查找目标字符串
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
        	strncat(bstr,str + i,1);//保存一字节进缓冲区
	    }
    }
 
    strcpy(str,bstr);
	puts(str);	
}


/*
 **查找单词所在结点
 */
wordNode *wordSearch(char *word,int *num){
    wordNode *node;//声明一个新结点
    
    if(headNode == NULL){//若头结点为空
        node = (wordNode*)malloc(sizeof(wordNode));
        strcpy(node->word, word);//将第一个单词赋值给这个新结点
        node->time = 0;//初始化该单词的出现次数
        *num+=1;
        headNode = node;//将头结点指向这个新结点
        return node;
        
    }
    
    wordNode *nextNode = headNode;
    wordNode *preNode = NULL;
    
    while(nextNode != NULL && strcmp(nextNode->word, word) != 0){
        preNode = nextNode;
        nextNode = nextNode->next;
    }
    
    //若该单词不存在，则在链表中生成新结点
    if(nextNode == NULL){
        node = (wordNode*)malloc(sizeof(wordNode));
        strcpy(node->word, word);
        node->time = 0;
        node->next = headNode->next;
        headNode->next = node;
        *num+=1;
        
        return node;
    }else
        return nextNode;
    
}


/*
 **词频统计
 */
status wordCount(char *word,int *num){
    wordNode *tmpNode = NULL;
    tmpNode = wordSearch(word,num);
    
    if(tmpNode == NULL){
        return ERROR;
    }
    
    tmpNode->time++;
    
    return 0;
}





/*
 **打印词频最高的10个词
 */



/*
 **对词频统计结果进行归并排序
 */
void mergeSort(wordNode **headnode){
    wordNode *pre,*next,*head;
    head = *headnode;
    
    //若链表长度为0或1则停止排序
    if(head == NULL || head->next == NULL){
        return;
    }
    
    FrontBackSplit(head,&pre,&next);
    
    mergeSort(&pre);
    mergeSort(&next);
    
    *headnode = SortedMerge(pre,next);
    
}


/*
 **将链表进行分组
 */
void FrontBackSplit(wordNode *source,wordNode **pre,wordNode **next){
    wordNode *fast;
    wordNode *slow;
    
    if(source == NULL || source->next == NULL){
        *pre = source;
        *next = NULL;
    }else{
        slow = source;
        fast = source->next;
        
        while(fast != NULL){
            fast = fast->next;
            
            if(fast != NULL){
                slow = slow->next;
                fast = fast->next;
            }
        }
        *pre = source;
        *next = slow->next;
        slow->next = NULL;
    }
}


/*
 **根据排序结果更换头结点
 */
wordNode *SortedMerge(wordNode *pre,wordNode *next){
    wordNode *result = NULL;
    
    if(pre == NULL)
        return next;
    else if(next == NULL)
        return pre;
    
    if(pre->time >= next->time){
        result = pre;
        result->next = SortedMerge(pre->next,next);
        
    }else{
        result = next;
        result->next = SortedMerge(pre,next->next);
    }
    return result;
}


/*
 **处理大写字母及特殊字符
 */
void wordJob(char word[]){
    int i,k;
    const char *specialChar = ",.;:'?!><+=|*&^%$#@\"";//定义特殊字符集
    
    for(i = 0;i<strlen(word);i++){
        //筛选并将字符串中的大写字母转化为小写字母
        if(word[i]>='A'&& word[i]<='Z'){
            word[i] += 32;
        }
        //筛选并去除字符串中的特殊字符
        for(k = 0;k<strlen(specialChar);k++){
            
            if(word[i] == specialChar[k]){
                
                while(i<strlen(word)){
                    word[i] = word[i+1];
                    i++;
                }
               
            }
        }
    }
    
}


/*
 **释放所有结点内存
 */
void release(){
    if(headNode == NULL)
        return;
    
    wordNode *pre = headNode;
    while(pre != NULL){
        headNode = pre->next;
        free(pre);
        pre = headNode;
        
    }
}

void Print(int* num){
    if(headNode == NULL){
        printf("该文件无内容!");
        
    }else{
        wordNode *preNode = headNode;
        printf("总词量 %d \n",*num);
        int i = 0;
        printf("出现次数最多的5个词如下: \n");
        
        while (preNode != NULL && i<5) {
            printf("%s 出现次数 %d\n",preNode->word,preNode->time);
            preNode = preNode->next;
            i++;

        }
        
    release();    
    }
}

/*功能5词频统计*/
void Count(char *s){
	FILE *fp = fopen("result.txt", "w+");
	
	fprintf(fp,"%s",s);
	fclose(fp);
	
	char temp[WORD_LENGTH];//定义用以临时存放单词的数组
    FILE *file;
    int count,articleWordNum = 0;//定义统计结点个数的变量
    int *num = &articleWordNum,choose;
    
    /*
     **读取文件
     */
    if((file = fopen("result.txt", "r")) == NULL){
        printf("文件读取失败!");
        exit(1);
    }
    
    while((fscanf(file,"%s",temp))!= EOF){
        wordJob(temp);
        count = wordCount(temp,num);
    }
    
    fclose(file);//关闭文件
    

    mergeSort(&headNode);
    Print(num);
 

}

/*功能选择*/ 
void FunctionChoose(int i,char* s){
	switch(i){
		case 1:Read(s);break;
		case 2:Copy(s);break;
		case 3:Move(s);break; 
		case 4:Replace(s);break;
		case 5:Count(s);break; 
	}
	
}


int main(){
	FILE *p;
	char s[2000]; 
	int ch;
	int i=0;
    p = fopen("paper.txt", "r");  //读取paper.txt
    while((ch=fgetc(p))!=EOF){
		s[i]=ch;
		i++;
	}//将txt文件存入字符串s 
    fclose(p);
	
	int target=0;
	int n;
	printf("欢迎使用该系统！\n");

	while(target==0){
		printf("请选择你想使用的功能(输入数字即可):\n1.read\n2.copy\n3.move\n4.replace\n5.count\n");
		scanf("%d",&n);
		FunctionChoose(n,s);//功能选择 
		printf("继续或退出：0：继续，1：退出\n");
		scanf("%d",&target);
	} 
	return 0;
}
 
