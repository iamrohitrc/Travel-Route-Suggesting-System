#include<stdio.h>
#include<string.h>
#define INFINITY 9999
int MAX;
void dijkstra(int G[MAX][MAX],int n,int startnode,char city[MAX][20]);
int main()
{
    printf("\nFINDING SHORTEST PATH IN A DIGRAPH FROM A SOURCE CITY TO ALL OTHER CITIES\n");
    int t,z;
    int a,b;
    int n,startnode;
    int input_type;
    printf("\nEnter the Data Input Type : \n1)From File\n2)Manual\nYour Option : ");
    scanf("%d",&input_type);
    if(input_type==2)
    {
        printf("\nEnter Number of Test Cases : ");
        scanf("%d",&t);
        for(z=0;z<t;z++)
            {
                printf("\nEnter Number of Cities (Nodes) : ");
                scanf("%d",&MAX);
                n=MAX;
                printf("\nEnter Adjacency Matrix : \n");
                int G[MAX][MAX];
                {
                    for(a=0;a<n;a++)
                    {
                        for(b=0;b<n;b++)
                        {
                            scanf("%d",&G[a][b]);
                        }
                        printf("\n");
                    }
                }
                int c;
                char city[n][20];
                for(c=0;c<MAX;c++)
                {
                    printf("\nEnter City For Node %d -> ",c);
                    scanf("%s",&city[c][0]);
                }
                printf("\nEnter Source City's Node Number : ");
                scanf("%d",&startnode);

                printf("\n======================================================================================\n");
                printf("Case Number %d\n--------------------------------------------------------------------------------------",z+1);
                printf("\nNumber of Cities is %d\n",MAX);
                printf("\nGiven Adjacency Matrix : \n\n");
                {
                    for(a=0;a<n;a++)
                    {
                        for(b=0;b<n;b++)
                        {
                            printf("%d\t",G[a][b]);
                        }
                        printf("\n");
                    }
                }
                dijkstra(G,n,startnode,city);
            }
    }
    if(input_type==1)
    {
        FILE *fp;
        fp=fopen("sample.txt","r");
        fscanf(fp,"%d",&t);
        for(z=0;z<t;z++)
        {
            fscanf(fp,"%d",&MAX);
            printf("\n======================================================================================\n");
            printf("Case Number %d\n--------------------------------------------------------------------------------------",z+1);
            printf("\nNumber of Cities is %d\n",MAX);
            printf("\nGiven Adjacency Matrix : \n\n");
            n=MAX;
            int G[MAX][MAX];
            {
                for(a=0;a<n;a++)
                {
                    for(b=0;b<n;b++)
                    {
                        fscanf(fp,"%d",&G[a][b]);
                        printf("%d\t",G[a][b]);
                    }
                    printf("\n");
                }
            }
            fscanf(fp,"%d",&startnode);
            int c;
            char city[n][20];
            for(c=0;c<MAX;c++)
            {
                fscanf(fp,"%s",&city[c][0]);
            }
            dijkstra(G,n,startnode,city);
        }
        fclose(fp);
    }
    
    return 0;
}
void dijkstra(int G[MAX][MAX],int n,int startnode,char city[MAX][20])
{
    
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
    
    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        if(i!=startnode) pred[i]=startnode;
        if(i==startnode) pred[i]=-1;
        visited[i]=0;
    }
    
    distance[startnode]=0;
    count=1;
    
    while(count<n-1)
    {
        mindistance=INFINITY;
        
        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++)
        {
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
            
        }
        
        //check if a better path exists through nextnode
        visited[nextnode]=1;
        for(i=0;i<n;i++)
            if(!visited[i])
            {
                if(mindistance+cost[nextnode][i]<distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
            }
        count++;
    }
    printSolution(distance, n, pred,startnode,city);
}
void printPath(int distance[],int pred[], int startnode,char city[MAX][20])
{
    int src;
    src=startnode;
    // Base Case : If startnode is source
    if (pred[startnode]==-1)
    {
        return;
    }
    printPath(distance,pred, pred[startnode],city);
    if(distance[startnode]==9999)
        printf(" - ");
    if(distance[startnode]!=9999)
    {
        //printf(" %d %s", startnode,city[startnode]);
        printf(" %s ",city[startnode]);
    }
}
int printSolution(int distance[], int n, int pred[],int startnode,char city[MAX][20])
{
    int src;
    src=startnode;
    printf("\nSource City is %s",city[startnode]);
    printf("\n--------------------------------------------------------------------------------------");
    printf("\nSource -> Destination\t  \tDistance\t\tPath\n");
    printf("--------------------------------------------------------------------------------------");
    for (startnode = 0; startnode < n; startnode++)
    {
        if(distance[startnode]==9999)
           // printf("\n%d -> %d\t\tINFINITY\t", src, startnode);
            printf("\n%s -> %s\t\t\t\tINFINITY\t", city[src], city[startnode]);
        if(distance[startnode]!=9999)
            //printf("\n%d -> %d\t\t%d\t\t %d", src, startnode, distance[startnode], src);
            //if(strlen(city[startnode])<=6)
              //  printf("\n%s -> %s     \t\t%d km\t\t\t%s", city[src], city[startnode], distance[startnode], city[src]);
           // else
                printf("\n%-11s ->  %-15s \t%-5dkm\t\t%s", city[src], city[startnode], distance[startnode], city[src]);
        printPath(distance,pred, startnode,city);
        
    }
    printf("\n--------------------------------------------------------------------------------------\n");
    printf("======================================================================================\n\n");
    return 0;
}
