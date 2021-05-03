#include <stdio.h>
#include <stdlib.h>

//rastreamento
/* 
	a func�o recebe como parametros, o numero que ser� convertido para binario,
	o indice que sera usado para a posi��o do array de caracteres "bin", sendo
	nesse caso, 8, devido a o numero maximo de caracteres covertidos (255) que
	em binario tera maximo de 7 digitos;
*/
void binario(int nro, int *i, char bin[8])
{	
	//verifica se o numero inteiro repassado � menor que 256
	if (nro < 256)
	{
		//repassa o numero dividido por 2 e verifica se essa divis�o resulta em um valor maior que 0;
		if(nro / 2 > 0)
		{
			//chama a fun��o sempre que o numero dividido por 2 resulta em um valor maior que 0;
			binario(nro / 2, i, bin);
			/*
				o array de caractes da posi��o "i" recebe o resto da divis�o do numero por 2
			   por exemplo, 5 % 2 resulta em 1 + o caractere 48 (na tebela ascii significa o numero 0)
			   mais convertdido em "letra".
			*/
			bin[*i] = (nro % 2) + 48;
			printf("bin[%d] = %c\n", *i, bin[*i]); // printa o indice e o resto da diviz�o do numero armezenado no array de caracteres
			(*i)++; // incremeta o indice
			
			printf("to no if\n");
		}
		else // se o numero dividido por 2 for igual a zero
		{
			printf("to no else\n");
			bin[*i] = (nro % 2) + 48;
			printf("bin[%d] = %c\n", *i, bin[*i]); // printa o valor (resto da divis�o)
			(*i)++;		
		}
		
		// a fun��o so � finalizada quando o ultimo digito � adicionado ao final, 
		// que so � feita com a codi��o "else". 
	}
}

//retornando o valor de i pela fun��o.
/*
	nesse caso, vai ser retornado o numero de digitos convertdidos em binario
	por exemplo, o numero 10 depois de converttido em binario ser�: "1010", 
	totalizando 4 digitos.
*/
int binario_retorno(int nro, int *i, char bin[8])
{
	if (nro < 256)
	{
		if(nro / 2 > 0)
		{
			binario(nro / 2, i, bin);
			bin[*i] = (nro % 2) + 48;
			printf("bin[%d] = %c\n", *i, bin[*i]);
			(*i)++;
		}
		else
		{
			bin[*i] = (nro % 2) + 48;
			printf("bin[%d] = %c\n", *i, bin[*i]);
			(*i)++;
		}
	}
	
	
	return *i; //retorno
}

int main(int argc, char** argv)
{

	int n, i = 0;
	char bin[9];
	printf("n: ");
	scanf("%d", &n);
		
	if(n < 256)
	{
		binario(n, &i, bin);
		bin[i] = '\0';
		printf("O numero binario e: %s\n", bin);
	}
	else printf("O maior n�mero poss�vel com 8 d�gitos � 255.\n");
	
	//chamando a nova fun��o com o retorno do numero de digitos
	printf("\n");
	i = 0; 
	int total = binario_retorno(n, &i, bin);
	
	printf("\nChamando a nova fun��o \"binario_retorno\" para verificar o numero de digitos que fora convertidos para binario:");
	printf("\nNumero de digitos: %d digitos\n", total);
	

	return 0;
}
