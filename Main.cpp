#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include "ListaEncadeada.h"

// ------------------------------------------------------------------------------------------------------- //

#define TITLE "FeL486 C++ Software"
#define MAX_PROCESSOS 10

#define INVALID_DIVISOR "[ERRO]: Divisor invalido.\n\n"
#define INVALID_DIVIDENDO "[ERRO]: Dividendo invalido.\n\n"

// ------------------------------------------------------------------------------------------------------- //

typedef struct processo Processo;

struct processo {
	Lista** listas;
	int concluido;
};

Processo* processos[MAX_PROCESSOS];

// ------------------------------------------------------------------------------------------------------- //

char intToChar(int v)
{
	if (v >= 0 && v <= 9) return ((char)v) + 48;
}

int charToInt(char c)
{
	return ((int)c) - 48;
}

int isStringZero(char str[]) {
	for (int a = 0; a < strlen(str); a++) {
		if (str[a] != '0') return 0;
	}

	return 1;
}

char* listToString(Lista* l) {
	char* c = (char*)malloc(sizeof(char) * tamanho(l));
	int a;
	for (a = 0; a < tamanho(l); a++) {
		c[a] = ((char)ler_pos(l, a)) + 48;
	}

	c[a] = '\0';

	return c;
}

char* getStringAbsoluta(char str[])
{
	char* c = (char*)malloc(sizeof(char) * 50);
	int a, b;

	if (isStringZero(str) == 1)
	{
		c[0] = '0';
		c[1] = '\0';
		return c;
	}

	for (a = 0, b = 0; a < strlen(str); a++)
	{
		if (b == 0 && str[a] == '0') continue;

		c[b++] = str[a];
	}

	c[b] = '\0';

	return c;
}

char* getMaiorString(char* v1, char* v2)
{
	if (strcmp(v1, v2))
	{
		if (strlen(v1) > strlen(v2)) return v1;
		else if (strlen(v1) < strlen(v2)) return v2;
		else {

			for (int a = 0; a < (strlen(v1) > strlen(v2) ? strlen(v1) : strlen(v2)); a++)
			{
				if (charToInt(v1[a]) == charToInt(v2[a])) continue;
				if (charToInt(v1[a]) >= charToInt(v2[a])) return v1;
				else return v2;
			}
		}
	}
	else return v1;
}

Lista* getMaiorLista(Lista* L1, Lista* L2)
{
	if (L1 != NULL && L2 != NULL)
	{
		if (ler_pos(L1, 0) != 0)
		{
			//printf("[STRCMP]: COMPARANDO %s com %s\n", listToString(L1), getStringAbsoluta(listToString(L2)));
			if (!strcmp(getMaiorString(listToString((L1)), getStringAbsoluta(listToString((L2)))), listToString(L1))) return L1;
			else return L2;
		}
		else
		{
			//printf("COMPARANDO L1 com L2: %s ---> %s. MAIOR: %s\n", (listToString(L1)), (listToString(L2)), getMaiorString((listToString((L1))), (listToString((L2)))));
			if (!strcmp(getMaiorString((listToString((L1))), (listToString((L2)))), listToString(L1))) return L1;
			else return L2;
		}
	}
}

Lista* getListaAbsoluta(Lista* l)
{
	if (l != NULL && tamanho(l) > 0) {
		Lista* resultado = criar();

		for (int a = 0, b = 0; a < tamanho(l); a++)
		{
			if (b == 0 && ler_pos(l, a) == 0) continue;
			
			inserir_pos(resultado, b++, ler_pos(l, a));
		}

		return resultado;
	}
}

int areListsEquals(Lista* L1, Lista* L2)
{
	Lista* a1 = getListaAbsoluta(L1);
	Lista* a2 = getListaAbsoluta(L2);

	if (tamanho(a1) != tamanho(a2)) return 0;

	for (int a = 0; a < tamanho(a1); a++)
	{
		if (ler_pos(a1, a) != ler_pos(a2, a)) return 0;
	}

	return 1;
}

char* intToString(int v)
{
	char str[50];

	sprintf(str, "%d", v);

	return str;
}

Lista* stringToList(char* str)
{
	Lista* lista = criar();

	for (int p = 0; p < strlen(str); p++)
	{
		inserir_pos(lista, p, charToInt(str[p]));
	}

	return lista;
}

