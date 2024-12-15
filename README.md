\documentclass[a4paper,12pt]{article}
\usepackage{hyperref}

\title{Projet Qt - Gestion des notes des joueurs}
\author{Votre nom}
\date{\today}

\begin{document}

\maketitle

\section*{Description}

Ce projet utilise Qt pour créer une interface graphique permettant d'afficher, de modifier et de mettre à jour des notes (ratings) des joueurs dans une base de données MySQL. Les notes sont représentées sous forme d'étoiles et peuvent être modifiées par l'utilisateur dans une table.

\section*{Prérequis}

Avant de commencer, vous devez avoir installé les éléments suivants sur votre machine :

\begin{itemize}
    \item \textbf{Qt 5 ou 6} : pour le développement de l'interface graphique.
    \item \textbf{MySQL} : pour la gestion de la base de données.
    \item \textbf{Qt SQL module} : pour interagir avec la base de données MySQL.
\end{itemize}

\section*{Installation}

\subsection*{1. Installer Qt}

Si vous n'avez pas encore installé Qt, vous pouvez le télécharger et l'installer depuis le site officiel : \href{https://www.qt.io/download}{Qt Installer}.

\subsection*{2. Installer MySQL}

Téléchargez et installez MySQL sur votre machine à partir de \href{https://dev.mysql.com/downloads/}{MySQL Downloads}. Assurez-vous que MySQL est bien en cours d'exécution.

\subsection*{3. Création de la base de données}

Une fois MySQL installé et en cours d'exécution, créez une base de données avec une table pour stocker les informations des joueurs. Voici un exemple de script SQL :

\begin{verbatim}
CREATE DATABASE foot;
USE foot;

CREATE TABLE jeu (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nom VARCHAR(100),
    club VARCHAR(100),
    rating INT
);

INSERT INTO jeu (nom, club, rating) VALUES
('Joueur1', 'ClubA', 3),
('Joueur2', 'ClubB', 5),
('Joueur3', 'ClubC', 4);
\end{verbatim}

\subsection*{4. Configuration de la connexion à la base de données}

Dans le code source, assurez-vous de configurer correctement votre nom d'utilisateur et votre mot de passe MySQL dans le fichier \texttt{main.cpp} :

\begin{verbatim}
db.setUserName("votre_utilisateur");
db.setPassword("votre_mot_de_passe");
\end{verbatim}

\section*{Utilisation}

\subsection*{1. Lancer l'application}

Compilez et exécutez le projet avec Qt Creator ou en ligne de commande avec \texttt{qmake} et \texttt{make}.

\subsection*{2. Interface graphique}

L'application affichera une table avec les informations des joueurs, y compris leur nom, leur club, et leur note sous forme d'étoiles.

\subsection*{3. Modifier une note}

Double-cliquez sur la colonne ``Rating'' pour modifier la note d'un joueur. La nouvelle note sera automatique
