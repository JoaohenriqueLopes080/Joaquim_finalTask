# Trabalho Final de Lógica de Algoritmo - Jogo de Tabuleiro

## Descrição

Este projeto, desenvolvido como Trabalho Final do 1º semestre da disciplina de Lógica de Algoritmo Do Professor Joaquim.
Consiste no desenvolvimento de um algoritmo que segue o exemplo de Xadrez, onde temos 3 Peças.

- **Peça X**
- **Peça Y**
- **Peça Z**

## Regras Gerais

- O tabuleiro possui **5 linhas** e **6 colunas**.
- Cada jogador controla três peças diferentes: `x`, `y`, `z` (minúsculas para um jogador, maiúsculas para o outro).
- As peças são posicionadas inicialmente conforme o enunciado do trabalho.
- Cada tipo de peça possui regras próprias de movimentação:
  - **Peça X:** Move-se até 2 casas em qualquer direção (horizontal, vertical ou diagonal), desde que o caminho não esteja bloqueado.
  - **Peça Y:** Move-se exatamente 2 casas, somando linha e coluna, podendo ser em "L" ou reto, sem obstáculos.
  - **Peça Z:** Move-se até 2 casas apenas em linha reta (horizontal ou vertical), sem obstáculos e não pode capturar a peça Y adversária.
- O jogo é realizado em turnos, onde o jogador informa a posição de origem e destino da peça que deseja mover.
- O movimento só é realizado se for válido conforme as regras da peça.

## Feito Por João Henrique, Nilo Maraschin E Vitor Da Penha
