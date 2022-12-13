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

 

## Referências
