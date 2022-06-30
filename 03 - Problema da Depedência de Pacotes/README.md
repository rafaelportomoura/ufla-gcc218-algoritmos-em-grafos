# Problema da Depedência de Pacotes

**(Esta questão foi adaptada de um problema utilizado em uma entrevista de emprego para Engenheiro de Software da Amazon/Seattle).**

Considere o seguinte problema: dada a dependência de compilação de alguns pacotes Java, determine a ordem em que eles devem ser compilados de modo a satisfazer essas restrições. Para tanto, implemente um algoritmo que resolva esse problema.

- **Entradas:** a entrada começará com dois inteiros representando o número de pacotes ( P ) e o número de dependências ( D ). A seguir, há  D  linhas cada uma contendo um par de inteiros  (a,b) , indicando que o pacote  b  ( 1≤b≤P ) depende do pacote a ( 1≤a≤P ) para poder ser compilado.

- **Saídas:** a ordem a qual os pacotes devem ser compilados. Priorize a ordem lexicográfica dos pacotes na exploração do algoritmo. Caso sua entrada tenha pacotes com dependência circular, seu programa deve imprimir a mensagem: "solucao inviavel".

**Exemplo de entrada**:  
4 3  
1 2  
1 3  
2 3  
