#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arqn = 1;
#define TAM 13
#define ERROR "arqnotfound-" // utilizado para retornar nas funções no lugar de NULL
#define RAIZ "arqsaved.dat"

int comp(const void *elem1, const void *elem2);

void cria_arv(int t, char *nome);
char* busca_arv(int t, char *no, int ch);
void imprime_arv(int t, char *no, int andar);

void insere_arv(int t, char *no, char *pai, int ch);
void divisao_arv(int t, char *no, char *pai);
// void insere_nao_completo_arv(int t, char *nome, int ch);
void insere_arv_agressivo(int t, char *raiz, int ch);
void libera_arv(int t, char *raiz);

void lerNoC(int t, char *nome); // printa tudo dentro do arquivo "nome"
void lerNoS(int t, char *nome,int andar); // printa só as chaves dentro do arquivo "nome"
int eFolha(int t, char *no);
void limpa_arq(char *nome); // reseta o arquivo, e deixa pronto pra ser usado de novo
int pos_arq(int t, int i); // retorna a posição do nome do arquivo filho desejado
void inicializa_arv(int t, char *nome, int raiz); // função só pra testar inicialização
char* busca_pai(int t, char *no); //busca pai e retorna o próprio no caso seja raiz, retorna ERROR se o no não pertence a arvore
char* busca_pai_aux(int t, char *aux, char *no); //auxiliar
char* busca_avo(int t, char *no); //busca avo e retorna no caso não tenha avo


