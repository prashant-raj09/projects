#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf  999999
struct vertex
{
    char name[40];
};
struct edge
{
    int dis;
    int walk;
    int car;
    int cycle;
};
int min_dist(int *,int *,int);
void shortest_distance(int ,int ,struct edge mat[][12],struct vertex v[12],int );
void shortest_walking(int s,int d,struct edge mat[][12],struct vertex v[12],int n);
void shortest_cycling(int s,int d,struct edge mat[][12],struct vertex v[12],int n);
void shortest_driving(int s,int d,struct edge mat[][12],struct vertex v[12],int n);
void edge_created(struct edge mat[12][12],int);
void vertex_display();
void vertex_created(struct vertex *,int);
void display(struct vertex *,int);
void edge_display(struct edge mat[12][12],int,struct vertex v[12]);
int main()
{
    int s,d,ch,ch2;
    struct vertex v[12];
    struct edge mat[12][12];
    vertex_created(v,12);
    edge_created(mat,12);

    do{
    system("cls");
    printf("                               ***      Kingslanding        ****\n");
    printf("\t1. Display Landmarks\n\t2. Display distance between landmarks\n\t3. Edit Database\n\t4. Find shortest path\n\t5. Exit\n");
    printf("                               ***************\n");
    printf("What would you like to do?\n");
    scanf("%d",&ch);
    switch(ch)
    {

            case 1: printf("\nThese are the land marks on the map enter where are you and where you want to go\n");
                    display(v,12);
                    printf("\nPress enter to continue\n");
                    fflush(stdin);
                    getchar();
                    break;
            case 2: edge_display(mat,12,v);
                    printf("\nPress enter to continue\n");
                    fflush(stdin);
                    getchar();
                    break;
            case 3: printf("Enter source location->  ");
                    scanf("%d",&s);
                    printf("Enter destination-> ");
                    scanf("%d",&d);
                    printf("Enter the new distance, walking time, cycling time, driving time\n");
                    scanf("%d%d%d%d",&mat[s][d].dis,&mat[s][d].walk,&mat[s][d].cycle,&mat[s][d].car);
                    printf("Data updated successfully, press enter to continue\n");
                    fflush(stdin);
                    getchar();
                    break;
            case 4: printf("your location->  ");
                    scanf("%d",&s);
                    printf("Enter your destination-> ");
                    scanf("%d",&d);
                    printf("\n1. Minimise distance\n2. Minimise walking time\n3. Minimise cycling time\n4. Minimise driving time\n");
                    scanf("%d",&ch2);
                    switch(ch2)
                    {
                        case 1: shortest_distance(s,d,mat,v,12);
                                break;
                        case 2: shortest_walking(s,d,mat,v,12);
                                break;
                        case 3: shortest_cycling(s,d,mat,v,12);
                                break;
                        case 4: shortest_driving(s,d,mat,v,12);
                                break;
                        default:printf("Invalid Input\n");
                    }
                    printf("\nPress enter to continue\n");
                    fflush(stdin);
                    getchar();
                    break;
            case 5: printf("Press 0 to exit and any other number to cancel\n");
                    scanf("%d",&ch);
                    break;
            default:printf("Invalid input, please try again\n");
                    printf("\nPress enter to continue\n");
                    fflush(stdin);
                    getchar();
    }
    }while(ch);



}
void shortest_distance(int s,int d,struct edge mat[][12],struct vertex v[12],int n)
{
  int c[n],vertex[n],i,u,j,p[n];

  for(i=0;i<n;i++)
  {
    if(i==s)
        c[i]=0;
    else
        c[i]=inf;
    vertex[i]=0;
  }

  p[s]=-1;

  for(i=0;i<n-1;i++)
  {
     u=min_dist(c,vertex,n);  //Selecting Nearest vertex

     vertex[u]=1;

     for(j=0;j<n;j++)   //Relaxation
     {
         if(mat[u][j].dis != 0 && vertex[j] == 0)
         {
             if(mat[u][j].dis + c[u] < c[j])
             {
                c[j] = c[u] + mat[u][j].dis;
                p[j]=u;
             }
         }
     }
  }
  int fn=11,ar[12],fnf=c[d];
  ar[fn]=d;
  do
  {
      ar[--fn]=p[d];
      d=p[d];
  }while(p[d]!=-1);
  for(;fn<11;fn++)
    printf("%s--->",v[ar[fn]].name);
  printf("%s",v[ar[11]].name);
  printf("\nTotal distance = %d\n",fnf);
}

int min_dist(int cost[],int vertices[],int n)
{
  int i,ind,min;
  for(i=0;i<n;i++)
    {
        if(vertices[i]==0)
            break;
    }
  ind=i;
  min=cost[i];
  i += 1;
  for(;i<n;i++)
  {
      if(vertices[i]==0)
      {
          if(cost[i]<min)
          {
              ind=i;
              min=cost[i];
          }

      }
  }
  return(ind);
}

void shortest_walking(int s,int d,struct edge mat[][12],struct vertex v[12],int n)
{
  int c[n],vertex[n],i,u,j,p[n];

  for(i=0;i<n;i++)
  {
    if(i==s)
        c[i]=0;
    else
        c[i]=inf;
    vertex[i]=0;
  }

  p[s]=-1;

  for(i=0;i<n-1;i++)
  {
     u=min_dist(c,vertex,n);  //Selecting Nearest vertex

     vertex[u]=1;

     for(j=0;j<n;j++)   //Relaxation
     {
         if(mat[u][j].walk != 0 && vertex[j] == 0)
         {
             if(mat[u][j].walk + c[u] < c[j])
             {
                c[j] = c[u] + mat[u][j].walk;
                p[j]=u;
             }
         }
     }
  }
  int fn=11,ar[12],fnf=c[d];
  ar[fn]=d;
  do
  {
      ar[--fn]=p[d];
      d=p[d];
  }while(p[d]!=-1);
  for(;fn<11;fn++)
    printf("%s--->",v[ar[fn]].name);
  printf("%s",v[ar[11]].name);
  printf("\nTotal walking time = %d\n",fnf);
}

void shortest_cycling(int s,int d,struct edge mat[][12],struct vertex v[12],int n)
{
  int c[n],vertex[n],i,u,j,p[n];

  for(i=0;i<n;i++)
  {
    if(i==s)
        c[i]=0;
    else
        c[i]=inf;
    vertex[i]=0;
  }

  p[s]=-1;

  for(i=0;i<n-1;i++)
  {
     u=min_dist(c,vertex,n);  //Selecting Nearest vertex

     vertex[u]=1;

     for(j=0;j<n;j++)   //Relaxation
     {
         if(mat[u][j].cycle != 0 && vertex[j] == 0)
         {
             if(mat[u][j].cycle + c[u] < c[j])
             {
                c[j] = c[u] + mat[u][j].cycle;
                p[j]=u;
             }
         }
     }
  }
  int fn=11,ar[12],fnf=c[d];
  ar[fn]=d;
  do
  {
      ar[--fn]=p[d];
      d=p[d];
  }while(p[d]!=-1);
  for(;fn<11;fn++)
    printf("%s--->",v[ar[fn]].name);
  printf("%s",v[ar[11]].name);
  printf("\nTotal cycling time = %d\n",fnf);
}
void shortest_driving(int s,int d,struct edge mat[][12],struct vertex v[12],int n)
{
  int c[n],vertex[n],i,u,j,p[n];

  for(i=0;i<n;i++)
  {
    if(i==s)
        c[i]=0;
    else
        c[i]=inf;
    vertex[i]=0;
  }

  p[s]=-1;

  for(i=0;i<n-1;i++)
  {
     u=min_dist(c,vertex,n);  //Selecting Nearest vertex

     vertex[u]=1;

     for(j=0;j<n;j++)   //Relaxation
     {
         if(mat[u][j].car != 0 && vertex[j] == 0)
         {
             if(mat[u][j].car + c[u] < c[j])
             {
                c[j] = c[u] + mat[u][j].car;
                p[j]=u;
             }
         }
     }
  }
  int fn=11,ar[12],fnf=c[d];
  ar[fn]=d;
  do
  {
      ar[--fn]=p[d];
      d=p[d];
  }while(p[d]!=-1);
  for(;fn<11;fn++)
    printf("%s--->",v[ar[fn]].name);
  printf("%s",v[ar[11]].name);
  printf("\nTotal driving time = %d\n",fnf);
}

