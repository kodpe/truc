# TODO-LIST

---
### MVP
- [ ] game checkboard
- [x] basic events
- [ ] charger les xpm
- [x] position mouse
- [x] event mouse
- [x] event Keyboard
- [x] triangle struct
- [x] point - triangle intersection
- [x] square grid
- [x] circular grid
- [ ] fog war
- [ ] game tiles

---
### ADD-ONS
- [ ] Multijoueur
- [ ] Trouver un nom pour le jeu
- [ ] Passer les structures mx em ptr c'est mieux
- [ ] Implémenter les OBB
- [ ] Aligner les logs()
- [ ] Bloquer les signaux C-c C-\
- [ ] Ajouter photo de profil

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
