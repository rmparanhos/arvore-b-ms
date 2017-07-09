#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arqn = 1;
#define TAM 13
#define ERROR "arqnotfound-" // utilizado para retornar nas funçoes no lugar de NULL
#define RAIZ "arqsaved.dat"

int comp(const void *elem1, const void *elem2);

void cria_arv(int t, char *nome);
char* busca_arv(int t, char *no, int ch);
void imprime_arv(int t, char *no, int andar);

void insere_arv(int t, char *no, int ch);
void divide(int t, char *no, int ch);
// void insere_nao_completo_arv(int t, char *nome, int ch);
void insere_arv_agressivo(int t, char *raiz, int ch);
void libera_arv(int t, char *raiz);

void lerNoC(int t, char *nome); // printa tudo dentro do arquivo "nome"
void lerNoS(int t, char *nome,int andar); // printa so as chaves dentro do arquivo "nome"
int eFolha(int t, char *no);
void limpa_arq(char *nome); // reseta o arquivo, e deixa pronto pra ser usado de novo
int pos_arq(int t, int i); // retorna a posicao do nome do arquivo filho desejado
void inicializa_arv(int t, char *nome, int raiz); // funcaoo so pra testar inicializacao
char* busca_pai(int t, char *no); //busca pai e retorna o proprio no caso seja raiz, retorna ERROR se o no nao pertence a arvore
char* busca_pai_aux(int t, char *aux, char *no); //auxiliar

int main(void) {
    int t, val, boolean;
    char raiz[TAM];
    FILE *fp = fopen(RAIZ,"rb");
    if(!fp){
        printf("Arvore nao encontrada\n");
        printf("Deseja inicia-la com qual valor de t e qual valor de raiz?\n");
        scanf("%d",&t);
        scanf("%d",&val);
        insere_arv(t,"arq00000.dat",val);
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
    //divide(t, "arq00000.dat");
    while(1){
        printf("Digite 1 para inserir na arvore\n");
        printf("Digite 2 para imprimir a arvore\n");
        printf("Digite 3 para remover um elemento\n");
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
            insere_arv(t, raiz, val);
            FILE *f1 = fopen(RAIZ,"rb");
            if(!f1)exit(1);
            fread(&raiz, sizeof(char), TAM, f1);
            fclose(f1);
        }else if(boolean == 2){
            imprime_arv(t, raiz, 0);
        }else if(boolean == 3){
            //deleta arvore
            printf("Nao implementado\n");
        }else if(boolean == 4) {
            libera_arv(t, raiz);
            limpa_arq(raiz);
            limpa_arq(RAIZ);
            break;
        }else if(boolean == 5){
            printf("Que valor voce deseja buscar? ");
            scanf("%d", &val);
            printf("\n");
            char no[TAM];
            strcpy(no,busca_arv(t,raiz,val));
            if(strcmp(no, ERROR)){
                printf("Valor esta no no %s\n",no);
                printf("Leitura deste no:\n");
                lerNoC(t,no);
                printf("\n");
            }else{
                printf("No nao pertence a arvore!\n");
            }

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
}

// LER NO
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



// LER NO (SO AS CHAVES)
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

// POSICAO NO ARQUIVO
int pos_arq(int t, int i) {
    int pos = 2*t * sizeof(int);
    return pos + (TAM * i * sizeof(char));
}

char* busca_pai(int t, char *no){
    FILE *fsave = fopen(RAIZ, "rb");
    if(!fsave)exit(1);
    char *saida = (char*)malloc(sizeof(char)*TAM);
    char raiz[TAM], nome[TAM];
    fread(&raiz, sizeof(char), TAM, fsave);
    fclose(fsave);
    if(!strcmp(raiz, no)){
        strcpy(saida, no);
        return saida;
    }
    FILE *fp = fopen(raiz, "rb");
    if(!fp)exit(1);
    int pos, nchaves, i;
    fseek(fp, 0, SEEK_SET);
    fread(&nchaves, sizeof(int), 1, fp);
    for(i = 0;i < t*2; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        if(!strcmp(nome, no)){
            fclose(fp);
            strcpy(saida, raiz);
            return saida;
        }
    }
    char str[TAM];
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        fclose(fp);
        strcpy(str,busca_pai_aux(t, nome, no));
        fp = fopen(raiz, "rb");
        if(strcmp(str, ERROR)){
            fclose(fp);
            strcpy(saida, str);
            return saida;
        }
    }
    //Isso nunca pode acontecer se no faz parte da arvore
    fclose(fp);
}

char* busca_pai_aux(int t, char *aux, char *no){
    FILE *fp = fopen(aux, "rb");
    if(!fp)return ERROR;
    int pos, nchaves, i;
    char nome[TAM];
    char *saida = (char*)malloc(sizeof(char)*TAM);
    fread(&nchaves, sizeof(int), 1, fp);
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        if(!strcmp(nome, no)){
            fclose(fp);
            strcpy(saida, aux);
            return saida;
        }
    }
    char str[TAM];
    for(i = 0;i <= nchaves; i++){
        pos = pos_arq(t, i);
        fseek(fp, pos, SEEK_SET);
        fread(&nome, sizeof(char), TAM, fp);
        fclose(fp);
        strcpy(str,busca_pai_aux(t, nome, no));
        fp = fopen(aux, "rb");
        if(strcmp(str, ERROR)){
            fclose(fp);
            strcpy(saida, str);
            return saida;
        }
    }
    //Isso pode acontecer, significa que nao foi encontrado nos filhos de baixo
    fclose(fp);
    strcpy(saida, ERROR);
    return saida;
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
    fclose(fp);
    return busca_arv(t , str, ch);
}

