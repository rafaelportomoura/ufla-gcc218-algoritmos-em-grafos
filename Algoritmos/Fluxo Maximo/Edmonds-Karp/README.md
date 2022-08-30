# Algoritmo de Edmonds-Karp

O Algoritmo de Edmonds-Karp consiste em um aprimoramento do Algoritmo de Ford-Fulkerson. Trata-se de um método de encontra o caminho aumentante do vértice origem  s  ao vértice destino  t , utilizando a Busca em Largura (BFS).

Dado um grafo direcionado  G=(V,E) , com  |V|=n  e  |E|=m , o Algoritmo de Edmonds-Karp executa em  O(nm<sup>2</sup>) . Isso é justificado pois tais autores mostraram que após  O(nm)  iterações, todos os caminhos aumentantes já serão encontrados. Levando em conta que em cada iteração gasta-se  O(m)  passos pela BFS, então chega-se à complexidade de  O(nm<sup>2</sup>) .