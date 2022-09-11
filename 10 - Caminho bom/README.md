# Caminho bom

A empresa de transporte urbano Sim: Vamos! acabou de se instalar em uma metrópole brasileira, e tem se destacado por tarifas acessíveis e agilidade no serviço. Você acabou de ser contratado como desenvolvedor Full Stack, e tem mostrado bastante pro-atividade em suas ações. O aplicativo da empresa busca sempre encontrar o caminho mais curto entre o ponto de partida S e o ponto de chegada T de um usuário. No entanto, os graves problemas de mobilidade urbana nas metrópoles brasileiras fizeram com que a empresa mudasse um pouco a estratégia para o cálculo das rotas.

Os Tech Leads da Sim: Vamos! pretendem implementar uma nova funcionalidade no aplicativo da empresa: dado um ponto de partida S e um ponto de chegada T de um usuário, encontrar um "bom caminho" entre S e T, que não seja o mais curto, mas que esteja próximo ao mais curto. Para tanto, foi definido que:

- Seja R uma rota correspondente ao menor caminho de S a T;
- Um "bom caminho" de S a T corresponde a um menor caminho W tal que nenhuma ligação entre dois pontos consecutivos em qualquer rota R pertença a W.

Por exemplo, considere a lista de adjacências do grafo abaixo, com 7 vértices (os pesos das arestas estão entre parênteses).

- 1: 2 (1), 3 (1), 4 (2), 5 (3).
- 2: 6 (2).
- 3: 7 (4).
- 4: 7 (2).
- 5: 7 (4).
- 6: 7 (1).
- 7: -.
Tomando S=1 e T=7, o "bom caminho" será calculado como S-3-T, valendo 5.

Apesar de trabalhar na parte de Tecnologia da Informação, você percebe que com seus conhecimentos de Algoritmos em Grafos, esse problema pode ser bem resolvido. Ajude os Tech Leads da Sim: Vamos! a resolver esse problema. Desenvolva um código que encontre o valor do "bom caminho".

## Entrada

A entrada consiste em vários casos de teste. A primeira linha contém dois inteiros n (2 <= n <= 500) e m (1 <= m <= 10000), indicando o número de pontos e o número de ligações (mão única) entre cada par de pontos descritos. Cada ponto é identificado por um inteiro entre 0 e n-1. A segunda linha possui dois inteiros, relativos a S e T, respectivamente, com S != T e 0 <= S,T < n. Cada uma das m linhas possui três inteiros u,v,p (u != v, 0 <= u,v < n e 1<=p<=1000), indicando a ligação dos pontos u e v com distância p. O fim da entrada é indicada por dois zeros.

## Saída

Para cada caso de teste, imprima o valor do "bom caminho".
