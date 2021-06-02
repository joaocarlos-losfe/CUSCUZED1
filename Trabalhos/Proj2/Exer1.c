/*
	Primeira quest�o referente a segunda avalia��o da discpina de Estrurura de dados I.

	Autores: Jo�o Carlos de Sousa F� && Vitor Jos� Ferreira dos Santos de Santana.

	Data de inicio da resolu��o deste exercicio: 08/05/2021

	Quest�o 2. Implementa��o estatica

        O estacionamento Picoense cont�m uma �nica alameda que guarda at� 10 carros. Existe uma entrada e 
    uma sa�da, de tal forma que quando um determinado carro entra ele fica no final da fila e o primeiro 
    que chegou sempre fica pr�ximo a sa�da, ou seja, todas as vezes que um carro sai todos os outros 
    devem ser manobrados um espa�o para frente. Fa�a um programa em C, onde o usu�rio entrar� com o 
    n�mero da placa do carro e 'E' se estiver entrando no estacionamento e 'S' se estiver saindo do 
    estacionamento. O programa deve emitir uma mensagem sempre que um carro entrar ou sair do 
    estacionamento. Quando um carro chegar, a mensagem deve especificar se existe ou n�o vaga no 
    estacionamento, esse n�o tiver vaga, simplesmente o carro vai embora, n�o existe fila de espera. 
    Quando um carro sair, a mensagem dever� incluir o n�mero de vezes em que o carro foi manobrado 
    para fora do estacionamento para permitir que outros carros sa�ssem, al�m de mostrar quantos carros 
    foram manobrados para que ele sa�sse.
    Obs.: N�o se esque�a que todas as vezes que um carro vai sair os que est�o na frente devem ser 
    manobrados para o final da fila, mas ao final os carros que estava na frente do carro que saiu devem 
    continuar no mesmo lugar de antes, ou seja, todos os demais carros devem ir para o fim da fila, mas 
    n�o deve ser contabilizado como manobra.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct
{
	int placa;

} Carro;

#define M 10

typedef struct
{
	Carro carros[10];
	int fim;
	
} Fila;


bool filaVazia(Fila *fila)
{
	bool vazia = false;

	if(fila->fim == 0)
		vazia = true;

	return vazia;
}

bool filaCheia(Fila *fila)
{
	bool cheia = false;

	if(fila->fim == M)
		cheia = true;

	return cheia;
}

void inserir(Fila *fila, Carro carro)
{
	if(!filaCheia(fila))
	{
		int i = fila->fim;
		fila->carros[i] = carro;
		fila->fim += 1;
	}
	else
	{
		printf("\nFila cheia !!\n");
	}
}

void exibirFila(Fila *fila)
{
	if(!filaVazia(fila))
	{
		int i;
		int p = 1;

		for(i = 0; i < fila->fim; i++)
		{
			printf("\nCarro %d placa: %d", p, fila->carros[i].placa);
			p++;
		}
	}
	else
	{
		printf("\nFila vazia\n");
	}
}

void remover(Fila *fila, Carro *carro)
{
	if(!filaVazia(fila))
	{
		int removidos = 0;
		int i;
		
		*carro = fila->carros[0];

		for(i = 0; i < fila->fim; i++)
		{
			fila->carros[i] = fila->carros[i + 1];
			removidos += 1;
		}

		fila->fim = removidos - 1;
	}
	else
	{
		printf("\nFila vazia !!\n");
	}
	
}

bool taNaFila(Fila *fila, int placa)
{
	Fila fila_temp; fila_temp.fim = 0;
	
	bool ta_na_fila = false;
	Carro carro;
	
	while(!filaVazia(fila))
	{
		remover(fila, &carro);
		
		inserir(&fila_temp, carro);
		
		if(placa == carro.placa)
			ta_na_fila = true;
	}
	
	*fila = fila_temp;
	
	return ta_na_fila;
}

bool manobrarCarroPraFora(Fila *fila, int *total_sairam, int *total_manobrados, int placa)
{
	bool carro_saiu = false;
	*total_sairam = 0;
	*total_manobrados = 0;
	
	Fila fila_temp; fila_temp.fim = 0;
	
	Carro carro;
	
	while(!filaVazia(fila))
	{
		if(placa != fila->carros[0].placa && carro_saiu != true)
		{
			*total_sairam+=1;
		}
		else
		{
			carro_saiu = true;
		}
		
		remover(fila, &carro);
		
		if(carro.placa != placa)
			inserir(&fila_temp, carro);
	}
	
	*total_manobrados = fila_temp.fim - *total_sairam;
	
	*fila = fila_temp;
	
	return carro_saiu;
}


void menu()
{
	printf("\n1 - estacionamento");
	printf("\n2 - exibir fila");
	printf("\n0 - encerrar programa\n> ");
	
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
    Fila fila_carros;
	
	fila_carros.fim = 0;
	
	Carro carro;
	
	int total_sairam = 0;
	int total_manobrados = 0;
	int op = 1;
	char E_S;
	bool saiu = false;
	
	do
	{
		menu();
		scanf("%d", &op);
		
		switch(op)
		{
		case 1:
			printf("\nPlaca do carro: ");
			scanf("%d", &carro.placa);
			
			printf("\nE - Entrar no estacionamento");
			printf("\nS - Sair do estacionamento\n> ");
			scanf(" %c", &E_S);
			
			if(E_S == 'E' || E_S == 'e')
			{
				if(!taNaFila(&fila_carros, carro.placa))
					inserir(&fila_carros, carro);
				else
					printf("\nCarro ja se encontra na fila. O carro � CLONADO !!\n");
			}
			else if (E_S == 'S' || E_S == 's')
			{
				saiu = manobrarCarroPraFora(&fila_carros, &total_sairam, &total_manobrados, carro.placa);
				
				if(saiu)
					printf("\nTotal sairam da frente: %d. total manobrados: %d\n", total_sairam, total_manobrados);
				else
					printf("\nCarro n�o encontrado...\n");
				
			}
			else
				printf("Opera��o cancelada");
			
			total_sairam = 0;
			total_manobrados = 0;
			
			break;
		case 2:
			exibirFila(&fila_carros);
			printf("\n");
		default:
			break;
		}
		
	}while(op!=0);
	
	return 0;
}