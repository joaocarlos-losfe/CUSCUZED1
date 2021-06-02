/*
	Terceira quest�o referente a segunda avalia��o da discpina de Estrurura de dados I.

	Autores: Jo�o Carlos de Sousa F� && Vitor Jos� Ferreira dos Santos de Santana.

	Data de inicio da resolu��o dos exercicios: 25/05/2021

	Quest�o 3. Implementa��o estatica
    
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
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

typedef struct 
{
    int topo;
    char dados[100][5];

}Pilha;

void empilhar(Pilha *expressoes, char *str)
{
    strcpy(expressoes->dados[expressoes->topo], str);
    expressoes->topo += 1;
}

char* desempilhar(Pilha *expressoes)
{
    expressoes->topo -=1;

    return expressoes->dados[expressoes->topo];
}

bool vazia(Pilha *expressoes)
{
    if (expressoes->topo > 0)
        return false;
    else
        return true;
}

void inverterPilha(Pilha *expressoes)
{
    Pilha expressoes_temp;
    expressoes_temp.topo = 0;

    int i=0;

    for(i= expressoes->topo-1; i>=0; i--)
    {
        empilhar(&expressoes_temp, expressoes->dados[i]);
    }

    *expressoes = expressoes_temp;

}

void exibirpilha(Pilha *expressoes)
{
    int i=0;

    for(i=expressoes->topo -1; i>=0; i--)
    {
        printf("%s ", expressoes->dados[i]);
    }
}

char * dadoTopo(Pilha *pilha)
{
    return pilha->dados[pilha->topo-1];
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

bool ehOperador(char *operandoOuoperador)
{
    switch (operandoOuoperador[0])
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    return true;
        break;
    default:
    return false;
        break;
    }   
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
            if (ehNumero(str) && ehNumero(pilha->dados[pilha->topo-1]))
            {
                valida = false;
            }
            else if (ehOperador(str) && ehOperador(pilha->dados[pilha->topo-1]))
            {
                valida = false;

                if (str[0] == '(' || pilha->dados[pilha->topo-1][0] == ')')
                {
                    valida = true;
                }
            }
            else if (str[0] == '(' && ehNumero(pilha->dados[pilha->topo-1]))
            {
                valida = false;
            }
            
        }
    }
    
    return valida;
}


bool fragmentarStringEmPilha(char *str_expressao, Pilha *expressoes)
{
    int i;
    strcat(str_expressao, " ");
    char string_composta[5];
    int k = 0;

    int qtdParenteseAberto = 0, qtdParentesefechado = 0;

    bool expressao_valida = true;

    for(i=0; i<=strlen(str_expressao); i++)
    {
        if(str_expressao[i] != ' ')
        {
            string_composta[k] = str_expressao[i];
            k++;
        }
        else
        {
            string_composta[k] = '\0';
            k = 0;
            
            if(validarExpressao(string_composta, expressoes, &qtdParenteseAberto, &qtdParentesefechado) == true)
                empilhar(expressoes, string_composta);
            else
                expressao_valida = false;
        }
    }
    empilhar(expressoes, string_composta);

    if (qtdParenteseAberto != qtdParentesefechado)
        expressao_valida = false;

    return expressao_valida;
}

int pesoOperadores(char *str)
{
    int peso;
    switch (str[0])
    {
    case '*':
    case '/':
        peso = 3;
        break;

    case '+':
    case '-':
        peso = 2;
        break;

    case '(':
    case ')':
        peso = 1;
        break;
    }

    return peso;
}

void converterPosfixa(Pilha *expressoes, Pilha *operadores, Pilha *pilha_pos_fixa)
{
    int i = 0;

    inverterPilha(expressoes);

    for(i=expressoes->topo-1; i>0; i--)
    {
        if(!ehOperador(expressoes->dados[i]))
        {
            empilhar(pilha_pos_fixa, expressoes->dados[i]);
        }
        else if (expressoes->dados[i][0] == '(')
        {
            empilhar(operadores, expressoes->dados[i]);
        }
        else if (expressoes->dados[i][0] == ')')
        {
            char *operador = desempilhar(operadores); // retornando uma string
            
            while (strcmp(operador, "(") != 0 && !vazia(expressoes))
            {
                empilhar(pilha_pos_fixa, operador);
                operador = desempilhar(operadores); //facila a compara��o
            }
        }
        else
        {
            while (!vazia(operadores) && 
            pesoOperadores(operadores->dados[operadores->topo-1]) >= 
            pesoOperadores(expressoes->dados[i]))
            {
                empilhar(pilha_pos_fixa, desempilhar(operadores));
            }

            empilhar(operadores, expressoes->dados[i]);
        }
    }

    while (!vazia(operadores))
    {
        empilhar(pilha_pos_fixa, desempilhar(operadores));
    }

    inverterPilha(pilha_pos_fixa);

}

int main()
{
    setlocale(LC_ALL, "");

    Pilha pilha_expressao;
    pilha_expressao.topo = 0;

    Pilha operadores; operadores.topo = 0;

    Pilha pilha_pos_fixa; pilha_pos_fixa.topo = 0;

    char expressao[100];

    bool valida = false;

    do
    {
        setbuf(stdin, NULL);
        printf("\nDigite uma express�o (digite 0 para sair): "); scanf(" %[^\n]s", expressao);

        if (expressao[0] != '0')
        {
            valida = fragmentarStringEmPilha(expressao, &pilha_expressao);

            if (valida)
            {
                converterPosfixa(&pilha_expressao, &operadores, &pilha_pos_fixa);
                exibirpilha(&pilha_pos_fixa);
            }
            else
                printf("\nExpress�o Invalida !\n");
            
            pilha_expressao.topo = 0;
            operadores.topo = 0;
            pilha_pos_fixa.topo = 0;

        }

    } while (expressao[0] != '0');
    
   
    return 0;
}