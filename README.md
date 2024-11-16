# Algoritmos 2 - UFMG

Esse é um repositório criado para a disciplina "Algoritmos 2" do curso de Ciência da Computação da UFMG.

Ele possui uma página web de apresentação dos trabalhos desenvolvidos que pode ser acessada por esse link: LINK

Esse repositório será privado durante o desenvolvimento dos trabalhos e voltará a visibilidade pública quando 
novos trabalhos não estiverem sendo desenvolvidos no momento ou quando a disciplina tiver sido finalizada.

## Instruções para Execução dos Trabalhos

Cada trabalho foi desenvolvido apenas com a linguagem C++. Para executar cada um deles, é necessário seguir o seguinte passo a passo:

 - Instalar o compilador padrão (gcc/g++):
    
     Recomenda-se os seguintes tutoriais:
    
     - Linux: https://www.youtube.com/watch?v=4e7pa6Pf3VQ
     - Mac: https://www.youtube.com/watch?v=Qw5qjRNlC-Y
     - Windows: https://www.youtube.com/watch?v=j5gJJe_0zP4

     Todos os créditos são dados aos devidos criadores dos canais recomendados.

 - Executar o programa no terminal:

     $ make
     $ make run
    
     OBS: cada um dos trabalhos possuem diversos testes desenvolvidos para demonstrar a usabilidade e eficiência do código. É necessário seguir as instruções específicas de cada trabalho para ter o resultado esperado. Novos testes devem ser inseridos seguindo o mesmo modelo apresentado no repositório.

 - Limpar arquivos criados:

     $ make clean

## Trabalho Prático 1 - Manipulação de Sequências

O trabalho desenvolvido tem como objetivo explorar a compressão de arquivos por meio do algoritmo Lempel-Ziv-Welch (LZW), utilizando a estrutura de dados Trie. O LZW, uma extensão eficiente do método LZ78, realiza a compressão substituindo sequências repetidas no texto por códigos numéricos, otimizando o espaço de armazenamento. Para suportar as operações de busca e inserção frequentes, foi empregada a Trie, uma estrutura de árvore de prefixo que permite gerenciar o dicionário dinâmico necessário ao funcionamento do algoritmo.

Duas variações do LZW foram implementadas: uma com tamanho fixo de código, padrão de 12 bits, e outra com tamanho variável, que ajusta dinamicamente o número de bits conforme a expansão do dicionário. Ambas utilizam uma Trie compacta para armazenar as associações string-índice e índice-string, otimizando o processo tanto na compressão quanto na descompressão.

Além do algoritmo principal, foram desenvolvidos scripts para capturar métricas de desempenho, como taxa de compressão, tempo de execução e consumo de memória, gerando relatórios detalhados com gráficos e tabelas. A implementação foi extensivamente testada com diferentes tipos de dados, incluindo arquivos de texto e imagens não comprimidas, validando a eficácia e robustez do método.