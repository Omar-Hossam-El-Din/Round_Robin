#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// NAME : Omar Hossam El Din Ebraheem .
// ID : 6667 .

typedef struct
{
    char *name;
    int start_time;
    int remain_time;
} Process;

typedef struct
{
    Process data;
    struct Node*next;

} Node;

typedef struct
{
    Node*front;
    Node*end;

} Queue;

Node*newNode(Process  value)
{
    Node*n;
    n=(Node*)malloc(sizeof(Node));
    n->data=value;
    n->next=NULL;
    return n;
}
Queue*initialize()
{
    Queue*q;
    q=(Queue*)malloc(sizeof(Queue));
    q->front=NULL;
    q->end=NULL;
    return q;
}
int isEmpty (Queue*q)
{
    if (q->front==NULL)
        return 1;
    else
        return 0;
}
void enqueue(Queue*q,Process value)
{
    Node *n=newNode(value);
    if (isEmpty(q))
        q->front=q->end=n;
    else
    {
        q->end->next=n;
        q->end=n;
    }
}
Process  dequeue(Queue*q)
{
    Process  num ;
    if(isEmpty(q))
        return ;
    else
    {
        num=q->front->data;
        q->front=q->front->next;
        return num;
    }
}

void destroy (Queue*q)
{
    while(!isEmpty(q))
    {
        if (q->front!=NULL)
        {
            Node * temp=q->front;
            q->front=temp->next;
            free(temp);
            if (q->front==NULL)
                q->end=NULL;
        }
    }
}
void RoundRobin(char* filename)
{
    FILE*fp;
    fp=fopen(filename,"r");
    if (fp==NULL)
        printf("The File Not Exist\n");
    char firstline[100];
    char line[5000];
    char str[1000];
    fgets(firstline,100,fp);
    printf("-------------------------------------------\n");
    printf("%s",firstline);
    fseek(fp,0,0);
    char arr[20];
    fscanf(fp,"%s",&arr);
    fscanf(fp,"%s",&arr);
    fscanf(fp,"%s",&arr);
    fscanf(fp,"%s",&arr);
    int slot;
    fscanf(fp,"%d",&slot);
    printf("Time:%d",slot);
    int i ;
    Process p[100];
    int count=0;
    fseek(fp,26,0);
    while(!feof(fp))
    {
        count++;
        fgets(line,5000,fp);

    }
    printf("\nlines:%d",count);
    fseek(fp,26,0);
    int n ;
    char name[4];
    int x,y;
    for (i=0; i<count; i++)
    {
        p[i].name=(char*)malloc(3);
        fscanf(fp,"%s",p[i].name);
        fscanf(fp,"%d",&p[i].start_time);
        fscanf(fp,"%d",&p[i].remain_time);
    }
    fclose(fp);
    printf("\n-------------------------------------------");
    for(i=0; i<count; i++)
    {
        printf("\n%s\t\t%d\t\t%d\t\t\n",p[i].name,p[i].start_time,p[i].remain_time);
    }
    int j;
    Queue*q=initialize();
    Process  c, d;
    printf("-------------------------------------------\n");
    printf("OutPut :\n");
    for (j=0; j<slot; j++)
    {
        for(i=0; i<count; i++)
        {
            if (j==p[i].start_time)
            {
                p[i].remain_time--;
                enqueue(q,p[i]);

            }
            else if (p[i].start_time<j&&p[i].remain_time!=0)
            {
                p[i].remain_time--;
                enqueue(q,p[i]);

            }
        }
        if (isEmpty(q))
            printf("\nidle\t(%d --> %d)",j,(j+1));
        else
        {
            Process a=dequeue(q);
            if (a.remain_time!=0)
                printf("\n%s\t(%d --> %d)",a.name,j,(j+1));
            else if (a.remain_time==0)
                printf("\n%s\t(%d --> %d)%s aborts",a.name,j,(j+1),a.name);
        }

    }
    printf("\n--------------stop-----------------------");
    destroy(q);
}


int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("-------------------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------------");
        }
        puts("\nEnter file name or Ctrl+Z to exit:\n");
        puts("----------------------------------------");
    }

    return 0;
}
