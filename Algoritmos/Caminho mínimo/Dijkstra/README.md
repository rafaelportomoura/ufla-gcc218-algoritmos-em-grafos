# Algoritmo de Dijkstra

## Motivação

O esquema a seguir representa os caminhos que ligam diversas localidades por onde devem passar o mosqueteiro D'Artagnan, que está repleto de emboscadas. Os números representam a probabilidade $\frac{x}{10}$ de sucesso de ultrapassar os trechos. Por exemplo, entre os vértices $2$ e $4$, a probabilidade de sucesso é de $70\%$. Qual é a probabilidade de sucesso de D'Artagnan de $1$ até os outros vértices?

## Implementação

O problema acima pode ser resolvido através do Algoritmo de Dijkstra, pois se trata de uma adaptação do problema de caminho mais curto de *fonte única*.  

$G=(V,E)$ trata-se de um grafo ponderado e orientado, em que os pesos dos arcos indicam a probabilidade de sucesso de ultrapassar cada trecho. Como Dijkstra visa minimizar o caminho mais curto, propõe-se a resolução do problema minizando o fracasso, dado por $1-\frac{x}{10}$. O vértice de origem é dado pelo vértice $1 \in V$.

Abaixo, segue uma sugestão de código para resolver o problema. **Note:** como pretende-se minimizar a probabilidade de fracasso, a atualização do valor da estimativa do menor caminho da origem  passando pelo arco $(u,v)$ deve considerar o produto de $d[u]$ por $w_{uv}$, em que $w_{uv}$ é o peso do arco $(u,v)$.
