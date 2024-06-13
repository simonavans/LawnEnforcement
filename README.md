# Story
The sunday morning at 7 AM feels quiet. A little... too quiet. You feel that something is off until you realize it.
The grass! It's getting too long again! Being the crappy neigbor that you are, you start up the lawn mower, waking
up dozens of angered people in the process.
	But then you notice an unnatural object through the weeds. It seems the neighborhood has had enough of your
mowing activities, since they have installed mines all over your lawn! Get ready to test your mine defusing skills
in the game where Minesweeper meets gardening chores!

Find the showcase video on [YouTube](https://www.youtube.com/watch?v=a7ECmH7Ih2Y).

# Controls
The game is controlled in first person mode. Look around by moving the mouse. Control your movements with the w, a,
s and d keys.

The player can work with two Minesweeper tools: the lawn mower and the flag. Only one tool can be wielded at any
time. The player starts off with the lawn mower equipped. With this tool, lawn tiles can be clicked to reveal their
type (e.g. a bomb tile). By scrolling with the scroll wheel, pressing the up or down arrow or pressing e, the player
equips the flag tool. Clicking lawn tiles with this tool equipped flags that tile. Hitting one of the mentioned keys
again equips the lawn mower again.

# Gameplay
Don't know the game rules?? Alright, it's very simple:
- Mowing any lawn tile reveals whether the tile has a mine or not. Unmowed tiles hide this information.
- The objective is to mow all tiles that don't have a mine, and to flag all tiles you suspect to contain a mine. If you mow a tile with a mine, then it's game over for you and your beautiful lawn.
- Every mowed tile without a mine shows how many neighboring mine tiles it has. Diagonal tiles count as neighbors as well. If a tile has just grass on it, it has zero neighbors.
- You must deduce which tiles have a mine by reading the amount of neighboring mines on each tile. Flag suspected mine tiles by clicking the tiles with the flag tool.
- Correctly flagging all mine tiles and mowing all other tiles (or losing the game) reveals all tiles. If you lost, you can see exactly where the bombs were located.

More info on [wikipedia](https://en.wikipedia.org/wiki/Minesweeper_(video_game))

# Game settings
The game settings, such as map size, can be changed by editing the text-file inside the `config` directory.

# Unit tests
Unit tests are enabled in debug mode. By running the program, the result of each unit test will be written to `unit_tests/result.txt`. Note that all of the game settings must have their default values set for the unit tests to execute successfully. Unit tests can be disabled by running the program in release mode.

# Table of criteria (in Dutch)

| Criterium                                                                                                                                                          | Voldaan | Bestand/klasse (evt regelnummer)                                                                                             |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------- | ---------------------------------------------------------------------------------------------------------------------------- |
| De code bevat geen overbodige \#defines en bevat geen magische constanten.                                                                                         | Ja      | N.v.t.                                                                                                                       |
| Gebruik maken van OO-principes in C++, zoals gebruik van klassen met constructors en destructors, polymorfisme en/of inheritance.                                  | Ja      | Klassen GameObject, Component en overervende klassen                                                                         |
| De code gebruikt op ten minste 1 plek op een zinnige wijze van overerving en virtuele<br>functie(s).                                                               | Ja      | Bijvoorbeeld klasse DrawComponent                                                                                            |
| De code heeft ten minste 1 unit-test waarbij het resultaat in een bestand wordt weggeschreven.                                                                     | Ja      | UnitTests.cpp                                                                                                                |
| Met behulp van FileIO, bestanden kunnen lezen en schrijven.                                                                                                        | Ja      | Klasse SettingsLoader                                                                                                        |
| Toepassen van standaard datastructuren in C++.                                                                                                                     | Ja      | Scene.cpp, constructor, vanaf regel 14                                                                                       |
| Gebruik maken van streams.                                                                                                                                         | Ja      | SettingsLoader.cpp, constructor, regels 16 en 20.                                                                            |
| Rekening gehouden met het voorkomen van memory leaks.                                                                                                              | Ja      | Zie criterium 'Smart pointers'                                                                                               |
| Zinnige foutmeldingen mocht er iets fout gaan, afhandeling via exceptions.                                                                                         | Ja      | SettingsLoader.cpp, functie readFile(), regels 36, 60, 67, 74 en 81.                                                         |
| Gebruik maken van C++ standaard, dus niet op C manier alloceren.                                                                                                   | Ja      | Zie criterium 'Smart pointers'                                                                                               |
| Weloverwogen gebruik van algoritmes binnen de applicatie (zowel zelfgeschreven alsmede de STL-bibliotheek).                                                        | Ja      | Scene.cpp, functie generateLawn(), vanaf regel 69                                                                            |
| Smart pointers.                                                                                                                                                    | Ja      | Bijvoorbeeld Game.cpp, constructor, vanaf regel 17                                                                           |
| Gebruik maken van Template Metaprogramming.                                                                                                                        | Ja      | Klasse GameObject, functies removeComponent() en getComponent()                                                              |
| Ervoor zorgen dat je programma const, constexpr en override correct is.                                                                                            | Ja      | Overrides: bijvoorbeeld klasse DrawComponent. Const en constexpr: bijvoorbeeld Scene.cpp, regels 104, 105 en regels 116, 117 |
| Lambda expressies, denk hierbij ook aan een typedef.                                                                                                               | Ja      | LawnEnforcement.cpp, regels 40 en 44                                                                                         |
| Pointer to implementation, scherm een structure of klasse af.                                                                                                      | Ja      | Game.h, attribuut equippedTool (regel 22) en het gebruik ervan (Game.cpp, functie swapTools(), vanaf regel 124)              |
| De code voldoet aantoonbaar aan andere, wenselijke (kwaliteit verhogende) en gespecificeerde criteria. (Zinvol commentaar en het gebruik van een static variabele) | Ja      | Zinvol commentaar: bijvoorbeeld Scene.cpp, functie generateLawn(), vanaf regel 69. Static variabele: Game.cpp, regel 152.    |
