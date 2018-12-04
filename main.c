#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _no{
    int info;
    struct _no * prox, *skip;
}NO;

typedef struct lista{
    NO *inicio;
}LISTSKIP;

LISTSKIP *list_create()
{
    LISTSKIP *l=(LISTSKIP*)malloc(sizeof(LISTSKIP));
    if(l)
        l->inicio=NULL;
    return l;
}//Cria a lista e inicia o campo inicio com NULL

int list_insert(LISTSKIP *l,int v)
{
    NO *no=(NO*)malloc(sizeof(NO));
    if(!no) return 0;
    if(l->inicio==NULL) l->inicio=no;//Se a lista estiver vazia, o inicio passa a apontar para o primeiro elemento
    no->info=v;//o no recebe o valor a ser inserido
    no->skip=NULL; // e o skip recebe null, onde será mudado na função preenche skip
    NO *aux;
    aux=l->inicio;
    while(aux->prox!=NULL)
        aux=aux->prox; //percorre para achar o ultimo elemento da lista pra fazer a ligação
    aux->prox=no;
    no->prox=NULL;//no passa a ser o ultimo
    return 1;
}

int preenche_skip(LISTSKIP *l)
{
    int x=0,cont=0,w=0;
    NO *aux=l->inicio;
    NO *aux2=l->inicio;
    w=tamanho(l);
    w=sqrt(w);
    while(x<w)//Enquanto a qtd de vezes que um skip já foi mudado for menor do q a quantidade necessaria 
    {
        while(aux2->prox!=NULL)//nesse while ele vai achar o endereço que um skip vai possuir
        {
            aux2=aux2->prox;
            cont++;
            if(cont%w==0 && cont!=0) //o aux2 vai andar na lista até achar a caixinha que vai ser o proximo skip alterado
            {
                break;
            }
        }
        if(cont%w==0 || aux2->prox==NULL)//se ele achou o proximo skip ele entra nesse if
        {
            aux->skip=aux2;//o skip recebe o proximo skip
            x++;//conto a qtd de skips
            aux=aux2;//a caixinha do proximo skip passa a ser o atual
        }
    }
}

int tamanho(LISTSKIP *l)
{
    int cont=0;
    NO *aux;
    aux=l->inicio;
    while(aux->prox!=NULL)
    {    
        aux=aux->prox;
        cont++;
    }
    return cont;
    
}

void interceccao_de_list(LISTSKIP *l,LISTSKIP *m)
{
    NO *aux_l=l->inicio;
    NO* x;
    while(m->inicio!=NULL){//ele só vai parar até q todos os elementos da segunda lista tenham se juntado com a primeira
        while(aux_l->info < m->inicio->info || aux_l->prox!=NULL)//enquanto o dado da lista 1 for menor que o primeiro da lista 2 
            if(aux_l->skip->info<=m->inicio->info)//se o skip da caixinha atual for menor que o dado q eu quero inserir da lista 2...
                aux_l=aux_l->skip;//...a caixinha passa a ser o seu skip
            else// se não for menor quer dizer que o numero está entre a caixinha que contem um skip e o seu skip
                aux_l=aux_l->prox;//portanto, a partir daí ele passa a andar de um em um
        if(aux_l->prox!=NULL)//se a caixinha que eu encontrei não foi a ultima eu tenho que fazer uma ligaçao especial
        {
            x=aux_l->prox;//uma variavel do tipo nó
            aux_l->prox=m->inicio;
            aux_l=aux_l->prox;
            aux_l=x;
        }
        else
        {
            aux_l->prox=m->inicio;
            aux_l=aux_l->prox;
            aux_l->prox=NULL;
        }
        m->inicio=m->inicio->prox;//eu ando uma casa da lista 2, que será o proximo elemento a ser inserido na lista 1
        aux_l=l->inicio;//reinicio o aux_l
    }
}

int main(int argc, char** argv) {
    int x=0;
    LISTSKIP *l,*m;
    l=list_create();
    m=list_create();
    //esses whiles do insert foi só pra testar , pra ver se tava inserindo
    while(x<9)
        list_insert(l,x);
        x++;
    while(x>0)
        list_insert(m,x);
        x--;
    preenche_skip(l);
    interceccao_de_list(l,m);
    return (EXIT_SUCCESS);
}

