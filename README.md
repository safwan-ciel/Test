# Projet Qt - Gestion des notes des joueurs

## Description
Ce projet utilise Qt pour créer une interface graphique permettant d'afficher, de modifier et de mettre à jour des notes (ratings) des joueurs dans une base de données MySQL. Les notes sont représentées sous forme d'étoiles et peuvent être modifiées par l'utilisateur dans une table.

# Prérequis
Avant de commencer, vous devez avoir installé les éléments suivants sur votre machine :

- **Qt 5 ou 6 :** pour le développement de l'interface graphique.
- **MySQL :** pour la gestion de la base de données.
  - `sudo apt upgrade`
  - `sudo apt install mysql-server`

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
