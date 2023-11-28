# IDEIA:
Uma pequena escola, no interior o estado, possui uma biblioteca onde consta apenas um exemplar de
cada livro.
Atualmente todo o seu processo é manual o que tem trazido grandes problemas de gerenciamento e perda
de livros, que já não são muitos.

Este Projeto consiste em um Sistema para Gerenciamento da Locação de Livros para esta biblioteca e
envolve os conceitos de LISTA ENCADEADA.
Projeto:
O Time dever criar um Sistema para Gerenciamento de Locação de Livros para a biblioteca dessa pequena
escola, considerando que há três pos de informações a serem gerenciadas:

1. LIVROS DISPONÍVEIS:
   Código de registro – valor inteiro;
   Título – cadeia de caracteres com no máximo 50 posições;Assunto – cadeia de caracteres com no máximo 100 posições;
   Autor – cadeia de caracteres com no máximo 50 posições;
   
3. LIVROS EMPRESTADOS:
   Código de idenficação do CLINETE que emprestou o livro– valor inteiro;
   Código de registro do Livro Emprestado – valor inteiro;
   Título – cadeia de caracteres com no máximo 50 posições;
   Assunto – cadeia de caracteres com no máximo 100 posições;
   Autor – cadeia de caracteres com no máximo 50 posições;
   
5. CLIENTE:
   Código de Idenficação – valor inteiro;
   Nome– cadeia de caracteres com no máximo 50 posições;
   Livros Emprestados – Lista encadeada que contém todas as informações sobre os livros
   emprestados
