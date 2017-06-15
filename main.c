#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arqn = 1;
#define TAM 13
#define ERROR "arqnotfound-" //Utilizado para retornar nas funções no lugar de NULL

/*#define TEMP1 "arq_temp_in1" //Utilizado no insere
#define TEMP2 "arq_temp_in2"
*/

int comp(const void * elem1, const void * elem2);

void cria_arv(int t, char *nome);
char *busca_arv(int t, char *no, int ch);
void imprime_arv(int t, char *no, int andar);

void insere_arv(int t, char *no, char *pai,int ch);
void divisao_arv(int t, char *no, char *pai);/*
void insere_nao_completo_arv(int t, char *nome, int ch);
*/

void lerNoC(int t, char *nome); //Printa tudo dentro do arquivo "nome"
void lerNoS(int t, char *nome); //Printa só as chaves dentro do arquivo "nome"
int eFolha(int t, char *no);
void limpaArq(char *nome); //Reseta o arquivo, e deixa pronto pra ser usado de novo
int pos_arq(int t, int i); //Retorna a posição do nome do arquivo filho desejado
void inicializa_arv(int t, char *nome, int raiz); //Função só pra testar inicialização
//********************************************************************************************************
//********************************************************************************************************

int main(){
    int t = 2;
    /* inicializa_arv(t, "raiz.dat", 20); //Raiz
     lerNoC(t, "raiz.dat");
     inicializa_arv(t, "arq00001.dat", 10); //Esquerda
     lerNoC(t, "arq00001.dat");
     inicializa_arv(t, "arq00002.dat", 33); //Direita
     lerNoC(t, "arq00002.dat");
     imprime_arv(t, "raiz.dat", 0);*/
    insere_arv(2,"arq00000.dat",NULL,6);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    insere_arv(2,"arq00002.dat",NULL,10);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    insere_arv(2,"arq00000.dat",NULL,15);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    insere_arv(2,"arq00000.dat",NULL, 5);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    lerNoC(t, "arq00001.dat");
    printf("\n");
    lerNoC(t, "arq00002.dat");
    printf("\n");
    insere_arv(2,"arq00000.dat",NULL, 20);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    lerNoC(t, "arq00001.dat");
    printf("\n");
    lerNoC(t, "arq00002.dat");
    printf("\n");
    insere_arv(2,"arq00000.dat",NULL, 40);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    lerNoC(t, "arq00001.dat");
    printf("\n");
    lerNoC(t, "arq00002.dat");
    printf("\n");
    insere_arv(2,"arq00000.dat",NULL, 50); //algum erro
    lerNoC(t, "arq00000.dat");
    printf("\n");
    lerNoC(t, "arq00001.dat");
    printf("\n");
    lerNoC(t, "arq00002.dat");
    printf("\n");
    //insere_arv(2,"arq00000.dat",4); //funciona mas descaralha o nchaves
    //insere_arv(2,"arq00000.dat",5); //descaralha a porra toda
    //lerNoC(t, "arq00000.dat");
    //printf("\n");
    //lerNoC(t, "arq00001.dat");
    //printf("\n");
    //lerNoC(t, "arq00002.dat");
    //printf("\n");

    char *nome = (char*)malloc(sizeof(char)*TAM);
    strcpy(nome, busca_arv(t, "raiz.dat", 44));
    if(strcmp(nome, ERROR))printf("%s", nome);
}

void lerNoC(int t, char *nome){
    FILE *fp = fopen(nome, "rb");
    if(!fp)exit(1);
    int i, elem;
    char str[TAM];
    for(i = 0;i < (2 * t); i++){
        fread(&elem, sizeof(int), 1, fp);
        printf("%d\n", elem);

    }
    for(i = 0;i < 2 * t; i++){
        fread(&str, sizeof(char), TAM, fp);
        printf("%s\n", str);
    }
    fclose(fp);
}

void lerNoS(int t, char *nome){
    FILE *fp = fopen(nome, "rb");
    if(!fp)return;
    int i, elem;
    char str[TAM];
    fseek(fp,sizeof(int),SEEK_SET);

    for(i = 0;i < (2 * t)-1; i++){
        fread(&elem, sizeof(int), 1, fp);
        if(elem != -1){
            printf("%d\n", elem);
        }
    }

    fclose(fp);
}

