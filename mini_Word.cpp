#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 1
#define OK 0
const int WORD_LENGTH = 25000;//���嵥��������󳤶�
typedef int status;

/*
 **����洢���ʼ�����ִ����Ľṹ��
 */
typedef struct Node{
    char word[WORD_LENGTH];
    int time;
    struct Node *next;
}wordNode;

wordNode *headNode = NULL;//��������ͷָ��

/*
 **��������
 */
wordNode *wordSearch(char *word,int *num);
status wordCount(char *word,int *num);

void Print(int* num);
void mergeSort(wordNode **head);
void FrontBackSplit(wordNode *head,wordNode **pre,wordNode **next);
void wordJob(char word[]);
wordNode *SortedMerge(wordNode *pre,wordNode *next);
void release();

/*����1���*/ 
void Read(char* s){
	puts(s); 
}


 //���ַ���q����s��n���λ��.  
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

/*����2����*/ 
void Copy(char* s){
	int j,k,n;
	//jΪ������ʼλ�ã�0Ϊ��һλ����kΪ�ַ�����
	printf("�����븴����ʼλ�ã����ֱ�ʾ��0Ϊ��һλ����\n");
	scanf("%d",&j);
	printf("�����븴��λ����\n");
	scanf("%d",&k);	
	char dest[2000]={""};
	strncpy(dest,s+j,k);
	int len=strlen(dest);
	dest[len-1]='\0';
	


	int tar=0; 

	while(tar==0){
		printf("������ճ��λ�ã�\n");
		scanf("%d",&n);
		Insert(s,dest,n); 
		puts(s);
		printf("�Ƿ����ճ����0��������1�����ټ���\n");
		scanf("%d",&tar);
	}
 
}

/*����3�ƶ�*/ 
void Move(char *s){
	int j,k,n,i; 
	printf("�������ƶ���ʼλ�ã����ֱ�ʾ��0Ϊ��һλ����\n");
	scanf("%d",&j);
	printf("�������ƶ�λ����\n");
	scanf("%d",&k);	
	char dest[2000]={""};
	strncpy(dest,s+j,k);
	printf("�������ƶ�����λ�ã�\n");
	scanf("%d",&n);
	Insert(s,dest,n); 
	for(i=j+k-1;i<strlen(s)-1;i++){
		s[i-k]=s[i];
	}
	s[strlen(s)-k]='\0';
	puts(s);
}

/*����4�滻*/ 
void Replace(char *str){
	char oldstr[50];
	char newstr[50];
	printf("������Ҫ�滻���ı���\n");
	fflush(stdin);
	gets(oldstr);
	printf("�������滻Ϊ���ı���\n");
	fflush(stdin);
	gets(newstr);
	char bstr[strlen(str)];//ת��������
    memset(bstr,0,sizeof(bstr));
 
    for(int i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){//����Ŀ���ַ���
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
        	strncat(bstr,str + i,1);//����һ�ֽڽ�������
	    }
    }
 
    strcpy(str,bstr);
	puts(str);	
}


/*
 **���ҵ������ڽ��
 */
wordNode *wordSearch(char *word,int *num){
    wordNode *node;//����һ���½��
    
    if(headNode == NULL){//��ͷ���Ϊ��
        node = (wordNode*)malloc(sizeof(wordNode));
        strcpy(node->word, word);//����һ�����ʸ�ֵ������½��
        node->time = 0;//��ʼ���õ��ʵĳ��ִ���
        *num+=1;
        headNode = node;//��ͷ���ָ������½��
        return node;
        
    }
    
    wordNode *nextNode = headNode;
    wordNode *preNode = NULL;
    
    while(nextNode != NULL && strcmp(nextNode->word, word) != 0){
        preNode = nextNode;
        nextNode = nextNode->next;
    }
    
    //���õ��ʲ����ڣ����������������½��
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
 **��Ƶͳ��
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
 **��ӡ��Ƶ��ߵ�10����
 */



/*
 **�Դ�Ƶͳ�ƽ�����й鲢����
 */
void mergeSort(wordNode **headnode){
    wordNode *pre,*next,*head;
    head = *headnode;
    
    //��������Ϊ0��1��ֹͣ����
    if(head == NULL || head->next == NULL){
        return;
    }
    
    FrontBackSplit(head,&pre,&next);
    
    mergeSort(&pre);
    mergeSort(&next);
    
    *headnode = SortedMerge(pre,next);
    
}


/*
 **��������з���
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
 **��������������ͷ���
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
 **�����д��ĸ�������ַ�
 */
void wordJob(char word[]){
    int i,k;
    const char *specialChar = ",.;:'?!><+=|*&^%$#@\"";//���������ַ���
    
    for(i = 0;i<strlen(word);i++){
        //ɸѡ�����ַ����еĴ�д��ĸת��ΪСд��ĸ
        if(word[i]>='A'&& word[i]<='Z'){
            word[i] += 32;
        }
        //ɸѡ��ȥ���ַ����е������ַ�
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
 **�ͷ����н���ڴ�
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
        printf("���ļ�������!");
        
    }else{
        wordNode *preNode = headNode;
        printf("�ܴ��� %d \n",*num);
        int i = 0;
        printf("���ִ�������5��������: \n");
        
        while (preNode != NULL && i<5) {
            printf("%s ���ִ��� %d\n",preNode->word,preNode->time);
            preNode = preNode->next;
            i++;

        }
        
    release();    
    }
}

/*����5��Ƶͳ��*/
void Count(char *s){
	FILE *fp = fopen("result.txt", "w+");
	
	fprintf(fp,"%s",s);
	fclose(fp);
	
	char temp[WORD_LENGTH];//����������ʱ��ŵ��ʵ�����
    FILE *file;
    int count,articleWordNum = 0;//����ͳ�ƽ������ı���
    int *num = &articleWordNum,choose;
    
    /*
     **��ȡ�ļ�
     */
    if((file = fopen("result.txt", "r")) == NULL){
        printf("�ļ���ȡʧ��!");
        exit(1);
    }
    
    while((fscanf(file,"%s",temp))!= EOF){
        wordJob(temp);
        count = wordCount(temp,num);
    }
    
    fclose(file);//�ر��ļ�
    

    mergeSort(&headNode);
    Print(num);
 

}

/*����ѡ��*/ 
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
    p = fopen("paper.txt", "r");  //��ȡpaper.txt
    while((ch=fgetc(p))!=EOF){
		s[i]=ch;
		i++;
	}//��txt�ļ������ַ���s 
    fclose(p);
	
	int target=0;
	int n;
	printf("��ӭʹ�ø�ϵͳ��\n");

	while(target==0){
		printf("��ѡ������ʹ�õĹ���(�������ּ���):\n1.read\n2.copy\n3.move\n4.replace\n5.count\n");
		scanf("%d",&n);
		FunctionChoose(n,s);//����ѡ�� 
		printf("�������˳���0��������1���˳�\n");
		scanf("%d",&target);
	} 
	return 0;
}
 
