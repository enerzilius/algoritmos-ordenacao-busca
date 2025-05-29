# Trabalho Prático - Algoritmos de Ordenação e Busca
## 1. Geração de dados:
- Os dados serão criados em arquivos binários que serão posteriormente consumidos pelos algoritmos de ordenação dentro de [codigo/ordenacao.cpp](codigo/ordenacao.cpp);
-  **Geração:**
    - Primeiro, garanta que você tem um compilador de c/c++ instalado;
    - Se tiver, é só seguir os seguintes passos:
        - **Linux**:
        ```shell
            >> g++ codigo/gerador_dados.cpp && ./a.out
        ```
        - **Windows**:
        ```shell
            >> g++ codigo/gerador_dados.cpp
            >> ./a.exe
        ```
- **Resultado:**
    - O resultado dessa execução deve ser a quantidade de números criados por arquivo em certo número de segundos:
    ![alt text](outputGerador.png)

    (No Linux o display das letras com acento devem funcionar normalmente)
    - Assim como os arquivos .bin localizados no diretório "dados":

    ![alt text](arquivosGerados.png)

## 2. Ordenação de dados:
-  **Execução:**
    - Para executar os códigos basta rodar os seguintes comandos:
        - **Linux**:
            ```shell
                >> g++ codigo/ordenacao.cpp && ./a.out
            ```
            - **Windows**:
            ```shell
                >> g++ codigo/ordenacao.cpp
                >> ./a.exe
            ```
- **Resultado:**
    - O resultado dessa execução deve ser a quantidade de números ordenados, o método de ordenação utilizado, o tempo decorrido (em segundos), o número de comparações e o número de trocas de posição:
    ![alt text](outputGerador.png)

    - Os arquivos .bin com a ordenação crescente dos arquivos gerados anteriormente também estarão localizados no diretório "dados":

    ![alt text](arquivosGerados.png)

## 3. Busca de dados:
