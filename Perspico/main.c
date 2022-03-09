#include <stdio.h>
#include <stdlib.h>
typedef struct nod
{
    int tabla[20][20];
    int cost,n;
    struct nod *urmator;
} TIP_NOD;
typedef struct lista
{
    TIP_NOD *nod;
    struct lista *urmator;
} LISTA;
void push(LISTA **prim, LISTA **ultim,TIP_NOD *p)
{
    LISTA *q;
    q=(LISTA *)malloc(sizeof(LISTA));
    q->nod=p;
    q->urmator=0;
    if (*prim==0)
    {
        *prim=q;
        *ultim=q;
    }
    else
    {
        (*ultim)->urmator=q;
        *ultim=q;
    }
}
int cost(TIP_NOD *p)
{
    int i,j,kost,n;
    n=p->n;
    kost=0;
    for (i=1; i<=p->n; i++)
        for (j=1; j<=p->n; j++)
            if (p->tabla[i][j]!=(i-1)*n+j)
                kost=kost+1;
    return kost;
}
void Branch_and_Bound()
{
    TIP_NOD *radacina;
    FILE *f;
    int i,j,kost,x,y,n,minim;
    TIP_NOD *pasinitial,*pasposibil,*pasrezultat;
    LISTA *prim, *ultim, *curent;
    radacina=(TIP_NOD *)malloc(sizeof(TIP_NOD));
    f=fopen("perspico.txt","r");
    if(!f)
    {
        perror("perspico.txt");
        exit(1);
    }
    fscanf(f,"%d",&radacina->n);
    for (i=1; i<=radacina->n; i++)
        for (j=1; j<=radacina->n; j++)
            fscanf(f,"%d",&radacina->tabla[i][j]);
    radacina->cost=cost(radacina);
    fclose(f);
    printf("Matricea de la care pornim:\n");
    for (i=1; i<=radacina->n; i++)
    {
        for (j=1; j<=radacina->n; j++)
            printf("%3d ",radacina->tabla[i][j]);
        printf("\n");
    }
    printf("\nPasii spre rezultat:\n");
    while (radacina->cost!=1)
    {
        prim=0;
        ultim=0;
        pasinitial=radacina;
        n=pasinitial->n;
        x=0;
        y=0;
        for (i=1; i<=n; i++)
            for (j=1; j<=n; j++)
                if (pasinitial->tabla[i][j]==(-1))
                {
                    x=i;
                    y=j;
                }
        pasposibil=(TIP_NOD *)malloc(sizeof(TIP_NOD));
        for (i=1; i<=n; i++)
            for (j=1; j<=n; j++)
                pasposibil->tabla[i][j]=pasinitial->tabla[i][j];
        pasposibil->n=n;
        if (x!=1)
        {
            pasposibil->tabla[x][y]=pasposibil->tabla[x-1][y];
            pasposibil->tabla[x-1][y]=-1;                           ///sus
            push(&prim,&ultim,pasposibil);
        }
        pasposibil=(TIP_NOD *)malloc(sizeof(TIP_NOD));
        for (i=1; i<=n; i++)
            for (j=1; j<=n; j++)
                pasposibil->tabla[i][j]=pasinitial->tabla[i][j];
        pasposibil->n=n;
        if (y!=1)
        {
            pasposibil->tabla[x][y]=pasposibil->tabla[x][y-1];
            pasposibil->tabla[x][y-1]=-1;                           ///stanga
            push(&prim,&ultim,pasposibil);
        }
        pasposibil=(TIP_NOD *)malloc(sizeof(TIP_NOD));
        for (i=1; i<=n; i++)
            for (j=1; j<=n; j++)
                pasposibil->tabla[i][j]=pasinitial->tabla[i][j];
        pasposibil->n=n;
        if (x!=n)
        {
            pasposibil->tabla[x][y]=pasposibil->tabla[x+1][y];
            pasposibil->tabla[x+1][y]=-1;                           ///jos
            push(&prim,&ultim,pasposibil);
        }
        pasposibil=(TIP_NOD *)malloc(sizeof(TIP_NOD));
        for (i=1; i<=n; i++)
            for (j=1; j<=n; j++)
                pasposibil->tabla[i][j]=pasinitial->tabla[i][j];
        pasposibil->n=n;
        if (y!=1)
        {
            pasposibil->tabla[x][y]=pasposibil->tabla[x][y+1];
            pasposibil->tabla[x][y+1]=-1;                       ///dreapta
            push(&prim,&ultim,pasposibil);
        }
        curent=prim;
        minim=n*n+1;
        while (curent!=0)
        {
            kost=cost(curent->nod);
            if (kost<minim)
            {
                pasrezultat=curent->nod;
                minim=kost;
                pasrezultat->cost=kost;
            }
            curent=curent->urmator;
        }
        for (i=1; i<=n; i++)
        {
            for (j=1; j<=n; j++)
                printf("%3d ",pasrezultat->tabla[i][j]);
            printf("\n");
        }
        radacina=pasrezultat;
        printf("\n");
    }
}
int main()
{
    Branch_and_Bound();
    return 0;
}
