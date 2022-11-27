# TODO-LIST

---
### MVP
- [x] Multiplayer lobby
- [ ] mx_reset_image()
- [ ] mouse react over pieces
- [ ] Multiplayer game
- [x] Bloquer les signaux C-c C-\
- [x] Ajouter photo de profil
- [ ] game checkboard
- [x] basic events
- [x] charger les xpm
- [x] position mouse
- [x] event mouse
- [x] event Keyboard
- [x] triangle struct
- [x] point - triangle intersection
- [x] square grid
- [x] circular grid
- [ ] fog war
- [ ] game tiles
- [ ] Fix CAPSLOCK

---
### ADD-ONS
- [ ] Trouver un nom pour le jeu
- [ ] Passer les structures mx em ptr c'est mieux
- [ ] Implémenter les OBB
- [ ] Aligner les logs()
- [ ] protection vs +3 exec at same time, game integrity
- [ ] protection of data in com file

---
### RULES

- [ ] Placement des pièces.
- [ ] Déplacement ou parachutage d'une pièce.
- [ ] Amélioration des mouvements des pièces.

```
- Placement des pièces.
- Déplacement ou parachutage d'une pièce.
- Temps d'amélioration des mouvements.
- Toutes les pièces et cases perdues peuvent récupérées et réintroduites dans la partie avec un parachutage.
- A chaque tour le joueur peut déplacer un personnage sur une case adjacente libre ou occupée par un autre personnage et/ou case spéciale.
- Si le personnage est sur une montagne sa portée est doublée mais il ne peut plus aller sur les cases adjacentes à la montagne.
```

#### Personnages

Name | Can move | Description
- | - | -
Samourai . Guerrier | ``YES`` | Gagne les points portés par les personnages vaincus.
Shinobi . Ninja     | ``YES`` | La grille de jeu n'a pas de limites.
Ryu . Dragon     	| ``YES`` | Invincible en défense. Perd toujours si il attaque un personnage.
Yama-Uba . Sorcière | ``YES`` | Prend l'apparence et les capacités de la dernière case visitée ou du dernier personnage vaincu.

#### Cases
Name | Can move | Description
- | - | -
Chochin . Lanterne  | ``NO``  |	Révèle le contenu des cases accessibles au personnage présent sur la lanterne. Elle est détruite si l'ennemi arrive dessus.
Renge . Lotus       | ``NO``  | Offre une deuxième vie à un personnage. Il est détruit à sa place.
Yama . Montagne     | ``NO``  | Double la portée du personnage allié ou ennemi présent sur la case. Ne peut etre détruit.
Shiro . Chateau     | ``NO``  | Le joueur qui s'empare du chateau de son adverse gagne la partie.

#### Computer AI
	/*
	- placer ses 8 pièces de manière aléatoire
		- chateau sur la ligne du fond
		- dragon devant le chateau
		- les autres pieces position random
	- choisir une pièce sur le board sauf le dragon ou une pièce à parachuter
	- choisir une case de destination parmi les positions possibles
	- si chateau position inconnue :
		tester le plus vite possible les 10 cases adverses pour trouver le chateau
	- si chateau position trouvée :
		rush le chateau ennemi
	*/
