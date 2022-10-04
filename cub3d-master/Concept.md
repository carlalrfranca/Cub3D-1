# Info

## Pontos Fortes (lembrar na implementação)
* Ray Casting é uma técnica de renderização (90's) que "emula" um ambiente 3D em um 2D;
* Ele transforma uma forma limitada de dados (mapas simples ou plantas baixas) em uma projeção 3D;
* Considerado uma subclasse do Ray Tracing;
* Ambos determinam a visibilidade das superfícies traçando raios imaginários de luz do olho do espectador até o objeto na cena, sendo que o Ray Casting lança uma quantidade menor de raios;
* A diferença primordial entre eles é que o Ray Casting é mais rápido por trabalhar com restrições geométricas, dessa forma acelera o processo de renderização;
Exemplo: em uma resolução de tela de 320×200, um ray-caster traça apenas 320 raios (o número 320 vem do fato de que a tela tem 320 pixels horizontais de resolução, portanto 320 colunas verticais).<br>
O ray tracing é mais indicado para imagem estatica;<br>

### Sobre as restrições do Ray Casting: 
Paredes sempre em ângulo de 90 graus em relação ao chão; <br>
Paredes sempre feitas com cubos do mesmo tamanho; <br>
Piso sempre plano; <br>

#### Necessário:
Cubos múltiplos de 2, dessa forma facilita as operações de deslocamento aritmético;<br>
Essas operações são mais rápidas que multiplicação ou divisão;<br>
Quanto maior o tamanho do cubo, mais em bloco o mundo parecerá;<br>

#### Sobre FOV (ponto de vista):
O jogador deve ser capaz de ver o que está a sua frente; <br>
Na tela o FOV não fica legal com 90 graus; 
Geralmente definimos em 60 graus (ajuste por teste e experimentação); <br>
A altura do jogador é definida como 32 unidades porque é uma suposição razoável considerando 64 unidades de altura <br>
Para colocar o jogador dentro do mundo precisamos definir os três atributos que formam o FOV do jogador: <br>
As coordenadas X e Y do jogador e o ângulo para o qual o jogador está de frente; <br>

#### Traçando Cenas:
 Podemos traçar o raio para cada coluna vertical da tela. <br>
 Então se temos uma tela de 320 X 200 pixels, teremos 320 linhas verticais <br>
 Sendo a coluna 0 o raio de extrema esquerda e a coluna 319 o raio de extrema direita <br>
 Ou seja, vamos renderizar traçando da esquerda para direita <br>
 Isso pode ser feito em um loop <br>
 
 <pre>
 Com base no ângulo de visão, subtraia 30 graus (metade do FOV).
 A partir da coluna 0:
 Lança um raio.
 Trace o raio até que ele atinja uma parede.
 Registre a distância até a parede (a distância é igual ao comprimento do raio).
 Adicione o incremento do ângulo para que o raio se mova para a direita (o valor do incremento do ângulo é 60/320 graus).
 Repita os passos 2 e 3 para cada coluna subsequente até que todos os 320 raios sejam lançados.
 </pre>

## Referências