char* multiplicar(char* str, int valor)
{
	char* resultado = (char*)malloc(sizeof(char) * 50);
	char* Valor = (char*)malloc(sizeof(char) * 50);
	int a;
	int id;
	int resto = 0;

	for (a = 0; a < strlen(intToString(valor)) - 1; a++) Valor[a] = '0';
	/*
		---> Colocando os zeros para balancear.
				Exemplo: (1000*10) = 10000 (5 digitos)
				-----> 4 digitos + (2 digitos - 1 digito) = 5 digitos de resultado
	*/

	Valor[a] = '\0'; // Encerra a string
	strcat(Valor, str); // Junta à string balanceada o valor digitado a ser multiplicado.

	for (a = 0; a < (strlen(str) + strlen(intToString(valor))) - 1; a++) resultado[a] = '0';
	
	/*
		---> Adiciona os zeros à String de Resultado para balancear.

		Exemplo: 1000 * 10 = 10000 (5 digitos)

		[4 digitos (1000) + 2 digitos(10) - 1] = 5 digitos (resultado: 10000).
	*/

	resultado[a] = '\0'; // Encerra a string.


	for (a = 0, id = strlen(resultado) - 1; a < valor; id--) // Processo normal de soma.
	{
		/*
			---> valor = números de vezes a somar.
			---> strlen(resultado)-1 = última posição do resultado.
		*/

		resultado[id] = intToChar(charToInt(resultado[id]) + resto);

		if ((charToInt(resultado[id]) + charToInt(Valor[id])) < 10)
		{
			resultado[id] = intToChar(charToInt(resultado[id]) + charToInt(Valor[id]));
			resto = 0;
		}

		else
		{
			resultado[id] = intToChar(charToInt(resultado[id]) + charToInt(Valor[id]) - 10);
			resto = 1;
		}

		if (id == 0)
		{
			id = strlen(resultado);
			a++;
		}
	}	

	return resultado;

}

void multiplicar(Lista* l, int valor)
{
	if (l != NULL)
	{
		char* v = (char*)malloc(sizeof(char) * 50);
		int a;

		for (a = 0; a < tamanho(l); a++) v[a] = intToChar(ler_pos(l, a));
		v[a] = '\0';

		v = multiplicar(v, valor);

		limpar(l);

		for (a = 0; a < strlen(v); a++)
		{
			inserir_pos(l, a, charToInt(v[a]));
		}

		free(v);

	}
}

Lista* multiplicarPor10(Lista* lista)
{
	if (lista != NULL)
	{
		Lista* resultado = getListaAbsoluta(lista);		
		inserir_ultimo(resultado, 0);		
		return resultado;
	}
}

void balancearListas(Lista* destino, Lista* origem) { // Origem > Destino
	if (origem != NULL && destino != NULL && tamanho(origem) > 0)
	{
		int dif = tamanho(origem) - tamanho(destino);		
		for (int a = 0; a < dif; a++) inserir_primeiro(destino, 0);
	}
}

void fixList(Lista* destino, Lista* origem)
{
	if (destino != NULL && origem != NULL)
	{
		remover_ultimo(destino);
		balancearListas(destino, origem);		
	}
}

Lista* somarListas(Lista* l1, Lista* l2)
{
	if (tamanho(l1) > 0 && tamanho(l2))
	{
		Lista* resultado = criar();
		Lista* maior = clonar(l1);
		Lista* menor = clonar(l2);
		int resto = 0;

		inserir_primeiro(resultado, 0);

		balancearListas(resultado, maior);
		balancearListas(menor, maior);

		for (int id = tamanho(resultado) - 1; id >= 0; id--)
		{
			escrever_pos(resultado, id, ler_pos(resultado, id) + resto);

			if (ler_pos(maior, id) + ler_pos(menor, id) >= 10)
			{
				escrever_pos(resultado, id, (ler_pos(maior, id) + ler_pos(menor, id)) - 10);
				resto = 1;
			}
			else {
				escrever_pos(resultado, id, (ler_pos(maior, id) + ler_pos(menor, id)));
				resto = 0;
			}
		}

		free(maior);
		free(menor);

		return resultado;
	}

	return NULL;
}

void menu() {
	system("CLS");
	printf("\n---------- MENU ----------\n\n1) Inserir Divisor e Dividendo\n2) Consultar Processador\n3) Verificar Processo\n4) Processar Lista\n5) Creditos\n6) Sair\n\n");
}

void exibirProcessos() {
	printf("--------------- PROCESSOS ---------------\n\n");
	for (int a = 0; a < MAX_PROCESSOS; a++) {
		printf("Processo (%d): %s\n", a, (processos[a] == NULL) ? "Processo inexistente" : (processos[a]->concluido == 1) ? "Concluido" : "Alocado - Nao concluido");
	}
	printf("\n");
}

int criarProcesso() {

	for (int a = 0; a < MAX_PROCESSOS; a++) {
		if (processos[a] == NULL) {
			Processo* p = (Processo*)malloc(sizeof(Processo));
			p->listas = (Lista**)malloc(sizeof(Lista*) * 4);
			p->concluido = 0;
			for (int a = 0; a < 4; a++) p->listas[a] = NULL;
			processos[a] = p;
			printf("\n\t\t\t\tProcesso (%d) criado com sucesso.\n", a);
			return a;
		}
	}

	return -1;
}

