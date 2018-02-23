/*
 * @Samaritan_infi
 */
/// 只存前40位，防止mle，注意hdu提交的时候选择c++

#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;

char c[100];
void add(char a[],char b[],char back[])//计算 a+b，结果存入 c,
{

    int i,j,k;
    int x,y,z;
    int up;
    i=strlen(a)-1;
    j=strlen(b)-1;
    k=0;
    up=0;
    while(i>=0||j>=0)
    {
        if(i<0)x=0;
        else x=a[i]-'0';
        if(j<0)y=0;
        else y=b[j]-'0';
        z=x+y+up;
        c[k++]=z%10+'0';
        up=z/10;
        i--;
        j--;
    }
    if(up>0)c[k++]=up+'0';
    for(i=0;i<k;i++)back[i]=c[k-1-i];
    back[k]='\0';
}

const int MAX=10;
typedef struct Node
{
    int id;
    struct Node *next[MAX];
}TrieNode;

TrieNode *head;

void Tree_insert(char str[],int index)//插入单词
{
    Node *t,*s=head;
    int i,j;
    int len=strlen(str);
    for(i=0;i<len&&i<41;i++)
    {
        int id=str[i]-'0';
        if(s->next[id]==NULL)
        {
            t=new Node;
            for(j=0;j<10;j++)
            {
                t->next[j]=NULL;
            }
            t->id=-1;
            s->next[id]=t;
        }
        s=s->next[id];
        if(s->id<0)s->id=index;
    }
}

int Tree_Find(char str[])
{
    Node *s=head;
    int count,i;
    int len=strlen(str);
    for(i=0;i<len;i++)
    {
        int id=str[i]-'0';
        if(s->next[id]==NULL)
        {
            return -1;
        }
        else
        {
            s=s->next[id];
            count=s->id;
        }
    }
    return count;
}



void Tree_Del(Node *p)
{
    for(int i=0;i<10;i++)
    {
        if(p->next[i]!=NULL)
          Tree_Del(p->next[i]);
    }
    free(p);
}


char str[3][100];
int main()
{
 //   freopen("in.txt","r",stdin);
 //   freopen("out.txt","w",stdout);
    head=new Node;
    for(int i=0;i<10;i++)head->next[i]=NULL;
    head->id=-1;
    str[0][0]='1';
    str[0][1]=0;
    Tree_insert(str[0],0);
    str[1][0]='1';
    str[1][1]=0;
    Tree_insert(str[1],1);
    for(int i=2;i<100000;i++)//注意题目是小于，不能取等号。。WA了很多次啊
    {
        int len1=strlen(str[0]);
        int len2=strlen(str[1]);
        if(len2>60)
        {
            str[1][len2-1]=0;
            str[0][len1-1]=0;
        }
        add(str[0],str[1],str[2]);
      //  printf("%s\n",str[2]);
        Tree_insert(str[2],i);
        strcpy(str[0],str[1]);
        strcpy(str[1],str[2]);
     //   for(int i=0;i<100;i++)str[0][i]=str[1][i];
     //   for(int i=0;i<100;i++)str[1][i]=str[2][i];
    }
    int T;
    char str1[60];
    scanf("%d",&T);
    int iCase=0;
    while(T--)
    {
        iCase++;
        scanf("%s",&str1);
        printf("Case #%d: %d\n",iCase,Tree_Find(str1));
    }
    Tree_Del(head);
    return 0;
}
