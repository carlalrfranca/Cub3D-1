![(https://github.com/42Paris/minilibx-linux/actions/workflows/ci.yml/badge.svg)](https://img.shields.io/badge/norminette-100%25-green)
# Cub3D

Desenvolver um projeto usando raycasting. Um método de implementar jogos emulando ambiente 3D em um 2D. Para que isso aconteça algumas limitações são necessárias como os cubos serem do mesmo tamanho, paredes perpendiculares <br>

Objetivo <br>

O que é feito a principio<br>
Se for usar algum argumento como será aplicado<br>

[**Mais**](https://bumpy-truffle-c97.notion.site/cub3D-miniRT-e85fe30656d84ecaaa03b30cac114b79)

## Sobre o repositório

- [**Cub3D**](./cub3d/) : arquivo contendo o código-fonte da aplicação
- [**Info**](./Concept.md/) : conceitos e aprendizados necessários

## Tecnologias utilizadas

- [**Analysis tool**](https://valgrind.org/docs/manual/manual-core-adv.html) : software para depuração e localização de erros.
- [**C**](https://www.iso.org/standard/74528.html) : linguagem compilada e estruturada escolhida para o desenvolvimento do cub3d.
- [**Excalidraw**](https://excalidraw.com/) : ferramenta utilizada para criar diagramas.
- [**Git**](https://git-scm.com/) : para controle das versões dos arquivos.
- [**Github**](https://github.com/42sp/42labs-selection-process-v3-carlalrfranca) : repositório para os arquivos.
- [**Makefile**](https://www.gnu.org/software/make/) : script aplicado para automatizar a compilação do projeto.
- [**Mermaid**](https://mermaid-js.github.io/mermaid/#/) : ferramenta para desenhar em arquivos markdown os diagramas de bloco.
- [**Trello**](https://trello.com/b/mz8GGxfd/cub3d#) : ferramenta visual para planejamento e organização.
- [**Stackedit**](https://stackedit.io/) : editor Markdown para escrever a documentação do projeto.
- [**Vscode**](https://code.visualstudio.com/) : editor usado para o desenvolvimento de código-fonte.
- [**Peek**](https://linuxhint.com/install-peek-animated-gif-recorder-linux/) gravador de telas. Usado para criar o .gif do Cub3D implementado.
<!-- - [**screentogif**](https://www.screentogif.com/) : grava telas. Usado para criar um arquivo .gif do Cub3D implementado. -->

## Header, bibliotecas e outros projetos

- [**Markdown**](https://www.markdownguide.org/) : linguagem de marcação padronizada para formatação de textos Web, usada para escrever a documentação.
- [**MinilibX**](https://github.com/42Paris/minilibx-linux) : biblioteca usada para renderização gráfica.
- [**Math.h**](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/math.h.html) : arquivo de cabeçalho que disponibiliza funções matemáticas.
- **LibFT** : primeira implementação proposta pela École42, onde algumas funções foram recriadas da biblioteca C e inseridas para complementar o desenvolvimento.
<!-- - [**MinilibX**](https://aurelienbrabant.fr/blog/getting-started-with-the-minilibx) -->

## Outline

#### **Divisão em duas fases**
- Na primeira fase foi feito o tratamento dos dados e inserção nas estruturas, também a autenticação do mapa. 
- A segunda fase foi criado 

## Funções Principais

#### Primeira fase:

Explica explica <br>
![alt image text](image.jpg)

#### Segunda fase:

Explica explica <br>
![alt image text](image.jpg)

## Acesso

#### Repo
```
git clone https://github.com/carlalrfranca/cub3D
```

#### Compilação e execução

 - cd cub3d : acessa o diretório
 - make : compila o projeto
 - make clean : remove objetos
 - make fclean : remove objetos e arquivos binários
 - make re  : recompila
 - ./cub3d : executa

#### Códigos usados e depuração

- `$ comando [OPÇÕES]` : sintaxe do comando XXX
- `valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ` : depuração completa

| Comando               | Descrição                                                  |
|:----------------------|:-----------------------------------------------------------|
| --track-origins=yes   | <sub> rastreia as origens de valores não iniciados </sub>  |
| --leak-check=full     | <sub> retorna o detalhamento dos vazamentos </sub>         |
| --show-leak-kinds=all | <sub> relatório completo dos vazamentos </sub>             |

- `valgrind --leak-check=full --show-leak-kinds=all ./cub3d ./maps/map.olar` <br>
- `valgrind --leak-check=full --show-leak-kinds=all ./cub3d ./maps/map.cub` <br>

## Miscelanea

#### Peek

`$ sudo apt install peek` <br>
`$ peek --version` <br>
`$ sudo apt update` <br>
`$ sudo apt remove --autoremove peek` <br>
