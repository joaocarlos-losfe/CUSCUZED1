/*
	Quarta quest�o referente a segunda avalia��o da discpina de Estrurura de dados I.

	Autores: Jo�o Carlos de Sousa F� && Vitor Jos� Ferreira dos Santos de Santana.

	Data de inicio da resolu��o dos exercicios: 28/05/2021

	Quest�o 4. Implementa��o dinamica

		Fa�a um programa em C onde o usu�rio digita uma express�o matem�tica no modo in-fixa e ent�o o 
    programa verifica se a express�o � v�lida, depois use pilha est�tica para converter para o modo p�s-fixa.
    Obs. 1: A express�o deve ser lida em uma string, e a string deve ser no m�ximo de 100 caracteres.
    Obs. 2: A express�o s� pode conter d�gitos e os operadores: (, +, -, *, /,); cada n�mero e operador deve 
    ser separado por um espa�o em branco, podendo a sim um n�mero possuir mais de um d�gito. 
    Exemplo: 130 + 50 - 25
    Obs. 4: A express�o deve sempre iniciar com operando ou abre par�nteses e terminar com operando ou 
    fecha par�nteses.
    
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

// estrutura basica dos dados

typedef struct aux
{
    char elemento_expressao[10];
    struct aux* proximo_abaixo;

}ElementoOperandoOperador, *PontElementoOperandoOperador;

typedef struct
{
    PontElementoOperandoOperador topo;

}Pilha;

//opera��es basicas de pilha

void inicializarPilha(Pilha *pilha)
{
    pilha->topo = NULL;
}

void reinicializarPilha(Pilha *pilha)
{
    PontElementoOperandoOperador apagar_end;
    PontElementoOperandoOperador posicao_elementos_validos = pilha->topo;

    while (posicao_elementos_validos != NULL)
    {
        apagar_end = posicao_elementos_validos;
        posicao_elementos_validos = posicao_elementos_validos->proximo_abaixo;
        free(apagar_end);
    }

    inicializarPilha(pilha); // topo apontar para null
}

bool vazia(Pilha *pilha)
{
    if(pilha->topo == NULL)
        return true;
    else
        return false;
}


void exibir(Pilha *pilha)
{
    if (!vazia(pilha))
    {
        PontElementoOperandoOperador end_topo = pilha->topo;
        printf("\n");
        while (end_topo!=NULL)
        {
            printf("%s ", end_topo->elemento_expressao);
            end_topo = end_topo->proximo_abaixo;
        }
        printf("\n");
    }
}

void empilhar(Pilha *pilha, char *elemento_expressao)
{
    PontElementoOperandoOperador novo_elemento_expressao = (PontElementoOperandoOperador) malloc(sizeof(ElementoOperandoOperador));
    strcpy(novo_elemento_expressao->elemento_expressao, elemento_expressao);
    novo_elemento_expressao->proximo_abaixo = pilha->topo;
    pilha->topo = novo_elemento_expressao;
}

bool desempilhar(Pilha *pilha, char *temp_elemento_expressao)
{
    if (!vazia(pilha))
    {
        strcpy(temp_elemento_expressao, pilha->topo->elemento_expressao);
        PontElementoOperandoOperador apagar_end = pilha->topo;
        pilha->topo = pilha->topo->proximo_abaixo;
        free(apagar_end);
        return true;
    }
    else
        return false;

}

void inverterPilha(Pilha *pilha)
{
    if(!vazia(pilha))
    {
        Pilha pilha_temp; inicializarPilha(&pilha_temp);
        char temp_elemento_expressao[10];

        while (!vazia(pilha))
        {
            desempilhar(pilha, temp_elemento_expressao);
            empilhar(&pilha_temp, temp_elemento_expressao);
        }

        pilha->topo = pilha_temp.topo;

    }
}

// fun��es para converter em pos fixa

bool ehOperador(char *str)
{
    bool eh_operador = false;
    switch (*str)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        eh_operador = true;
        break;
    default:
        break;
    }

    return eh_operador;
}

int prioridade(char *str)
{
    int prioridade = 0;
    switch (*str)
    {
    case '+':
    case '-':
        prioridade = 2;
        break;
    case '*':
    case '/':
        prioridade = 3;
        break;
    case '(':
    case ')':
        prioridade = 1;
        break;
    }

    return prioridade;
}

bool ehNumero(char *str)
{
    bool eh_numero = true;
    int i = 0;
    char temp_str[10];

    while (str[i] != '\0')
    {
        if(!isdigit(str[i]))
        {
            eh_numero = false;
            break;
        }

        i++;
    }
    
    return eh_numero;
}

bool validarExpressao(char *str, Pilha *pilha, int *qtdParenteseAberto, int *qtdParentesefechado)
{
    bool valida  = true;

    if (str[0] == '(')
        *qtdParenteseAberto +=1;
    else if (str[0] == ')')
        *qtdParentesefechado +=1;

    if (!ehNumero(str) && !ehOperador(str))
    {
        valida = false;
    }
    else
    {
        if (!vazia(pilha))
        {
            
            if (ehNumero(str) && ehNumero(pilha->topo->elemento_expressao))
            {
                valida = false;
            }
            else if (ehOperador(str) && ehOperador(pilha->topo->elemento_expressao))
            {
                valida = false;

                if (str[0] == '(' || pilha->topo->elemento_expressao[0] == ')')
                {
                    valida = true;
                }
            }
            else if (str[0] == '(' && ehNumero(pilha->topo->elemento_expressao) )
            {
                valida = false;
            }
            
        }
    }
    
    return valida;
}

bool fragmentarString(char *str, Pilha *pilha)
{
    char str_composta[10];
    int i = 0;
    int k = 0;
    strcat(str, " ");

    int qtdParentesesAbertos = 0;
    int qtdParentesesFechados = 0;
    bool expressao_valida = false;

    while (str[k] != '\0')
    {
        if(str[k] != ' ')
        {
            str_composta[i] = str[k];
            i++;
        }
        else
        {
            str_composta[i] = '\0';
            i = 0;

            expressao_valida = validarExpressao(str_composta, pilha, &qtdParentesesAbertos, &qtdParentesesFechados);

            if(expressao_valida)
                empilhar(pilha, str_composta);
            else 
                break;
        }

        k++;
    }

    if (qtdParentesesAbertos != qtdParentesesFechados)
        expressao_valida = false;
    
    return expressao_valida;
}

void converterPosfixa(Pilha *pilha_operando_operador, Pilha *pilha_operadores, Pilha *pilha_pos_fixa)
{
    inverterPilha(pilha_operando_operador);
   
    while (!vazia(pilha_operando_operador))
    {
        if (!ehOperador(pilha_operando_operador->topo->elemento_expressao))
        {
            empilhar(pilha_pos_fixa, pilha_operando_operador->topo->elemento_expressao);
        }
        else if(pilha_operando_operador->topo->elemento_expressao[0] == '(')
        {
            empilhar(pilha_operadores, pilha_operando_operador->topo->elemento_expressao);
        }
        else if (pilha_operando_operador->topo->elemento_expressao[0] == ')')
        {
            char operador[10];

            desempilhar(pilha_operadores, operador);

            while ( operador[0] != '(' && !vazia(pilha_operando_operador))
            {
                empilhar(pilha_pos_fixa, operador);
                desempilhar(pilha_operadores, operador);
            }
        }
        else
        {
            char temp_elemento_expressao[10];
            while (!vazia(pilha_operadores) &&
            prioridade(pilha_operadores->topo->elemento_expressao) >=
            prioridade(pilha_operando_operador->topo->elemento_expressao))
            {
                desempilhar(pilha_operadores, temp_elemento_expressao);
                empilhar(pilha_pos_fixa, temp_elemento_expressao);
            }

            empilhar(pilha_operadores, pilha_operando_operador->topo->elemento_expressao);

        }

        pilha_operando_operador->topo = pilha_operando_operador->topo->proximo_abaixo;
    }

    while (!vazia(pilha_operadores))
    {
        char temp_elemento[5];
        desempilhar(pilha_operadores, temp_elemento);
        empilhar(pilha_pos_fixa, temp_elemento);
    }

    inverterPilha(pilha_pos_fixa);

}

int main()
{
    setlocale(LC_ALL, "");
    
    Pilha pilha_operando_operador; inicializarPilha(&pilha_operando_operador);
    Pilha pilha_operadores; inicializarPilha(&pilha_operadores);
    Pilha pilha_pos_fixa; inicializarPilha(&pilha_pos_fixa);

    int qtdParenteseAberto = 0;
    int qtdParentesefechado = 0;
    char expressao[100];
    bool valida = false;

    do
    {
        setbuf(stdin, NULL);

        printf("\nDigite uma express�o (digite 0 para sair): "); scanf(" %[^\n]s", expressao);

        if(expressao[0] != '0')
        {
            valida = fragmentarString(expressao, &pilha_operando_operador);

            if (valida)
            {
                converterPosfixa(&pilha_operando_operador, &pilha_operadores, &pilha_pos_fixa);
                exibir(&pilha_pos_fixa);
            }
            else
                printf("\nExpress�o Invalida !\n");
        }

        //limpar todos os elemnetos das pilhas para reutiliza��o.
        reinicializarPilha(&pilha_operando_operador);
        reinicializarPilha(&pilha_operadores);
        reinicializarPilha(&pilha_pos_fixa);

    } while (expressao[0] != '0');
    
    
    return 0;
}
