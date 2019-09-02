#ifndef BATAILLENAVALEFEN_HPP
#define BATAILLENAVALEFEN_HPP

#include <QApplication>
#include <QtWidgets>
#include <QLineEdit>
#include <QTableWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVector>
#include "navire.hpp"
#include "grille.hpp"
#include "utilisateur.hpp"
#include "ordinateur.hpp"
#include "optionsfen.hpp"
#include "paramutil.hpp"

class BatailleNavaleFen: public QMainWindow
{
Q_OBJECT
public:
    BatailleNavaleFen();
    ~BatailleNavaleFen();

public slots:
    void algo();
    void rejouer();
    void options();
    void grilleSolution();
    void grilleSolutionCache();
    void parametreUtilisateur();

private slots:
    void closeEvent(QCloseEvent *event);

private:
    QPushButton *m_boutonOK;
    QPushButton *m_boutonQuit;
    QPushButton *m_boutonRejouer;
    QPushButton *m_boutonSolution;
    QPushButton *m_boutonSolutionCache;
    QTableWidget *m_grilleHaut;
    QTableWidget *m_grilleBas;
    QTableWidget *m_grilleHautOrdi;
    QTableWidget *m_grilleBasOrdi;
    QLineEdit *m_lineedit;
    QTextEdit *m_navDetruitHaut;
    QTextEdit *m_navDetruitBas;
    OptionsFen m_options;
    ParamUtil m_paramUtil;

public:
    void init();
    void initHeaderTab();
    void init1J(QTableWidgetItem *itemBas,QTableWidgetItem *itemHaut);
    void init2JUtilisateur(QTableWidgetItem *itemBas,QTableWidgetItem *itemHautOrdi);
    void init2JOrdinateur(QTableWidgetItem *itemBasOrdi,QTableWidgetItem *itemHaut);
    void algo1J(QTableWidgetItem *itemHaut);
    void algo2JUtilisateur(QTableWidgetItem *itemHaut,QTableWidgetItem *itemBasOrdi);
    void algo2JOrdinateur(QTableWidgetItem *itemHautOrdi,QTableWidgetItem *itemBas);
};

#endif // BATAILLENAVALEFEN_HPP
