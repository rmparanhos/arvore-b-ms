#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arqn = 1;
#define TAM 13
#define ERROR "arqnotfound-" //Utilizado para retornar nas funções no lugar de NULL
/*#define TEMP1 "arq_temp_in1" //Utilizado no insere
#define TEMP2 "arq_temp_in2"
*/
void cria_arv(int t, char *nome);
char *busca_arv(int t, char *no, int ch);
void imprime_arv(int t, char *no, int andar);
/*void *insere_arv(int t, char *no, int ch);
void divisao_arv(int t, char *s, int i, char *no);
void insere_nao_completo_arv(int t, char *nome, int ch);
*/
void lerNoC(int t, char *nome); //Printa tudo dentro do arquivo "nome"
void lerNoS(int t, char *nome); //Printa só as chaves dentro do arquivo "nome"
int eFolha(int t, char *no);
void limpaArq(int t, char *nome); //Reseta o arquivo, e deixa pronto pra ser usado de novo
int pos_arq(int t, int i); //Retorna a posição do nome do arquivo filho desejado
void inicializa_arv(int t, char *nome, int raiz); //Função só pra testar inicialização
//********************************************************************************************************
//********************************************************************************************************
int main(){
	int t = 2;
	inicializa_arv(t, "raiz.dat", 20); //Raiz
	lerNoC(t, "raiz.dat");
	inicializa_arv(t, "arq00001.dat", 10); //Esquerda
	lerNoC(t, "arq00001.dat");
	inicializa_arv(t, "arq00002.dat", 33); //Direita
	lerNoC(t, "arq00002.dat");
	//imprime_arv(t, "raiz.dat", 0);
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
		if(elem != -1){
			printf("%d\n", elem);
		}
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
	
	for(i = 0;i < nchaves; i++){
		fread(&filho, sizeof(char), TAM, fp);
		FILE *ff = fopen(filho, "rb");
		if(fp){
			int e;
			fread(&e, sizeof(int), 1, ff);
			if(e){
				fclose(ff);
				return 0;
			}
			fclose(ff);
		}
	}
	
	fclose(fp);
	return 1;
}

void limpaArq(int t, char *nome){
	FILE *fp = fopen(nome, "wb");
	if (!fp) exit(1);
	
	int e = -1, i = 0;
	fwrite(&i, sizeof(int), 1, fp);
	for(i = 0; i < (2 * t)-1; i++){
		fwrite(&e, sizeof(int), 1, fp);
	}
	
	fclose(fp);
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

char *busca_arv(int t, char *no, int ch){
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
void *insere_arv(int t, char *no, int ch){
	if(strcmp(ERROR, busca_arv(t, no, ch))) return no;
	
	FILE *fp = fopen(no, "rb+");
	if(!fp){
		inicializa_arv(t, no, ch);
		return;
	}
	
	int nchaves;
	fread(&nchaves, sizeof(int), 1, fp);
	
	if(nchaves == (2*t)-1){
		cria_arv(t, TEMP1);
		//divisao_arv
		//insere_nao_completo_arv
	}
	//insere_nao_completo
}*/
/*TAB *Divisao(TAB *x, int i, TAB* y, int t){
  TAB *z=Cria(t);
  z->nchaves= t - 1;
  z->folha = y->folha;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}

void divisao_arv(int t, char *x, int i, char *no){
	cria_arv(t, TEMP2);
	FILE *ft2 = fopen(TEMP2, "rb+");
	if(!ft2)return;
	FILE *fp = fopen(no, "rb+");
	if(!fp)return;
	fseek(fp, (t+1)*sizeof(int), SEEK_SET);
	
	int nchaves = t - 1, j, elem, e = -1;
	fwrite(&nchaves, sizeof(int), 1, fp);
	
	for(j = 0; j < t-1;j++){
		fread(&elem, sizeof(int), 1, fp);
		fwrite(&elem, sizeof(int), 1, ft2);
	}
	
	if(!eFolha(t, no)){
		fseek(ft2, (j+1)*sizeof(int), SEEK_SET);
		fseek(fp, (j + t)*sizeof(int), SEEK_SET);
		
		for(j=0;j<t;j++){
			fread(&elem, sizeof(int), 1, fp);
			fwrite(&elem, sizeof(int), 1, ft2);
			fseek(fp, (j + t)*sizeof(int), SEEK_SET);
			fwrite(&e, sizeof(int), 1, fp);
        }
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(&nchaves, sizeof(int), 1, fp);
	
	FILE *ft1 = fopen(x, "rb+");
	if(!ft1)return;
	
	int xnchaves = 0;
	
	for(j = xnchaves; i)
	for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
    x->chave[i-1] = y->chave[t-1];
    x->nchaves++;
    return x;
}*/