void vertex_display()
{
    printf("\nPlaces in the city are\n");
    printf("\n1.CURE hospital\n2.LERNER higher secondry school\n3.GOD's church\n4.YOUR bank\n5.All IN ONE general store\n6.CITY mall\n7.PLAY's theatre\n8.police station\n9.District court\n10.District jail\n11.Sant sabstian park\n12.bhand bar");
}
void vertex_created(struct vertex v[],int n)
{

    strcpy(v[0].name,"CURE hospital");
    strcpy(v[1].name,"LERNER higher secondry school");
    strcpy(v[2].name,"GOD's church");
    strcpy(v[3].name,"YOUR bank");
    strcpy(v[4].name,"All IN ONE general store");
    strcpy(v[5].name,"CITY mall");
    strcpy(v[6].name,"PLAY's theatre");
    strcpy(v[7].name,"police station");
    strcpy(v[8].name,"District court");
    strcpy(v[9].name,"District jail");
    strcpy(v[10].name,"Sant sabstian park");
    strcpy(v[11].name,"bhand bar");
}
void display(struct vertex v[],int n)
{
    int i;
    printf("\n");
    for(i=0;i<n;i++)
        printf("press %d.for %s\n",i,v[i].name);
}
void edge_created(struct edge mat[12][12],int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
        mat[i][j].dis=0;
        mat[i][j].walk=0;
        mat[i][j].cycle=0;
        mat[i][j].car=0;
        }
    mat[0][2].dis=2;
    mat[0][2].walk=6;
    mat[0][2].cycle=2;
    mat[0][2].car=1;
      mat[0][6].dis=3;
    mat[0][6].walk=9;
    mat[0][6].cycle=3;
    mat[0][6].car=2;
      mat[1][2].dis=4;
    mat[1][2].walk=12;
    mat[1][2].cycle=4;
    mat[1][2].car=2;
      mat[1][5].dis=5;
    mat[1][5].walk=15;
    mat[1][5].cycle=5;
    mat[1][5].car=3;
      mat[1][6].dis=6;
    mat[1][6].walk=18;
    mat[1][6].cycle=6;
    mat[1][6].car=3;
      mat[1][11].dis=7;
    mat[1][11].walk=21;
    mat[1][11].cycle=7;
    mat[1][11].car=4;
      mat[3][4].dis=8;
    mat[3][4].walk=24;
    mat[3][4].cycle=8;
    mat[3][4].car=4;
      mat[3][5].dis=9;
    mat[3][5].walk=27;
    mat[3][5].cycle=9;
    mat[3][5].car=5;
      mat[4][5].dis=10;
    mat[4][5].walk=30;
    mat[4][5].cycle=10;
    mat[4][5].car=5;
      mat[4][7].dis=11;
    mat[4][7].walk=33;
    mat[4][7].cycle=11;
    mat[4][7].car=6;
      mat[4][8].dis=12;
    mat[4][8].walk=36;
    mat[4][8].cycle=12;
    mat[4][8].car=6;
      mat[6][9].dis=13;
    mat[6][9].walk=39;
    mat[6][9].cycle=13;
    mat[6][9].car=7;
      mat[6][10].dis=14;
    mat[6][10].walk=42;
    mat[6][10].cycle=14;
    mat[6][10].car=7;
      mat[7][11].dis=15;
    mat[7][11].walk=45;
    mat[7][11].cycle=15;
    mat[7][11].car=8;
      mat[8][9].dis=16;
    mat[8][9].walk=48;
    mat[8][9].cycle=16;
    mat[8][9].car=8;
      mat[9][10].dis=17;
    mat[9][10].walk=52;
    mat[9][10].cycle=17;
    mat[9][10].car=9;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        if(i>j)
        {
    mat[i][j].dis=mat[j][i].walk;
    mat[i][j].walk=mat[j][i].walk;
    mat[i][j].cycle=mat[j][i].cycle;
    mat[i][j].car=mat[j][i].car;
        }
    }
}
void edge_display(struct edge mat[12][12],int n,struct vertex v[12])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        if(mat[i][j].dis)
        printf("%s to %s     =     %dKm\n",v[i].name,v[j].name,mat[i][j].dis);
    }
}
