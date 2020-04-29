# Groupe d'Habi_a & Courta_f & Jargal_m & Souiss_y

## Nécessité

### _Afin de faire fonctionner notre programme, nous avons besoin de :_

- **Docker OU une machine Linux/Mac avec gcc make et les libsdl2 installées**

### _Installation et lancement du projet :_

- **$> git clone {projet}**
- **$> cd {projet}**

Si utilisation de docker:
- **$> docker build -t bomberman .**
- **$> docker run --rm -it -v ${PWD}:/app sdl_project**

Ensuite:
- **$> cd {projet}**
- **$> make**
- **$> ./bomberman**

### _Informations Supplémentaire :_

#### _Héberger une partie :_

- **Héberger une partie**
- **Choix d'une map (1/2)**
- **Temps maximum (en minute)**
- **Nombre de bombe maximum**
- **Ajout d'un port (par exemple 94200)**
- **Attendre la connexion des joueurs !**

#### _Rejoindre une partie :_

- **Rejoindre une partie**
- **Ajout de l'adresse de l'hébergement**
- **Ajout du port utilisé par l'hébergement !**
- **Enjoy**

#### _Touches :_

- **Haut = Flèche du Haut**
- **Bas = Flèche du Bas**
- **Gauche = Flèche de Gauche** 
- **Droite = Flèche de Droite** 
- **Action = Espace**