// IMPRIME
void imprime_arv(int t, char *no, int andar) {
    FILE *fp = fopen(no, "rb");
    if (!fp) return;

    int i, j, nchaves;
    char filho[TAM];

    fread(&nchaves, sizeof(int), 1, fp);
    int vetChaves[nchaves];
    fread(&vetChaves,sizeof(int),nchaves,fp);
    for(i = 0;i <= nchaves-1; i++) {
        fseek(fp, pos_arq(t, i), SEEK_SET);
        fread(&filho, sizeof(char), TAM, fp);
        imprime_arv(t, filho, andar+1);
        if(!eFolha(t,no)){
            for(j = 0; j <= andar; j++) printf("   ");
            printf("%d\n", vetChaves[i]);
        }
    }
    fclose(fp);
    if(eFolha(t,no)){
        lerNoS(t, no, andar);
    }

    printf("\n");
    fp = fopen(no, "rb");
    if (!fp) return;
    fseek(fp, pos_arq(t, i), SEEK_SET);
    fread(&filho, sizeof(char), TAM, fp);
    imprime_arv(t, filho, andar+1);
    fclose(fp);
}

int comp(const void *elem1, const void *elem2) {
    int f = *((int*) elem1);
    int s = *((int*) elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

// DIVISAO
void divide(int t, char *no, int ch) {
    char str1[TAM], str2[TAM], ci[6];
    sprintf(ci, "%05d", arqn);
    arqn++;
    strcpy(str1, "arq");
    strcat(str1, ci);
    strcat(str1, ".dat");
    sprintf(ci, "%05d", arqn);
    arqn++;
    strcpy(str2, "arq");
    strcat(str2, ci);
    strcat(str2, ".dat");
    inicializa_arv(t, str1, 0);
    inicializa_arv(t, str2, 0);
    FILE *ff1 = fopen(str1, "rb+");
    FILE *ff2 = fopen(str2, "rb+");
    FILE *fp = fopen(no, "rb");
    if(!ff1 || !ff2 || !fp)exit(1);
    int size = (t*2 -1)/2;
    int i, vet[size];
    fseek(fp, sizeof(int), SEEK_SET);
    fread(&vet, sizeof(int), size, fp);
    fwrite(&size, sizeof(int), 1, ff1);
    fwrite(&vet, sizeof(int), size, ff1);
    fseek(fp, sizeof(int), SEEK_CUR);
    fread(&vet, sizeof(int), size, fp);
    fwrite(&size, sizeof(int), 1, ff2);
    fwrite(&vet, sizeof(int), size, ff2);
    int pos = pos_arq(t, 0);
    fseek(ff1, pos, SEEK_SET);
    fseek(ff2, pos, SEEK_SET);
    char temp[TAM];
    for(i = 0; i < size+1; i++){
        fread(&temp, sizeof(char), TAM, fp);
        fwrite(&temp, sizeof(char), TAM, ff1);
    }
    for(i = 0; i < size+1; i++){
        fread(&temp, sizeof(char), TAM, fp);
        fwrite(&temp, sizeof(char), TAM, ff2);
    }
    fclose(ff1);
    fclose(ff2);
    //str1 = novo filho da esquerda
    //str2 = novo filho da direita
    fseek(fp, sizeof(int) + sizeof(int)*size, SEEK_SET);
    int novoElem;
    fread(&novoElem, sizeof(int), 1, fp);
    fclose(fp);
    strcpy(temp, busca_pai(t, no));
    char raiz[TAM];
    FILE *fsave = fopen(RAIZ, "rb+");
    if(!fsave)exit(1);
    fread(&raiz, sizeof(char), TAM, fsave);
    if(!strcmp(raiz, no)){
        char novaRaiz[TAM];
        sprintf(ci, "%05d", arqn);
        arqn++;
        strcpy(novaRaiz, "arq");
        strcat(novaRaiz, ci);
        strcat(novaRaiz, ".dat");
        fseek(fsave, 0, SEEK_SET);
        fwrite(&novaRaiz, sizeof(char), TAM, fsave);
        fclose(fsave);
        inicializa_arv(t, novaRaiz, novoElem);
        FILE *fnova = fopen(novaRaiz, "rb+");
        if(!fnova)exit(1);
        fseek(fnova, pos, SEEK_SET);
        fwrite(&str1, sizeof(char), TAM, fnova);
        fwrite(&str2, sizeof(char), TAM, fnova);
        fclose(fnova);
        remove(no);
        return insere_arv(t, novaRaiz, ch);
    }
    //Talvez tenha erro aqui(ph) - acho q nao (ff)
    fclose(fsave);
    FILE *fpai = fopen(temp, "rb+");
    if(!fpai)exit(1);
    int nchaves;
    fread(&nchaves, sizeof(int), 1, fpai);
    int vetor[nchaves+1];
    fread(&vetor, sizeof(int), nchaves, fpai);
    vetor[nchaves] = novoElem;
    qsort(vetor, nchaves+1, sizeof(int), comp);
    fseek(fpai, sizeof(int), SEEK_SET);
    fwrite(&vetor, sizeof(int), nchaves+1, fpai);
    nchaves++;
    fseek(fpai, 0, SEEK_SET);
    fwrite(&nchaves, sizeof(int), 1, fpai);

    fseek(fpai, sizeof(int), SEEK_SET);
    int aux;
    for(i = 0; i < nchaves; i++){
        fread(&aux, sizeof(int), 1, fpai);
        if(aux == novoElem)break;
    }
   // printf("%d\n", aux);
   // printf("%d\n", i);
    if(i == nchaves-1){
        pos = pos_arq(t, i);
        fseek(fpai, pos, SEEK_SET);
        fwrite(&str1, sizeof(char), TAM, fpai);
        fwrite(&str2, sizeof(char), TAM, fpai);
        fseek(fpai, sizeof(int), SEEK_SET);
    }else{
        //O ERRO ESTA AQUI (ph) - resolvido (ff)
        pos = pos_arq(t, 0);
        char mat[nchaves+1][TAM];
        char m[TAM];
        int j;
        fseek(fpai,pos,SEEK_SET); // FALTOU ISSO LEK (ff)
        for(j = 0; j < nchaves+1;j++){
            fread(&m, sizeof(char), TAM, fpai);
            strcpy(mat[j],m);
        }
        pos = pos_arq(t, 0);
        fseek(fpai, pos, SEEK_SET);
        strcpy(mat[i], str1);
        for(j=nchaves;j > i;j--){
            strcpy(mat[j],mat[j-1]);
        }
        strcpy(mat[i+1],str2);
        for(i = 0;i < nchaves+1;i++){
            strcpy(m, mat[i]);
            fwrite(&m, sizeof(char), TAM, fpai);
        }
        //O ERRO ESTA AQUI EM CIMA ^^^^^^^^^^ (ph)- resolvido(ff)
    }
    fseek(fpai,sizeof(int),SEEK_SET); //faltou isso(ff)
    for(i = 0; i < nchaves; i++){
        fread(&aux, sizeof(int), 1, fpai);
        if(ch < aux)break;
    }
    pos = pos_arq(t, i);
    fseek(fpai, pos, SEEK_SET);
    fread(&temp, sizeof(char), TAM, fpai);
    fclose(fpai);
    remove(no);
    return insere_arv(t, temp, ch);
}

// INSERE
void insere_arv(int t, char *raiz, int ch){
    FILE *fp = fopen(raiz, "rb+");
    if(!fp){
        inicializa_arv(t, raiz, ch);
        return;
    }
    int nchaves;
    fread(&nchaves, sizeof(int), 1, fp);
    fclose(fp);
    if(nchaves == (t * 2)- 1){
        return divide(t, raiz, ch);
    }
    if(eFolha( t, raiz)){
        fp = fopen( raiz, "rb+");
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
        int i, aux1, aux2;
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
                insere_arv( t, no, ch);
                return;
            }
        }
        pos = pos_arq( t, i);
        fseek(fp, pos, SEEK_SET);
        char no[TAM];
        fread(&no, sizeof(char), TAM, fp);
        fclose(fp);
        insere_arv( t, no, ch);
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
