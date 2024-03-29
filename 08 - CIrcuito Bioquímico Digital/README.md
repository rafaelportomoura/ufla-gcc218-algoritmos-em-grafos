# Circuito Bioquímico Digital

[Beecrowd](https://www.beecrowd.com.br/judge/pt/problems/view/1486)

Um circuito bioquímico digital (CBD) é um artefato composto de um conjunto de pontos de processamento. Cada ponto de processamento é constituído por um minúsculo receptáculo para reagentes bioquímicos, feito de um substrato biológico que se comporta como um microcircuito eletrônico digital. Dependendo do estado da reação no receptáculo, o substrato gera dois níveis de voltagem. Um leitor acoplado ao CBD é capaz de realizar a leitura de todos os pontos de processamento de um CDB num dado instante, interpretando os dois níveis de voltagem como 0 ou 1.

Um experimento com o CBD é realizado da seguinte maneira. Os pontos de processamento são carregados com as substâncias de interesse e reagentes apropriados e, a cada intervalo fixo de tempo (tipicamente alguns milissegundos), os pontos de processamento são lidos. Assim, o experimento resulta em uma sequência de conjuntos (vetores) de bits, cada vetor correspondendo a uma medição do CBD.

Uma sequência ininterrupta de bits 1 de um mesmo ponto de processamento ao longo do tempo é denominada de palito. O comprimento de um palito é o número de bits 1 que o compõe (note que o comprimento dos palitos de um experimento pode variar entre um e o número de medições efetuadas). Uma característica importante de um experimento com o CBD é a quantidade e o comprimento dos palitos gerados. A figura abaixo mostra o resultado de um experimento realizado com um CBD de seis pontos de processamento, em que foram efetuadas quatro medições, contendo três palitos de comprimento um, um palito de comprimento dois e um palito de comprimento quatro.

![img](assets/img.png)

Você foi contratado para escrever um programa que determine, dado o resultado de um experimento, quantos palitos de comprimento igual ou maior do que um certo valor foram gerados.

## Entrada

A entrada contém vários casos de teste. A primeira linha de um caso de teste contém três inteiros **P**, **N** e **C** que indicam respectivamente o número de pontos de processamento (1 ≤ **P** ≤ 1000), o número de medições efetuadas (1 ≤ **N** ≤ 1000) e o comprimento mínimo de palitos de interesse (1 ≤ **C** ≤ **N**). Cada uma das próximas N linhas contém sequências de **P** dígitos {0, 1}, separados por um espaço em branco. O final da entrada é indicado por **P** = **N** = **C** = 0.

## Saída

Para cada caso de teste da entrada seu programa deve produzir uma única linha da saída, contendo o número de palitos de comprimento maior ou igual a **C** produzidos pelo experimento.

### Exemplo de entradas

```txt
2 2 2
1 1
1 1
4 5 3
0 1 0 1
1 1 1 1
1 0 0 1
1 0 1 1
1 1 0 0
0 0 0
```

## Exemplo de saída

```txt
2
2
```
