/*
por Jo�o Carlos de Sousa F�. 01/04/2021

A): "px" aponta para o ENDERE�O de "x", logo qualquer altera��o no CONTE�DO
de "px" ira refletir diretamente no CONTE�DO de x.

B): "px" e "py" ambos esperam receber um ENDERE�O DE MEMORIA das variaveis 
"x" e "y" respectivamente. Por tanto, nesse caso, n�o diferenca, ja que ambos
esperam receber ENDERE�O DE MEMORIA

C): "x" deve imprimir o valor 500, "&x" deve imprimir seu endere�o em hexadecimal 
(nota��o "%p") de "x" (algo como 0060FEF4) , "px" deve imprimir o endere�o de "x"
(nesse caso por exemplo: 0060FEF4). "y" debe imprimir o valor de x (500) acrescido
de 200: 500 + 200, logo a saida de y sera 700.

saida do printf esperada: x = 500, End. x = 0060FEF4, px = 0060FEF4, y = 700


D): o CONTE�DO para onde "px" APONTA � alterado para o conte�do de y, nesse caso
fica "*px" na fun��o "altera1" recebeu o valor de y, 700. o CONTE�DO de "y"
(valor: 700) � acrescido em mais 50, logo o CONTEUDO "y" passa a ser 750.

Saida do printf esperada: x = 700, End. x = 0060FEF4, px = 0060FEF4, y = 750. 


E): ser� impresso primeiramente o valor de "y", alterado anteriormente pela fun�o "altera1",
nesse caso o valor 750 ser� impresso. o ENDERE�O de "y" ser� impresso em seguida (algo como 0FEF4).
em seguida ser� impresso o ENDERE�O DE MEM�RIA de "y" apontado por "py" (0FEF4). Ao final ser� impresso
a valor de X, que ser� 700.

Saida do printf esperada: y = 750, End. y = 0FEF4, py = 0FEF4, x = 700


F): o valor de "y" ser� impresso (ainda 750). O endere�o apontando por "py" ser� impresso (ainda 0FEF4).
"py" dentro da fun��o "altera2" passa a apontar para o ENDERE�O de "x", logo qualquer altera��o
no CONTEUDO DE "py" ir� refletir diretamente no CONTE�DO de "x". ao imprimir o "py", sera impresso
algo como "0060FEF4", que � o endere�o de "x" agora "apontado" por "py". "x" (com CONTE�DO "700") 
dentro da fun��o "altera2" � somado com 300. 
"x" agora, o seu valor CONTE�DO passa a ser 1000.

saida esperada: y = 750, End. y = 0FEF4, py = 0060FEFC, x = 1000


G): na fun��o "altera1" somente � alterado o CONTEUDO das variaveis repassadas.
ja na fun��o altera2, o endere�o apontando por "py" � alterado, APONTANDO diretamente para
o ENDERE�O de "x", em seguida o CONTEUDO de x � alterado.

*/