int isOnlyNumeric(char str[]) {
	for (int a = 0; a < strlen(str); a++) {
		if (str[a] < '0' || str[a] > '9') return 0;
	}

	return 1;
}

Lista* getListWithZeros(Lista* l)
{
	if (l != NULL) {

		Lista* resultado = criar();
		Lista* absoluta = getListaAbsoluta(l);
		exibir(absoluta);

		//printf("--> %d = \n", tamanho(l)); exibir(getListaAbsoluta(l));

		for (int a = 0, b = 0; a < tamanho(absoluta)-1; a++)
		{
			/*if (ler_pos(l, a) != 0 && b == 0)
			{
				b++;
				continue;
			}
			*/
			if (ler_pos(absoluta, a) == 0) {
				inserir_ultimo(resultado, 0);
			}
		}

		inserir_primeiro(resultado, 1);
		return resultado;
	}
}

int getQuantZeros(Lista* l)
{
	int count = 0;

	if (l != NULL)
	{
		Lista* abs = getListaAbsoluta(l);

		for (int a = 0; a < tamanho(abs); a++) if (ler_pos(abs, a) == 0) count++;
	}

	return count;
}

// ------------------------------------------------------------------------------------------------------- //

int main(int argc, char** args)
{
	char dividendo[100];
	char divisor[100];
	char nTitle[30];
	int option;
	int pAtual;

	sprintf(nTitle, "title %s", TITLE);
	system(nTitle);	
	
	while (true)
	{
		while (true) {
			menu();
			printf("Digite a Option correspondente: ");
			scanf("%d", &option);

			switch (option)
			{
				case 1:
				{
					pAtual = criarProcesso();

					while (true)
					{
						printf("----> Insira o dividendo: ");
						scanf(" %s", &dividendo);

						if (!isOnlyNumeric(dividendo)) printf(INVALID_DIVIDENDO);
						else break;
					}

					while (true)
					{
						printf("----> Insira o divisor: ");
						scanf(" %s", &divisor);

						if (!isOnlyNumeric(divisor) || isStringZero(divisor)) printf(INVALID_DIVISOR);
						else break;
					}

					processos[pAtual]->listas[0] = stringToList(dividendo); // # Dividendo
					processos[pAtual]->listas[1] = stringToList(divisor); // # Divisor
					processos[pAtual]->listas[2] = stringToList("0"); // # Quociente
					processos[pAtual]->listas[3] = stringToList("0"); // # Resto					

					balancearListas(processos[pAtual]->listas[1], processos[pAtual]->listas[0]);
					balancearListas(processos[pAtual]->listas[2], processos[pAtual]->listas[0]);
					balancearListas(processos[pAtual]->listas[3], processos[pAtual]->listas[0]);

					if (getMaiorLista(processos[pAtual]->listas[0], processos[pAtual]->listas[1]) == processos[pAtual]->listas[1])
					{
						escrever_pos(processos[pAtual]->listas[2], 0, 0);
						processos[pAtual]->listas[3] = processos[pAtual]->listas[0];

						printf("\n----> Dividendo: "); exibir(processos[pAtual]->listas[0]);
						printf("----> Divisor: "); exibir(processos[pAtual]->listas[1]);
						printf("----> Quociente: "); exibir(processos[pAtual]->listas[2]);
						printf("----> Resto: "); exibir(processos[pAtual]->listas[3]);
						printf("\n PROCESSO %d finalizado com sucesso!", pAtual);
						processos[pAtual]->concluido = 1;
						getchar(); getchar();
						break;
					}

					printf("\n----> Dividendo: "); exibir(processos[pAtual]->listas[0]);
					printf("----> Divisor: "); exibir(processos[pAtual]->listas[1]);
					printf("----> Quociente: "); exibir(processos[pAtual]->listas[2]);
					printf("----> Resto: "); exibir(processos[pAtual]->listas[3]);

					sprintf(nTitle, "title %s - Processo: %d", TITLE, pAtual);
					system(nTitle);										

					Sleep(1000);
					
					break;
				}

				case 2: printf("\n\n"); exibirProcessos(); getchar(); getchar(); break;
				case 3:
				{
					int pId;

					while (true)
					{
						printf("\nInsira o numero do processo a ser consultado: "); scanf("%d", &pId);

						if (processos[pId] == NULL)
						{
							printf("\n------> Processo invalido!\n");
							Sleep(1000);
						}
						else {
							printf("\n\n");
							printf("----------- PROCESSO (%d) ----------- STATUS: %s\n\n", pId, processos[pAtual]->concluido == 0 ? "Nao Concluido" : "Concluido");
							printf("------> Dividendo: "); exibir(processos[pId]->listas[0]);
							printf("------> Divisor: "); exibir(getListaAbsoluta(processos[pId]->listas[1]));
							printf("------> Quociente: "); exibir(getListaAbsoluta(processos[pId]->listas[2]));
							printf("------> Resto: "); printf("[%s]", isStringZero(listToString(processos[pAtual]->listas[3])) ? "0" : getStringAbsoluta(listToString(processos[pAtual]->listas[3])));
							getchar(); getchar();
						}

						break;
					}

					break;
				}
				case 4:
				{
					if (!processos[pAtual]->concluido) {

						
						int resto = 0;
						int ableToLoop = 1;						
						
						Lista* nDividendo = clonar(processos[pAtual]->listas[0]);
						Lista* nDivisor = clonar(processos[pAtual]->listas[1]);						
						Lista* aSomar = criar();						

						int cPos = tamanho(processos[pAtual]->listas[0]) - 1;
						int nZeros = 0;
						int quant = 1;

						for (; true; cPos--)
						{
							if (ableToLoop == 1)
							{
								inserir_primeiro(aSomar, 1);

								while (getMaiorLista(nDividendo, nDivisor) == nDividendo)
								{
									nDivisor = multiplicarPor10(nDivisor);
									balancearListas(nDivisor, nDividendo);

									balancearListas(aSomar, processos[pAtual]->listas[2]);
									
									nZeros ++;
								}

								fixList(nDivisor, nDividendo);
								for (int a = 0; a < nZeros-1; a++) inserir_ultimo(aSomar, 0);
								balancearListas(aSomar, processos[pAtual]->listas[2]);								
								ableToLoop = 0; 								
							}

							escrever_pos(nDividendo, cPos, ler_pos(nDividendo, cPos) - resto);

							if (ler_pos(nDividendo, cPos) >= ler_pos(nDivisor, cPos))
							{
								int dif = ler_pos(nDividendo, cPos) - ler_pos(nDivisor, cPos);
								escrever_pos(nDividendo, cPos, dif);
								resto = 0;
							}
							else 
							{
								int dif = (ler_pos(nDividendo, cPos) + 10) - ler_pos(nDivisor, cPos);
								escrever_pos(nDividendo, cPos, dif);
								if(cPos != 0) resto = 1;
								else resto = 0;								
							}

							//printf("Progresso ---> "); exibir(getListaAbsoluta(nDividendo));
							//Sleep(10);							

							if (getMaiorLista(nDividendo, nDivisor) == nDivisor && cPos <= 1)
							{
								aSomar = getListaAbsoluta(aSomar);
								multiplicar(aSomar, quant);								
								balancearListas(aSomar, processos[pAtual]->listas[2]);
								ableToLoop = 1;
								nDivisor = clonar(processos[pAtual]->listas[1]);								
								processos[pAtual]->listas[2] = somarListas(aSomar, processos[pAtual]->listas[2]);								
								limpar(aSomar);								
								nZeros = 0;
								quant = 0; //118518518529 // 118518518520

							}
							
							if ((cPos == 1 || cPos == 0) && getMaiorLista((nDividendo), (processos[pAtual]->listas[1])) == (processos[pAtual]->listas[1]))
								break;							

							if (cPos == 0) {
								quant++;
								cPos = tamanho(processos[pAtual]->listas[0]);
							}
																				
						}

						printf("------> Dividendo: "); exibir(getListaAbsoluta(processos[pAtual]->listas[0]));
						printf("------> Divisor: "); exibir(getListaAbsoluta(processos[pAtual]->listas[1]));
						printf("------> Quociente: "); exibir(getListaAbsoluta(processos[pAtual]->listas[2]));
						printf("------> Resto: "); printf("[%s]", isStringZero(listToString(nDividendo)) ? "0" : getStringAbsoluta(listToString(nDividendo)));
						processos[pAtual]->concluido = 1;
						processos[pAtual]->listas[3] = clonar(nDividendo);
						getchar(); getchar();						
					}
					else {
						printf("\n ----> Processo %d ja finalizado.", pAtual);
						Sleep(1000);						
					}

					break;
				}

				case 5:
				{
					printf("\n\nSoftware de divisao optimizada utilizando lista encadeada.\n");
					printf("\n----> Desenvolvido por FeL 486\n");
					printf("http://www.pastebin.com/u/fel486\n\n");
					system("PAUSE");
					break;
				}

				case 6:
				{
					char end[] = "Encerrando Software em %d segundos";

					for (int a = 0; a < 5; a++)
					{
						system("CLS");
						sprintf(end, "%s.", end);
						printf(end, 5 - a);
						Sleep(200);
					}
					exit(486);
					break;
				}
			}		
		}		

	}

	printf("\n\n");
	system("PAUSE");
}