int main(void) {
    int t, val, boolean;
    char raiz[TAM];
    /*int x;
    char c;
    char *aux;
    char *nome_raiz = (char*) malloc(sizeof(char) * TAM);
    strcpy(nome_raiz, "aqr00000.dat");
    while (1) {
        printf("t: ");
        scanf("%d", &t);
        if (t > 1) break;
    }
    while (1) {
        printf("I (inserir) / R (retirar) / B (buscar) / P (imprimir) / L (liberar) / S (sair): ");
        scanf(" %c", &c);
        if (c == 'S' || c == 's') break;
        else if (c == 'I' || c == 'i') {
            printf("Valor: ");
            scanf("%d", &x);
            // insere x
        }
        else if (c == 'R' || c == 'r') {
            printf("Valor: ");
            scanf("%d", &x);
            // retira x
        }
        else if (c == 'B' || c == 'b') {
            printf("Valor: ");
            scanf("%d", &x);
            aux = busca_arv(t, nome_raiz, x);
            lerNoC(t, aux);
        }
        else if (c == 'P' || c == 'p') {
            imprime_arv(t, nome_raiz, 0);
        }
        else if (c == 'L' || c == 'l') {
            // libera arv
        }
    }
    /*****/
    FILE *fp = fopen(RAIZ,"rb");
    if(!fp){
        printf("Arvore nao encontrada\n");
        printf("Deseja inicia-la com qual valor de t e qual valor de raiz?\n");
        scanf("%d",&t);
        scanf("%d",&val);
        insere_arv(t,"arq00000.dat",NULL,val);
        FILE *fp = fopen(RAIZ,"wb");
        if(!fp)exit(1);
        strcpy(raiz,"arq00000.dat");
        fwrite(&raiz, sizeof(char), TAM, fp);
        fwrite(&t, sizeof(int), 1, fp);
        fwrite(&arqn, sizeof(int), 1, fp);
        fclose(fp);
    }
    else{
        printf("Arvore encontrada\n");
        fread(&raiz, sizeof(char), TAM, fp);
        fread(&t, sizeof(int), 1, fp);
        fread(&arqn, sizeof(int), 1, fp);
        fclose(fp);
    }
    while(1){
        printf("Digite 1 para inserir na arvore\n");
        printf("Digite 2 para imprimir a arvore\n");
        printf("Digite 3 para deletar a arvore\n");
        printf("Digite 4 para limpar a arvore\n");
        printf("Digite 5 para busca um valor\n");
        printf("Digite qualquer outro valor para sair\n");
        printf("Do it: ");
        scanf("%d", &boolean);
        printf("\n");
        if(boolean == 1){
            printf("Que valor voce deseja inserir? ");
            scanf("%d", &val);
            printf("\n");
            insere_arv(t, raiz, NULL, val);
            FILE *f1 = fopen(RAIZ,"rb");
            if(!f1)exit(1);
            fread(&raiz, sizeof(char), TAM, f1);
            fclose(f1);
        }else if(boolean == 2){
            imprime_arv(t, raiz, 0);
        }else if(boolean == 3){
            //deleta arvore
            printf("Nao implemntado\n");
        }else if(boolean == 4) {
            libera_arv(t, raiz);
            limpa_arq(RAIZ);
            _fcloseall();
            limpa_arq(raiz);
            break;
        }else if(boolean == 5){
            printf("Que valor voce deseja buscar? ");
            scanf("%d", &val);
            printf("\n");
            char no[TAM];
            strcpy(no,busca_arv(t,raiz,val));
            printf("Valor esta no no %s\n",no);
            printf("Leitura deste no:\n");
            lerNoC(t,no);
            printf("\n");
        }else{
            printf("Fechando arquivo e atualizando save\n");
            FILE *f2 = fopen(RAIZ,"rb+");
            if(!f2)exit(1);
            int pos = TAM * sizeof(char);
            fseek(f2, pos + sizeof(int), SEEK_SET);
            fwrite(&arqn, sizeof(int), 1, f2);
            fclose(f2);
            printf("Done\n");
            break;
        }
    }

   /* insere_arv(2,RAIZ,NULL,6);
    imprime_arv(2,RAIZ,0);*/
   /* insere_arv(2,RAIZ,NULL,10);
    imprime_arv(2,RAIZ,0);
    insere_arv(2,RAIZ,NULL,15);
    imprime_arv(2,RAIZ,0);
    printf("\n---------------\n");
    insere_arv(2,RAIZ,NULL, 5);
    lerNoC(t, "arq00000.dat");
    printf("\n");
    lerNoC(t, "arq00007.dat");
    printf("\n");
    lerNoC(t, "arq00010.dat");
    printf("\n----------------\n");
    insere_arv(2,RAIZ,NULL, 20);
    imprime_arv(2,RAIZ,0);
    insere_arv(2,RAIZ,NULL, 40);
    imprime_arv(2,RAIZ,0);
    insere_arv(2,RAIZ,NULL, 50);
    printf("-----------\n");
    imprime_arv(2,RAIZ,0);
    insere_arv(2,RAIZ,NULL, 60);
    imprime_arv(2,RAIZ,0);*/
   /* insere_arv(2,"arq00000.dat",NULL, 9); // nao funciona por causa do preemptive split
    printf("-----------\n");
    lerNoC(t, "arq00000.dat");
    printf("\n");
    lerNoC(t, "arq00001.dat");
    printf("\n");
    lerNoC(t, "arq00002.dat");
    printf("\n");
    lerNoC(t, "arq00003.dat");
    printf("\n");
    lerNoC(t, "arq00004.dat");
    printf("\n");
    //insere_arv(2,"arq00000.dat",4); // funciona mas descaralha o nchaves
    //insere_arv(2,"arq00000.dat",5); // descaralha a porra toda
    //lerNoC(t, "arq00000.dat");
    //printf("\n");
    //lerNoC(t, "arq00001.dat");
    //printf("\n");
    //lerNoC(t, "arq00002.dat");
    //printf("\n");*/

    //Exemplo de uso do Busca e do ERROR
    /*char *nome = (char*) malloc(sizeof(char) * TAM);
    strcpy(nome, busca_arv(t, "raiz.dat", 44));
    if (strcmp(nome, ERROR)) printf("%s", nome);
    */
}

