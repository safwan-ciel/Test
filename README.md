\documentclass{article}
\usepackage{xcolor}
\usepackage{listings}
# Projet Qt - Gestion des notes des joueurs


\lstset{
    backgroundcolor=\color{lightgray},   % couleur de fond
    basicstyle=\ttfamily,                % police de base
    keywordstyle=\color{blue},           % couleur des mots-clés
    commentstyle=\color{green},          % couleur des commentaires
    stringstyle=\color{red},             % couleur des chaînes
}

\begin{document}

\begin{lstlisting}[language=Python]
# Ceci est un commentaire
def hello_world():
    print("Hello, World!")  # Affiche un message
\end{lstlisting}

\end{document}
## Description
Ce projet utilise Qt pour créer une interface graphique permettant d'afficher, de modifier et de mettre à jour des notes (ratings) des joueurs dans une base de données MySQL. Les notes sont représentées sous forme d'étoiles et peuvent être modifiées par l'utilisateur dans une table.

# Prérequis
Avant de commencer, vous devez avoir installé les éléments suivants sur votre machine :

- **Qt 5 ou 6 :** pour le développement de l'interface graphique.
- https://download.qt.io/official_releases/qtcreator/15.0/15.0.0/qt-creator-opensource-linux-x86_64-15.0.0.run
- **MySQL :** pour la gestion de la base de données.
  - `sudo apt upgrade`
  - `sudo apt install mysql-server`
  - `mysqladmin -u root password 'mot_de_passe'`
  - Ensuite créer une base de données avec la commande `CREATE DATABASE nomdevotrebasededonnees;`
  - Ensuite pour pouvoir faire des requêtes SQL il faut créer un autre utilisateur :
  - `CREATE USER 'nom_utilisateur'@'hôte' IDENTIFIED BY 'mot_de_passe';`
  - `GRANT ALL PRIVILEGES ON *.* TO 'nom_utilisateur'@'loclahost;'`

Création de la base de données : Une fois MySQL installé et en cours d'exécution, créez une base de données avec une table pour stocker les informations des joueurs. Voici un exemple de script SQL :


Copier le code

`CREATE DATABASE foot;
USE foot;`

`CREATE TABLE jeu (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nom VARCHAR(100),
    club VARCHAR(100),
    rating INT
);`

INSERT INTO jeu (nom, club, rating) VALUES
('Joueur1', 'ClubA', 3),
('Joueur2', 'ClubB', 5),
('Joueur3', 'ClubC', 4);

Configuration de la connexion à la base de données : Dans le code source, assurez-vous de configurer correctement ***votre nom d'utilisateur*** et ***votre mot de passe MySQL*** dans le fichier main.cpp :


Copier le code

db.setUserName("votre_utilisateur");
db.setPassword("votre_mot_de_passe");

## Utilisation

-**Lancer l'application :** Compilez et exécutez le projet avec Qt Creator ou en ligne de commande avec `qmake` et `make`.

-**Interface graphique :** L'application affichera une table avec les informations des joueurs, y compris leur nom, leur club, et leur note sous forme d'étoiles.

-**Modifier une note :** Double-cliquez sur la colonne "Rating" pour modifier la note d'un joueur. La nouvelle note sera automatiquement mise à jour dans la base de données.

## Fonctionnement du code

-**Interface graphique :**
L'application utilise un `QTableWidget` pour afficher les informations des joueurs. Chaque ligne représente un joueur et la colonne "Rating" affiche sa note sous forme d'étoiles.

-**Mise à jour de la base de données :**
Lorsque l'utilisateur modifie une note, la fonction updateRatingInDatabase est appelée pour mettre à jour la base de données MySQL avec la nouvelle note.

-**Gestion de l'édition des notes :**
La classe StarRating est utilisée pour afficher et gérer les étoiles, et un délégué personnalisé (StarDelegate) permet à l'utilisateur de modifier les notes.
