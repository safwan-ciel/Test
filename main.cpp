#include "widget.h"
#include "StarDelegate.h"
#include "StarEditor.h"
#include "StarRating.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QTableWidget>

void populateTableWidget(QTableWidget *tableWidget)
{
    //Création d'un tableau de structures rprésentant la base de donnéees
    static struct {
        QString id;
        QString nom;
        QString club;
        int rating;
    } staticData[] = {
        {},
        { nullptr, nullptr, nullptr, 0 }
    };

    //Chaque colonne de la BDD est affiliée à un item
    for (int row = 0; staticData[row].id != nullptr; ++row) {
        QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].id);
        QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].nom);
        QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].club);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setData(0,  QVariant::fromValue(StarRating(staticData[row].rating)));

        tableWidget->setItem(row, 0, item0);
        tableWidget->setItem(row, 1, item1);
        tableWidget->setItem(row, 2, item2);
        tableWidget->setItem(row, 3, item3);
    }

}

//-------------------------------------------------------------------------------------------------//

//Fonction qui permet de modifier la note dans la BDD
void updateRatingInDatabase(const QString &id, int newRating, QSqlDatabase &db)
{
    // Vérifier si la base de données est ouverte
    if (!db.isOpen()) {
        qDebug() << "La base de données n'est pas ouverte!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE jeu SET rating = :rating WHERE id = :id");
    query.bindValue(":rating", newRating);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour de la note dans la base de données:" << query.lastError().text();
    } else {
        qDebug() << "Note mise à jour pour le joueur avec l'ID:" << id;
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Enregistrement du type StarRating
    qRegisterMetaType<StarRating>("StarRating");

    QTableWidget tableWidget;
    tableWidget.setColumnCount(4);

    Widget w;

    //Ouverture de la BDD sous le nom "bd"
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("TP5");

    db.setUserName("invite");
    db.setPassword("invite");
    if(db.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << db.hostName();

        QSqlQuery query;

        //Envoi d'une requête SQL qui séléctionne tous les éléments de la BDD
        query.exec("SELECT * FROM jeu");

        //Tant que la colonne n'est pas nulle
        while(query.next())
        {
            //On enregistre l'id, le nom, et le club dans des variables
            QString ID = query.value(0).toString();
            QString Nom = query.value(1).toString();
            QString Club = query.value(2).toString();

            //Affichage dans la console des éléments enrgistrés
            qDebug() << "\t |-----------------------------------------------------";
            qDebug() << "\t |" << ID << "\t |" << Nom << "\t |" << Club << "\t |";

            //Index de ligne
            int row = tableWidget.rowCount();

            tableWidget.insertRow(row);
            tableWidget.setItem(row, 0, new QTableWidgetItem(ID));
            tableWidget.setItem(row, 1, new QTableWidgetItem(Nom));
            tableWidget.setItem(row, 2, new QTableWidgetItem(Club));


            QTableWidgetItem *item3 = new QTableWidgetItem;
            item3->setData(Qt::UserRole, QVariant::fromValue(StarRating(5)));// Remplacez 5 par la valeur appropriée
            tableWidget.setItem(row, 3, item3);

            // DEBUG : Affichez la donnée insérée pour la colonne Rating
            qDebug() << "Donnée insérée pour Rating (ligne" << row << "):"
                     << tableWidget.item(row, 3)->data(Qt::UserRole);

            row++; // Incrémenter l'index de ligne

        }

        qDebug() << "\t |-----------------------------------------------------";
        qDebug() << "Requete OK !";
    }

    else
    {
        qDebug() << "La connexion a échouée, désolé" << db.lastError().text();
    }

        //Création du tableau dans la fenêtre
        tableWidget.setItemDelegateForColumn(3, new StarDelegate);

        tableWidget.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        tableWidget.setSelectionBehavior(QAbstractItemView::SelectRows);

        //Nom de chaque colonne du tableau
        tableWidget.setHorizontalHeaderLabels({"ID", "Nom", "Club", "Rating"});

       populateTableWidget(&tableWidget);

        //Taille du tableau
        tableWidget.resizeColumnsToContents();
        tableWidget.resize(500, 300);

        //Affichge du tableau
        tableWidget.show();

        // Connecter le signal de changement de valeur à la mise à jour de la base de données
        QObject::connect(&tableWidget, &QTableWidget::itemChanged, [&](QTableWidgetItem *item) {
            if (item->column() == 3) {  // Si l'élément changé est dans la colonne des notes
                QString playerId = tableWidget.item(item->row(), 0)->text();  // Récupérer l'ID du joueur
                int newRating = item->data(Qt::UserRole).value<StarRating>().getRating();  // Récupérer la nouvelle note
                updateRatingInDatabase(playerId, newRating, db);
            }
        });


    return a.exec();

    //Déconnexion à la BDD
    db.close();
}