// LER NÓ
void lerNoC(int t, char *nome) {
    FILE *fp = fopen(nome, "rb");
    if (!fp) exit(1);
    int i, elem;
    char str[TAM];

    for (i = 0; i < 2*t; i++) {
        fread(&elem, sizeof(int), 1, fp);
        printf("%d\n", elem);
    }

    for (i = 0; i < 2*t; i++) {
        fread(&str, sizeof(char), TAM, fp);
        printf("%s\n", str);
    }

    fclose(fp);
}



// LER NÓ (SÓ AS CHAVES)
void lerNoS(int t, char *nome,int andar) {
    FILE *fp = fopen(nome, "rb");
    if (!fp) return;

    int i, j, elem;
    fseek(fp, sizeof(int), SEEK_SET);

    for(i = 0; i < 2*t - 1; i++) {
        fread(&elem, sizeof(int), 1, fp);
        if (elem != -1) {
            for(j = 0; j <= andar; j++) printf("   ");
            printf("%d\n", elem);
        }
    }

    fclose(fp);
}

// FOLHA
int eFolha(int t, char *no) {
    FILE *fp = fopen(no, "rb");
    if (!fp)return 1;

    int nchaves, i;
    int pos = pos_arq(t, 0);
    fread(&nchaves, sizeof(int), 1, fp);
    fseek(fp, pos, SEEK_SET);
    char filho[TAM];

    for(i = 0; i < nchaves+1; i++) {
        fread(&filho, sizeof(char), TAM, fp);
        FILE *ff = fopen(filho, "rb");

        if (ff) {
            fclose(ff);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

// LIMPA ARQ
void limpa_arq(char *nome) {
    FILE *fp = fopen(nome, "rb");
    if (!fp) return;
    fclose(fp);
    remove(nome);
}

// POSIÇÃO NO ARQUIVO
int pos_arq(int t, int i) {
    int pos = 2*t * sizeof(int);
    return pos + (TAM * i * sizeof(char));
}

char* busca_pai(int t, char *no){
    FILE *fsave = fopen(RAIZ, "rb");
    if(!fsave)exit(1);
    char raiz[TAM], nome[TAM];
    fread(&raiz, sizeof(char), TAM, fsave);
    fclose(fsave);
    if(!strcmp(raiz, no)){
        return no;
    }
    FILE *fp = fopen(raiz, "rb");
    if(!fp)exit(1);
    int pos, nchaves, i;
    fread(&nchaves, sizeof(int), 1, fp);
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        if(!strcmp(nome, no)){
            fclose(fp);
            return raiz;
        }
    }
    char saida[TAM];
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        strcpy(saida,busca_pai_aux(t, nome, no));
        if(strcmp(saida, ERROR)){
            fclose(fp);
            return saida;
        }
    }
    //Isso nunca pode acontecer se no faz parte da arvore
    return ERROR;
}

char* busca_pai_aux(int t, char *aux, char *no){
    FILE *fp = fopen(aux, "rb");
    if(!fp)return ERROR;
    int pos, nchaves, i;
    char nome[TAM];
    fread(&nchaves, sizeof(int), 1, fp);
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        if(!strcmp(nome, no)){
            fclose(fp);
            return aux;
        }
    }
    char saida[TAM];
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        strcpy(saida,busca_pai_aux(t, nome, no));
        if(strcmp(saida, ERROR)){
            fclose(fp);
            return saida;
        }
    }
    //Isso pode acontecer, significa que não foi encontrado nos filhos de baixo
    return ERROR;
}

char* busca_avo(int t, char *no){
    char nome[TAM], saida[TAM];
    strcpy(nome, busca_pai(t, no));
    if(!strcmp(nome, ERROR)){
        //Deu merda
        //Tem algum erro no busca_pai ou o no não pertence a arvore
        return no;
    }
    if(!strcmp(nome, no)){
        //Ele é a raiz e não tem pai;
        return nome;
    }else{
        //Achou o pai!
        //Agora buscar o pai do pai;
        //Retorna ele mesmo se não tiver avo e for a raiz;
        strcpy(saida, busca_pai(t, nome));
        if(!strcmp(saida, ERROR)){
            //Se entrar aqui, é pq o no não faz parte da arvore ou tem algum erro em um desses busca pai e avo
            //retorna o próprio no, indicando que não tem avo
            //se retornasse o "nome", que é um pai válido, não seria possível dizer se "nome" é avo ou não, fora dessa função
            //seria preciso usar outro busca_pai;
            //Lembrar de usar STRCMP com a saida dessa função, para verificar se é um avo ou não
            return no;
        }
        //Achou o avo!
        return saida;
    }
}

