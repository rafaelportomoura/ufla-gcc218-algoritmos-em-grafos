# Ajude os matemáticos

## Descrição

Éder e Wando são dois matemáticos brasileiros que trabalham no Departamento de Matemática de uma prestigiosa universidade americana. Apesar das inúmeras contribuições téoricas já publicadas
por essa dupla, especialmente no campo do Cálculo, Éder e Wando decidiram se arriscar no mundo da Teoria de Grafos. Comprovando a sua competência, tais pesquisadores criaram o conceito de
Subgrafo EW, com promissoras aplicações em modelagem de grafos na área de logística. Um Subgrafo EW, presente em um grafo não-direcionado G=(V,E), é definido por uma sequência de ciclos C1, C2, ..., Ck, com k >= 1, satisfazendo as condições abaixo:

- Dois ciclos quaisquer Ci e Cj, i,j=1,...,k, i != j, não possuem arestas em comum.
- Existe exatamente um vértice em comum entre dois ciclos adjacentes Ci e Cj, com 1 <= i,j <= k.
- Ciclos que não-adjacentes não possuem vértices em comum.
- Um vértice aparece em um ciclo no máximo uma vez.

Um Subgrafo EW entre dois vértices X e Y, X, Y pertencentes a V, consiste em uma sequência de ciclos C1, C2, ..., Ck tal que X pertence a C1 e Y pertence a Ck.

Éder e Wando são brilhantes na parte teórica, mas não possuem conhecimento computacional para resolver a seguinte tarefa: **Dado um grafo não-direcionado G, como implementar um programa que decide se G possui um Subgrafo EW?**

Você, aluno de Algoritmos em Grafos, foi escolhido para resolver esse problema!

## Entrada

A entrada é constituída de vários casos de teste. Cada caso apresenta, na primeira linha, dois inteiros n (2 <= n <= 10.000) e m (1 <= m <= 100.000), representando o número de vértices e o número de arestas do grafo não-direcionado G=(V,E), respectivamente. Cada uma das próximas m linhas contém os inteiros u e v (1 <= u,v <= n), que indicam as arestas do grafo. A última linha de cada caso de teste indica os vértices X e Y, respectivamente. Os valores 0 0, na última linha, indicam que todos os casos de teste foram finalizados.

## Saída

Para cada caso de teste, imprima em uma linha separada o valor 1, caso o grafo G=(V,E) possua um Subgrafo EW. Caso contrário, imprima 0.
