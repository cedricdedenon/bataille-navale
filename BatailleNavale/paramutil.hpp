#ifndef PARAMUTIL_HPP
#define PARAMUTIL_HPP

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QComboBox>
#include <QStringList>
#include <QGroupBox>
#include <QVector>
#include <QTextEdit>
#include <QCloseEvent>
#include "navire.hpp"
#include "grille.hpp"
#include "utilisateur.hpp"


class ParamUtil: public QWidget
{
Q_OBJECT

public:
    ParamUtil();

public slots:
    void parametresVisible();
    void parametresNonVisible();
    void selectionCoordonnees();

private slots:
    void closeEvent(QCloseEvent *event);

private:
    QPushButton *m_boutonOK;
    QRadioButton *m_placementAuto;
    QRadioButton *m_placementManuel;
    QVector<QComboBox*> m_coordXY;
    QVector<QComboBox*> m_orientation;
    QVector<Navire> m_navires;
    bool m_placementManuelOK;

public:
    bool getPlacementAuto();
    bool getPlacementManuel();
    QVector<Navire> getNavires();
    QPushButton* getboutonOK();

signals:
    void paramUtilisateurOK();
};


#endif // PARAMUTIL_HPP