// INICIALIZA
void inicializa_arv(int t, char *nome, int raiz) {
    FILE *fp = fopen(nome, "wb");
    if (!fp) exit(1);

    int n1 = 1, e = -1, i;
    fwrite(&n1, sizeof(int), 1, fp);
    fwrite(&raiz, sizeof(int), 1, fp);

    for(i = 0; i < 2*t - 2; i++)
        fwrite(&e, sizeof(int), 1, fp);

    char str[TAM], ci[6];

    for(i = 0; i < 2*t; i++) {
        sprintf(ci, "%05d", arqn);
        arqn++;
        strcpy(str, "arq");
        strcat(str, ci);
        strcat(str, ".dat");
        fwrite(&str, sizeof(char), TAM, fp);
    }
    fclose(fp);
}

// CRIA
void cria_arv(int t, char *nome) {
    FILE *fp = fopen(nome, "wb");
    if (!fp) exit(1);

    int e = -1, i = 0;
    fwrite(&i, sizeof(int), 1, fp);
    for(i = 0; i < (2 * t)-1; i++)
        fwrite(&e, sizeof(int), 1, fp);

    char str[TAM], ci[6];
    for(i = 0; i < 2*t; i++) {
        sprintf(ci, "%05d", arqn);
        arqn++;
        strcpy(str, "arq");
        strcat(str, ci);
        strcat(str, ".dat");
        fwrite(&str, sizeof(char), TAM, fp);
    }
    fclose(fp);
}

// BUSCA
char *busca_arv(int t, char *no, int ch) { // no = raiz
    FILE *fp = fopen(no, "rb");
    if (!fp) return ERROR;

    int nchaves, i = 0;

    fread(&nchaves, sizeof(int), 1, fp);
    if (!nchaves) {
        fclose(fp);
        return ERROR;
    }

    int chaves[nchaves];
    fread(&chaves, sizeof(int), nchaves, fp);

    while(i < nchaves && ch > chaves[i])i++;
    if (i < nchaves && ch == chaves[i])return no;

    fclose(fp);
    if (eFolha(t, no))return ERROR;
    fp = fopen(no, "rb");

    int pos = pos_arq(t, i);

    fseek(fp, pos, SEEK_SET);
    char str[TAM];
    fread(&str, sizeof(char), TAM, fp);
    return busca_arv(t , str, ch);
}

// IMPRIME
void imprime_arv(int t, char *no, int andar) {
    FILE *fp = fopen(no, "rb");
    if (!fp) return;

    int i, j, nchaves;
    char filho[TAM];

    fread(&nchaves, sizeof(int), 1, fp);
    for(i = 0;i <= nchaves-1; i++) {
        fseek(fp, pos_arq(t, i), SEEK_SET);
        fread(&filho, sizeof(char), TAM, fp);
        imprime_arv(t, filho, andar+1);




    }
    fclose(fp);
    lerNoS(t, no, andar);

    fp = fopen(no, "rb");
    if (!fp) return;

    fseek(fp, pos_arq(t, i), SEEK_SET);
    fread(&filho, sizeof(char), TAM, fp);
    imprime_arv(t, filho, andar+1);

    fclose(fp);
}