int eFolha(int t, char *no){
    FILE *fp = fopen(no, "rb");
    if(!fp)return 1;

    int nchaves, i, e;
    int pos = pos_arq(t, 0);
    fread(&nchaves, sizeof(int), 1, fp);
    fseek(fp, pos, SEEK_SET);
    char filho[TAM];

    for(i = 0;i < nchaves+1; i++){
        fread(&filho, sizeof(char), TAM, fp);
        FILE *ff = fopen(filho, "rb");
        if(ff){
            fclose(ff);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

void limpaArq(char *nome){
    FILE *fp = fopen(nome, "rb");
    if (!fp) return;
    remove(nome);
}

int pos_arq(int t, int i){
    int pos = ((t * 2))* sizeof(int);
    return pos+(TAM*i*sizeof(char));
}

void inicializa_arv(int t, char *nome, int raiz){
    FILE *fp = fopen(nome, "wb");
    if (!fp) exit(1);

    int n1 = 1, e = -1, i;
    fwrite(&n1, sizeof(int), 1, fp);
    fwrite(&raiz, sizeof(int), 1, fp);
    for(i = 0; i < (2 * t)-2; i++){
        fwrite(&e, sizeof(int), 1, fp);
    }

    char str[TAM], ci[6];
    for(i = 0; i < 2 * t; i++){
        sprintf(ci, "%05d", arqn);
        arqn++;
        strcpy(str, "arq");
        strcat(str, ci);
        strcat(str, ".dat");
        fwrite(&str, sizeof(char), TAM, fp);
    }
    fclose(fp);
}

void cria_arv(int t, char *nome){
    FILE *fp = fopen(nome, "wb");
    if (!fp) exit(1);

    int e = -1, i = 0;
    fwrite(&i, sizeof(int), 1, fp);
    for(i = 0; i < (2 * t)-1; i++){
        fwrite(&e, sizeof(int), 1, fp);
    }

    char str[TAM], ci[6];
    for(i = 0; i < 2 * t; i++){
        sprintf(ci, "%05d", arqn);
        arqn++;
        strcpy(str, "arq");
        strcat(str, ci);
        strcat(str, ".dat");
        fwrite(&str, sizeof(char), TAM, fp);
    }
    fclose(fp);
}

char *busca_arv(int t, char *no, int ch){ //no = raiz
    FILE *fp = fopen(no, "rb");
    if(!fp)return ERROR;

    int nchaves, i = 0;

    fread(&nchaves, sizeof(int), 1, fp);
    if(!nchaves){
        fclose(fp);
        return ERROR;
    }
    int chaves[nchaves];
    fread(&chaves, sizeof(int), nchaves, fp);

    while(i < nchaves && ch > chaves[i])i++;
    if(i < nchaves && ch == chaves[i])return no;

    fclose(fp);
    if(eFolha(t, no))return ERROR;
    fp = fopen(no, "rb");

    int pos = pos_arq(t, i);

    fseek(fp, pos, SEEK_SET);
    char str[TAM];
    fread(&str, sizeof(char), TAM, fp);
    return busca_arv(t , str, ch);
}

void imprime_arv(int t, char *no, int andar){
    FILE *fp = fopen(no, "rb");
    if(!fp)return;

    int i, j, nchaves;
    char filho[TAM];

    fread(&nchaves, sizeof(int), 1, fp);
    for(i = 0;i <= nchaves-1; i++){
        fseek(fp, pos_arq(t, i), SEEK_SET);
        fread(&filho, sizeof(char), TAM, fp);
        imprime_arv(t, filho, andar+1);

        for(j=0; j<=andar; j++) printf("   ");

        fclose(fp);
        lerNoS(t, no);
        FILE *fp = fopen(no, "rb");
        if(!fp)return;
    }

    fseek(fp, pos_arq(t, i), SEEK_SET);
    fread(&filho, sizeof(char), TAM, fp);
    imprime_arv(t, filho, andar+1);

    fclose(fp);
}

/*TAB *Insere(TAB *T, int k, int t){
  if(Busca(T,k)) return T;
  if(!T){
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,k,t);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t);
  return T;
}*/
/*
void insere_arv(int t, char *no, int ch){ //no = raiz
	if(strcmp(ERROR, busca_arv(t, no, ch))) {
        return;
    }

	FILE *fp = fopen(no, "rb+");

    if(!fp){
		inicializa_arv(t, no, ch);
		return;
	}

    if(eFolha(t,no)){
        int nchaves;
        fread(&nchaves,sizeof(int),1,fp);
        if (nchaves + 1 <= (2*t)-1){
            nchaves++;
            int pos = nchaves * sizeof(int);
            fseek(fp,0,SEEK_SET);
            fwrite(&nchaves,sizeof(int),1,fp);
            fseek(fp,pos,SEEK_SET);
            fwrite(&ch, sizeof(int),1,fp);
            fclose(fp);
            return;
        }
        else{
            int meio = descobreMeio(no,ch,t);
            int aux;
            int cont=0;
            while(1) {
                cont++;
                fseek(fp, cont * 4, SEEK_SET);
                fread(&aux, sizeof(int), 1, fp);
                if (aux == -1) {
                    fseek(fp,0,SEEK_SET);
                    int nchaves;
                    fread(&nchaves,sizeof(int),1,fp);
                    nchaves++;
                    fseek(fp,0,SEEK_SET);
                    fwrite(&nchaves,sizeof(int),1,fp);
                    fseek(fp, cont * 4, SEEK_SET);
                    fwrite(&ch, sizeof(int), 1, fp);
                    break;
                }
            }
            cont = 0;
            fclose(fp);
            while(1) {
                fp = fopen(no,"rb+");
                cont++;
                fseek(fp, cont*4, SEEK_SET);
                fread(&aux, sizeof(int), 1, fp);
                if(aux < meio){
                    int pos = pos_arq(t,0);
                    fseek(fp,pos,SEEK_SET);
                    char nome[TAM];
                    fread(&nome,sizeof(char)*TAM,1,fp);
                    fseek(fp, cont*4, SEEK_SET);
                    int kek = -1;
                    fwrite(&kek, sizeof(int), 1, fp);
                    fseek(fp,0,SEEK_SET);
                    int nchaves;
                    fread(&nchaves,sizeof(int),1,fp);
                    nchaves--;
                    if(nchaves < 1){
                        nchaves = 1;
                    }
                    fseek(fp,0,SEEK_SET);
                    fwrite(&nchaves,sizeof(int),1,fp);
                    fclose(fp);
                    reorganiza(t,no);
                    insere_arv(t,nome,aux);
                }
                else if(aux > meio){
                    int pos = pos_arq(t,1);
                    fseek(fp,pos,SEEK_SET);
                    char nome[TAM];
                    fread(&nome,sizeof(char)*TAM,1,fp);
                    fseek(fp, cont*4, SEEK_SET);
                    int kek = -1;
                    fwrite(&kek, sizeof(int), 1, fp);
                    fseek(fp,0,SEEK_SET);
                    int nchaves;
                    fread(&nchaves,sizeof(int),1,fp);
                    nchaves--;
                    if(nchaves < 1){
                        nchaves = 1;
                    }
                    fseek(fp,0,SEEK_SET);
                    fwrite(&nchaves,sizeof(int),1,fp);
                    fclose(fp);
                    reorganiza(t,no);
                    insere_arv(t,nome,aux);
                }
                if (cont == (2*t)-1 ){
                    fclose(fp);
                    break;
                }
            }
        }
    }
    else {
        int i;
        int aux, aux2;
        fseek(fp, sizeof(int), SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        fread(&aux2, sizeof(int), 1, fp);
        for (i = 1; i < (2 * t) - 1; i++){
            if (ch > aux && (ch < aux2 || aux2 == -1)) {
                int pos = pos_arq(t, i);
                fseek(fp, pos, SEEK_SET);
                char nome[TAM];
                fread(&nome, sizeof(char) * TAM, 1, fp);
                insere_arv(t, nome, ch);
            }
            else if (ch<aux){
                int pos = pos_arq(t, 0);
                fseek(fp, pos, SEEK_SET);
                char nome[TAM];
                fread(&nome, sizeof(char) * TAM, 1, fp);
                insere_arv(t, nome, ch);
            }
            else{
                fseek(fp, sizeof(int) * i, SEEK_SET);
                fread(&aux, sizeof(int), 1, fp);
                fread(&aux2, sizeof(int), 1, fp);
            }
        }
    }
 }
*/
void reorganiza(int t,char* no){
    FILE *fp =fopen(no,"rb+");
    if(!fp) exit(1);
    int vet[(2*t)-1];
    fseek(fp,sizeof(int),SEEK_SET);
    fread(&vet,sizeof(int),(2*t)-1,fp);
    for (int i = 0; i <(2*t)-1 ; ++i) {
        for (int j = i + 1; j < (2*t)-1; ++j) {
            if(vet[i]==-1 && vet[j]!=-1){
                vet[i] = vet[j];
                vet[j] = -1;
            }
        }
    }
    fseek(fp,sizeof(int),SEEK_SET);
    fwrite(&vet,sizeof(int),(2*t)-1,fp);
    fclose(fp);
}

int descobreMeio(char* no,int ch,int t){
    FILE *fp = fopen(no,"rb");
    if(!fp) return -1;
    int meio[(2*t)-1], aux;
    int i, trigger = 1;
    for(i=0;i<3;i++) {
        fseek(fp, i*sizeof(int) + 4, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if(i==2){
            meio[i] = ch;
        }
        else{
            meio[i] = aux;
        }
    }
    qsort(meio,(2*t)-1,sizeof(int),comp);
    return meio[((2*t)-1)/2];

}

int comp(const void * elem1, const void * elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void divide(int t, char *no, char *pai){
    FILE *fp = fopen(no,"rb+");
    if(!fp);
    int nchaves;
    fread(&nchaves, sizeof(int),1,fp);
    int vet[nchaves];
    int aux[nchaves];
    int zeroChaves = 0;
    for(int i = 0;i<nchaves;i++){
        aux[i] = -1;
    }
    fread(vet,sizeof(int),nchaves,fp);
    fseek(fp,0,SEEK_SET);
    fwrite(&zeroChaves,sizeof(int),1,fp);
    fwrite(aux,sizeof(int),nchaves,fp);
    if(0){ //if é raiz ou seja, pai == null
        //temos uma nova raiz
        //altura da arvore vai aumentar
        //arvore precisara ser reestruturada
    }
    else{
        fclose(fp);
        FILE *fpai = fopen(pai,"rb+");
        int nchavesPai;
        fread(&nchavesPai,sizeof(int),1,fpai);
        char filho[TAM];
        for(int i=0;i<nchaves;i++){
            fp = fopen(no,"rb+");
            if(i == nchaves/2){
                if(nchavesPai < 2*t-1){
                    fclose(fp);
                    insere_arv_agressivo(t,pai,vet[i]);
                }
                else{
                    insere_arv(t,pai,"avo",vet[i]);// avo precisa ser implementado
                }
            }
            else if(i < nchaves/2){ //filho da esquerda do pai
                int pos = pos_arq(t,nchavesPai);
                fseek(fpai,pos,SEEK_SET);
                fread(filho,sizeof(char),TAM,fpai);
                fclose(fp);
                insere_arv(t,filho,pai,vet[i]);
            }
            else{ //filho da direita do pai
                int pos = pos_arq(t,nchavesPai+1);
                fseek(fpai,pos,SEEK_SET);
                fread(filho,sizeof(char),TAM,fpai);
                fclose(fp);
                insere_arv(t,filho,pai,vet[i]);
            }
        }
    }

}
void insere_arv_agressivo(int t,char *raiz,int ch){
    FILE *fp = fopen(raiz,"rb+");
    if(!fp) exit(1);
    int nchaves;
    fread(&nchaves, sizeof(int), 1, fp);
    fseek(fp, sizeof(int), SEEK_SET);
    int vet[nchaves+1];
    fread(&vet, sizeof(int), nchaves, fp);
    vet[nchaves] = ch;
    qsort( vet, nchaves+1, sizeof(int), comp);
    fseek(fp, sizeof(int), SEEK_SET);
    fwrite(&vet, sizeof(int), nchaves+1, fp);
    fseek(fp, 0, SEEK_SET);
    nchaves++;
    fwrite(&nchaves, sizeof(int), 1, fp);
    fclose(fp);
    return;

}

void insere_arv(int t, char *raiz, char*pai, int ch){
    FILE *fp = fopen(raiz, "rb+");
    if(!fp){
        inicializa_arv(t, raiz, ch);
        return;
    }
    int nchaves;
    fread(&nchaves, sizeof(int), 1, fp);
    if(nchaves == (t * 2)- 1){
        fclose(fp);
        divide(t, raiz, pai);
        insere_arv( t, raiz, pai, ch);
        return;
    }
    fclose(fp);
    if(eFolha( t, raiz)){
        fp = fopen( raiz, "rb+"); //erra em algum lugar desse else quando insere o 50
        if(!fp)exit(1);
        fseek(fp, sizeof(int), SEEK_SET);
        int vet[nchaves+1];
        fread(&vet, sizeof(int), nchaves, fp);
        vet[nchaves] = ch;
        qsort( vet, nchaves+1, sizeof(int), comp);
        fseek(fp, sizeof(int), SEEK_SET);
        fwrite(&vet, sizeof(int), nchaves+1, fp);
        fseek(fp, 0, SEEK_SET);
        nchaves++;
        fwrite(&nchaves, sizeof(int), 1, fp);
        fclose(fp);
        return;
    }else{
        int i;
        fp = fopen( raiz, "rb+");
        if(!fp)exit(1);
        fseek(fp, sizeof(int), SEEK_SET);
        int vet[nchaves], pos;
        fread(&vet, sizeof(int), nchaves, fp);
        for(i = 0; i < nchaves; i++){
            if(ch < vet[i]){
                pos = pos_arq( t, i);
                fseek(fp, pos, SEEK_SET);
                char no[TAM];
                fread(&no, sizeof(char), TAM, fp);
                fclose(fp);
                insere_arv( t, no, raiz, ch);
                return;
            }

        }
        pos = pos_arq( t, i);
        fseek(fp, pos, SEEK_SET);
        char no[TAM];
        fread(&no, sizeof(char), TAM, fp);
        fclose(fp);
        insere_arv( t, no, raiz, ch);
        return;
    }
}