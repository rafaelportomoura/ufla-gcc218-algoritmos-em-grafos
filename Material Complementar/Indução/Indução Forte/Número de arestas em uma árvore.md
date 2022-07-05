# Indução Forte

## Base

Seja G = (V,E) uma árvore de 2 vértices e 1 aresta:

(1) - (2)

A propriedade é válida.

## Indutivo

Considere que para qualquer árvore G' = (V', E'), |V'| < n, temos |E'| = |V'| - 1.  

Suponha G = (V,E) uma árvore com |V| = n vértices. Vamos eliminar uma aresta qualquer (u,v) ∈ E.

COmo toda areta de G é ponte, então teremos duas componentes G<sub>1</sub> = (V<sub>1</sub>,E<sub>1</sub>) e G<sub>2</sub> = (V<sub>2</sub>,E<sub>2</sub>) árvores.

Logo, pela hipótese indutiva:

|E<sub>1</sub>| = |V<sub>1</sub>| - 1  
|E<sub>2</sub>| = |V<sub>2</sub>| - 1  

Portanto:

|E| = |E<sub>1</sub>| + |E<sub>2</sub>| + 1  
|E| = (|V<sub>1</sub>| - 1 ) + (|V<sub>2</sub>| - 1 ) + 1  
|E| = |V<sub>1</sub>| + |V<sub>2</sub>| - 1 - 1 + 1  
|E| = |V<sub>1</sub>| + |V<sub>2</sub>| - 1
|E| = n - 1