/*TAB *Insere(TAB *T, int k, int t) {
  if (Busca(T,k)) return T;
  if (!T) {
    T=Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T;
  }
  if (T->nchaves == (2*t)-1) {
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
void insere_arv(int t, char *no, int ch) { //no = raiz
	if (strcmp(ERROR, busca_arv(t, no, ch))) {
        return;
    }
	FILE *fp = fopen(no, "rb+");
    if (!fp) {
		inicializa_arv(t, no, ch);
		return;
	}
    if (eFolha(t,no)) {
        int nchaves;
        fread(&nchaves,sizeof(int),1,fp);
        if (nchaves + 1 <= (2*t)-1) {
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
                if (aux < meio) {
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
                    if (nchaves < 1) {
                        nchaves = 1;
                    }
                    fseek(fp,0,SEEK_SET);
                    fwrite(&nchaves,sizeof(int),1,fp);
                    fclose(fp);
                    reorganiza(t,no);
                    insere_arv(t,nome,aux);
                }
                else if (aux > meio) {
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
                    if (nchaves < 1) {
                        nchaves = 1;
                    }
                    fseek(fp,0,SEEK_SET);
                    fwrite(&nchaves,sizeof(int),1,fp);
                    fclose(fp);
                    reorganiza(t,no);
                    insere_arv(t,nome,aux);
                }
                if (cont == (2*t)-1 ) {
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
        for (i = 1; i < (2 * t) - 1; i++) {
            if (ch > aux && (ch < aux2 || aux2 == -1)) {
                int pos = pos_arq(t, i);
                fseek(fp, pos, SEEK_SET);
                char nome[TAM];
                fread(&nome, sizeof(char) * TAM, 1, fp);
                insere_arv(t, nome, ch);
            }
            else if (ch<aux) {
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

/* void reorganiza(int t,char* no) {
    FILE *fp =fopen(no,"rb+");
    if (!fp) exit(1);
    int vet[(2*t)-1];
    fseek(fp,sizeof(int),SEEK_SET);
    fread(&vet,sizeof(int),(2*t)-1,fp);
    for (int i = 0; i <(2*t)-1 ; ++i) {
        for (int j = i + 1; j < (2*t)-1; ++j) {
            if (vet[i]==-1 && vet[j]!=-1) {
                vet[i] = vet[j];
                vet[j] = -1;
            }
        }
    }
    fseek(fp,sizeof(int),SEEK_SET);
    fwrite(&vet,sizeof(int),(2*t)-1,fp);
    fclose(fp);
} */

/* int descobreMeio(char* no,int ch,int t) {
    FILE *fp = fopen(no,"rb");
    if (!fp) return -1;
    int meio[(2*t)-1], aux;
    int i, trigger = 1;
    for(i=0;i<3;i++) {
        fseek(fp, i*sizeof(int) + 4, SEEK_SET);
        fread(&aux, sizeof(int), 1, fp);
        if (i==2) {
            meio[i] = ch;
        }
        else{
            meio[i] = aux;
        }
    }
    qsort(meio,(2*t)-1,sizeof(int),comp);
    return meio[((2*t)-1)/2];
} */


