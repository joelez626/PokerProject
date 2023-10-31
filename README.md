# PokerProject
C++ Program that contains several poker games

## Table of contents
1. [Introduction](#introduction)
2. [Changelog](#changelog)

### Introduction <a name="introduction"></a>
This is a basic text-based program where we can play different poker games on the console. The games include:
1. Texas Hold 'Em Poker (In progress)
... More to come
There are algorithms to determine the winner in each round and each game.

Here, C++ was used due to the extensive available algorithms in the Standard Template Library (STL) and the performance. It is also portable as the release will be in .exe format and does not require an interpreter. Object-Oriented Programming (OOP) is the main structure of the program, where there are classes for Cards and Decks/Hands.

Poker has been one of my favorite card games due to its simplicity to pick up. However, the games are typically difficult to master, as it involves strategy to make the best of what you have. One of the biggest challenges for me was the use of pointers - raw pointers are prone to errors and undefined behavior (dangling pointers, memory leaks, double deletion). Most importantly, I learned how to use OOP, as well as debug and troubleshoot my program using Visual Studio.

### Changelog <a name="changelog"></a>
v0.1.0 (Build #1)
- Added framework for Cards and Decks
- Basic functions for Texas Hold 'Em Poker
  - Deal random cards based on number of players
  - Evaluate best hand and determine winner
