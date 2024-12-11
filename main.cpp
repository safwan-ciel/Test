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

// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


//! [0]
void populateTableWidget(QTableWidget *tableWidget)
{
    static struct {
        QString id;
        QString nom;
        QString club;
        int rating;
    } staticData[] = {
        //! [0] //! [1]
        {},
        //! [1]

        //! [2]
        { nullptr, nullptr, nullptr, 0 }
        //! [2] //! [3]
    };
    //! [3] //! [4]
    //!

    for (int row = 0; staticData[row].id != nullptr; ++row) {
        QTableWidgetItem *item0 = new QTableWidgetItem(staticData[row].id);
        QTableWidgetItem *item1 = new QTableWidgetItem(staticData[row].nom);
        QTableWidgetItem *item2 = new QTableWidgetItem(staticData[row].club);
        QTableWidgetItem *item3 = new QTableWidgetItem;
        item3->setData(0,
                       QVariant::fromValue(StarRating(staticData[row].rating)));

        tableWidget->setItem(row, 0, item0);
        tableWidget->setItem(row, 1, item1);
        tableWidget->setItem(row, 2, item2);
        tableWidget->setItem(row, 3, item3);
    }

//-------------------------------------------------------------------------------------------------//

    /*Widget w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("TP5");

    db.setUserName("invite");
    db.setPassword("invite");
    if(db.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << db.hostName();

        QSqlQuery query;

        query.exec("SELECT * FROM jeu");
        while(query.next())
        {
            QString ID = query.value(0).toString();
            QString Nom = query.value(1).toString();
            QString Club = query.value(2).toString();
            qDebug() << "\t |-----------------------------------------------------";
            qDebug() << "\t |" << ID << "\t |" << Nom << "\t |" << Club << "\t |";
            staticData[0].nom = Nom;
        }
        qDebug() << "\t |-----------------------------------------------------";
        qDebug() << "Requete OK !";
        db.close();
    }
    else
    {
        qDebug() << "La connexion a échouée, désolé" << db.lastError().text();
    }
*/
}
//! [4]

//! [5]








int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableWidget tableWidget;
    tableWidget.setColumnCount(4);

    Widget w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("TP5");

    db.setUserName("invite");
    db.setPassword("invite");
    if(db.open())
    {
        qDebug() << "Vous êtes maintenant connecté à " << db.hostName();

        QSqlQuery query;

        query.exec("SELECT * FROM jeu");
        while(query.next())
        {
            QString ID = query.value(0).toString();
            QString Nom = query.value(1).toString();
            QString Club = query.value(2).toString();
            qDebug() << "\t |-----------------------------------------------------";
            qDebug() << "\t |" << ID << "\t |" << Nom << "\t |" << Club << "\t |";
            int row = tableWidget.rowCount();
            tableWidget.insertRow(row);
            tableWidget.setItem(row, 0, new QTableWidgetItem(ID));
            tableWidget.setItem(row, 1, new QTableWidgetItem(Nom));
            tableWidget.setItem(row, 2, new QTableWidgetItem(Club));

            // Vous pouvez également ajouter un item pour le rating ici

            QTableWidgetItem *item3 = new QTableWidgetItem;
            item3->setData(Qt::UserRole, QVariant::fromValue(StarRating(5)));// Remplacez 5 par la valeur appropriée
            tableWidget.setItem(row, 3, item3);

            row++; // Incrémenter l'index de ligne

        }

        qDebug() << "\t |-----------------------------------------------------";
        qDebug() << "Requete OK !";
        db.close();
    }
    else
    {
        qDebug() << "La connexion a échouée, désolé" << db.lastError().text();
    }

        tableWidget.setItemDelegate(new StarDelegate);
        tableWidget.setEditTriggers(QAbstractItemView::DoubleClicked
                                    | QAbstractItemView::SelectedClicked);
        tableWidget.setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget.setHorizontalHeaderLabels({"ID", "Nom", "Club", "Rating"});

       populateTableWidget(&tableWidget);

        tableWidget.resizeColumnsToContents();
        tableWidget.resize(500, 300);
        tableWidget.show();

    return a.exec();
}