int comp(const void *elem1, const void *elem2) {
    int f = *((int*) elem1);
    int s = *((int*) elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

// DIVISÃO
char* divide(int t, char *no, char *pai) {
    FILE *fp = fopen(no,"rb+");
    if (!fp);
    int i;

    if (!pai) {
        // if é raiz ou seja, pai == null
        //temos uma nova raiz
        //altura da arvore vai aumentar
        //arvore precisara ser reestruturada
        int vet[3];
        int nchaves = 1;
        fseek(fp,sizeof(int),SEEK_SET);
        fread(vet,sizeof(int),3,fp);

        int vetEsq[3];
        vetEsq[0] = vet[0];
        int vetDir[3];
        vetDir[0] = vet[2];
        int vetRaiz[3];
        vetRaiz[0] = vet[1];
        for (int j = 1; j < 3; ++j) {
            vetEsq[j] = -1;
            vetDir[j] = -1;
            vetRaiz[j] = -1;
        }
        //raiz original
        fseek(fp,0,SEEK_SET);
        fwrite(&nchaves,sizeof(int),1,fp);
        fwrite(vetEsq,sizeof(int),3,fp);
        int pos = pos_arq(t,2);
        fseek(fp,pos,SEEK_SET);
        char arq3[TAM],arq4[TAM];
        fread(arq3,sizeof(char),TAM,fp);
        fread(arq4,sizeof(char),TAM,fp);
        fseek(fp,pos,SEEK_SET);
        char str[TAM], ci[6];
        for(i = 2; i < 2*t; i++) {
            sprintf(ci, "%05d", arqn);
            arqn++;
            strcpy(str, "arq");
            strcat(str, ci);
            strcat(str, ".dat");
            fwrite(&str, sizeof(char), TAM, fp);
        }
        //novo nó
        char novoNo[TAM], ci2[6];
        sprintf(ci2, "%05d", arqn);
        arqn++;
        strcpy(novoNo, "arq");
        strcat(novoNo, ci2);
        strcat(novoNo, ".dat");
        FILE *fpNovo = fopen(novoNo,"wb+");
        if(!fpNovo) exit(1);
        nchaves;
        fwrite(&nchaves,sizeof(int),1,fpNovo);
        fwrite(vetDir,sizeof(int),3,fpNovo);
        fwrite(arq3,sizeof(char),TAM,fpNovo);
        fwrite(arq4,sizeof(char),TAM,fpNovo);
        for(i = 2; i < 2*t; i++) {
            sprintf(ci2, "%05d", arqn);
            arqn++;
            strcpy(str, "arq");
            strcat(str, ci2);
            strcat(str, ".dat");
            fwrite(&str, sizeof(char), TAM, fpNovo);
        }
        //nova raiz
        char novaRaiz[TAM], ci3[6];
        sprintf(ci3, "%05d", arqn);
        arqn++;
        strcpy(novaRaiz, "arq");
        strcat(novaRaiz, ci3);
        strcat(novaRaiz, ".dat");
        FILE *fpNovoRaiz = fopen(novaRaiz,"wb+");
        if(!fpNovoRaiz) exit(1);
        fwrite(&nchaves,sizeof(int),1,fpNovoRaiz);
        fwrite(vetRaiz,sizeof(int),3,fpNovoRaiz);
        fwrite(no,sizeof(char),TAM,fpNovoRaiz);
        fwrite(novoNo,sizeof(char),TAM,fpNovoRaiz);
        for(i = 2; i < 2*t; i++) {
            sprintf(ci3, "%05d", arqn);
            arqn++;
            strcpy(str, "arq");
            strcat(str, ci3);
            strcat(str, ".dat");
            fwrite(&str, sizeof(char), TAM, fpNovoRaiz);
        }
        fclose(fp);
        fclose(fpNovo);
        fclose(fpNovoRaiz);

        FILE *fsave = fopen(RAIZ, "rb+");
        if(!fsave)exit(1);
        fwrite(&novaRaiz, sizeof(char), TAM, fsave);
        fclose(fsave);

        return novaRaiz;
    }
    else{
        int nchaves;
        fread(&nchaves, sizeof(int), 1, fp);
        int vet[nchaves], aux[nchaves];
        int zeroChaves = 0;

        int i;
        for (i = 0; i < nchaves; i++)
            aux[i] = -1;

        fread(vet, sizeof(int), nchaves, fp);
        fseek(fp, 0, SEEK_SET);
        fwrite(&zeroChaves,sizeof(int),1,fp);
        fwrite(aux,sizeof(int),nchaves,fp);
        fclose(fp);
        FILE *fpai = fopen(pai,"rb+");
        int nchavesPai;
        fread(&nchavesPai,sizeof(int),1,fpai);
        char filho[TAM];

        for(i = 0; i < nchaves; i++) {
            fp = fopen(no,"rb+");

            if (i == nchaves/2) {
                if (nchavesPai < 2*t - 1) {
                    fclose(fp);

                    insere_arv_agressivo(t, pai, vet[i]);
                }

                else {
                    char avo[TAM];
                    strcpy(avo,busca_avo(t,no));
                    insere_arv(t, pai, avo, vet[i]); // avo precisa ser implementado
                }
            }

            else if (i < nchaves/2) { //filho da esquerda do pai
                int pos = pos_arq(t,nchavesPai);
                fseek(fpai, pos, SEEK_SET);
                fread(filho, sizeof(char), TAM, fpai);
                fclose(fp);
                insere_arv(t, filho, pai, vet[i]);
            }

            else { //filho da direita do pai
                int pos = pos_arq(t, nchavesPai+1);
                fseek(fpai, pos, SEEK_SET);
                fread(filho,sizeof(char), TAM, fpai);
                fclose(fp);
                insere_arv(t, filho, pai, vet[i]);
            }
        }
    }
}

void insere_arv_agressivo(int t, char *raiz, int ch) {
    FILE *fp = fopen(raiz,"rb+");
    if (!fp) exit(1);
    int nchaves;
    fread(&nchaves, sizeof(int), 1, fp);
    fseek(fp, sizeof(int), SEEK_SET);
    int vet[nchaves+1];
    fread(&vet, sizeof(int), nchaves, fp);
    vet[nchaves] = ch;
    qsort(vet, nchaves+1, sizeof(int), comp);
    fseek(fp, sizeof(int), SEEK_SET);
    fwrite(&vet, sizeof(int), nchaves+1, fp);
    fseek(fp, 0, SEEK_SET);
    nchaves++;
    fwrite(&nchaves, sizeof(int), 1, fp);
    fclose(fp);
    return;

}

// INSERE
void insere_arv(int t, char *raiz, char*pai, int ch) {
    FILE *fp = fopen(raiz, "rb+");
    if (!fp) {
        inicializa_arv(t, raiz, ch);
        return;
    }
    int nchaves;
    fread(&nchaves, sizeof(int), 1, fp);
    if (nchaves == (t * 2)- 1) {
        fclose(fp);
        char novoPai[TAM];
        strcpy(novoPai,divide(t, raiz, pai));
        int i;
        FILE *fpai;
        if (!novoPai) {
            fpai = fopen(pai, "rb+");
            if (!fpai) exit(1);
        }
        else{
            fpai = fopen(novoPai,"rb+");
            if (!fpai) exit(1);
        }
        fread(&nchaves,sizeof(int),1,fpai);
        int vet[nchaves], pos;
        fread(&vet, sizeof(int), nchaves, fpai);
        for(i = 0; i < nchaves; i++) {
            if (ch < vet[i]) {
                pos = pos_arq(t, i);
                fseek(fpai, pos, SEEK_SET);
                char no[TAM];
                fread(&no, sizeof(char), TAM, fpai);
                fclose(fpai);
                insere_arv(t, no, pai, ch);
                return;
            }

        }
        pos = pos_arq(t, i);
        fseek(fpai, pos, SEEK_SET);
        char no[TAM];
        fread(&no, sizeof(char), TAM, fpai);
        fclose(fpai);
        insere_arv(t, no, pai, ch);
        return;
        insere_arv( t, raiz, pai, ch);
        return;
    }

    fclose(fp);

    if (eFolha(t, raiz)) {
        fp = fopen(raiz, "rb+");
        if (!fp)exit(1);
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

    else {
        int i;
        fp = fopen( raiz, "rb+");
        if (!fp) exit(1);

        fseek(fp, sizeof(int), SEEK_SET);
        int vet[nchaves], pos;
        fread(&vet, sizeof(int), nchaves, fp);
        for(i = 0; i < nchaves; i++) {
            if (ch < vet[i]) {
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


// LIBERA
void libera_arv(int t, char *raiz) {
    FILE *fp = fopen(raiz, "rb");
    if (!fp) return;

    int i;
    char filho[TAM];

    if (!eFolha(t, raiz)) {
        //fread(&nchaves, sizeof(int), 1, fp);
        fseek(fp, (t+1)*sizeof(int)+sizeof(int), SEEK_SET);

        for (i = 0; i < 2 * t; i++) {
            fread(&filho, sizeof(char), TAM, fp);
            libera_arv(t, filho);
        }
    }

    fclose(fp);
    limpa_arq(raiz);
}