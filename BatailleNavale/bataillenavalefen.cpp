#include "bataillenavalefen.hpp"

//Déclaration des grilles de jeu (utilisateur et ordinateur)
Grille *grilleBas;
Grille *grilleHaut;
Grille *grilleBasOrdi;
Grille *grilleHautOrdi;

//Déclaration de l'utilisateur
Utilisateur *utilisateur = new Utilisateur();

//Déclaration de l'ordinateur
Ordinateur *ordinateur = new Ordinateur();

//Tableau contenant la flotte entière (tous les navires)
Navire tabNavires[NB_NAVIRES];
Navire tabNaviresOrdi[NB_NAVIRES];

//Tableau contenant la taille de tous les navires (décrémente lorsque un navire se fait toucher)
int tabTaille[NB_NAVIRES];
int tabTailleOrdi[NB_NAVIRES];

//Stocke toutes les coordonnées de l'utilisateur dans un tableau dynamique
vector<string> TabchoixUtilisateurIdentique;

//Algorithme de la pseudo-intelligence artificielle
AlgoIA algorithmeIA;


BatailleNavaleFen::BatailleNavaleFen()
{
    QWidget *zoneCentrale = new QWidget;
    QFont maPolice("Arial",9);

    //Déclaration des menus, sous-menus et des actions
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuAide = menuBar()->addMenu("&?");

    QAction *actionNvlPartie = new QAction("&Nouvelle Partie",this);
    QAction *actionOptions = new QAction("&Options",this);
    QAction *actionParametres = new QAction("&Placement navires",this);
    QAction *actionQuitter = new QAction("&Quitter", this);
    QAction *actionAide = new QAction("&Aide",this);
    QAction *actionAPropos = new QAction("&A Propos",this);

    menuFichier->addAction(actionNvlPartie);
    menuFichier->addAction(actionOptions);
    menuFichier->addAction(actionParametres);
    menuFichier->addAction(actionQuitter);
    menuAide->addAction(actionAide);
    menuAide->addAction(actionAPropos);

    //Raccourci pour les menus
    actionNvlPartie->setShortcut(QKeySequence("CTRL+N"));
    actionQuitter->setShortcut(QKeySequence("CTRL+Q"));
    actionOptions->setShortcut(QKeySequence("CTRL+O"));
    actionParametres->setShortcut(QKeySequence("CTRL+P"));
    actionAide->setShortcut(QKeySequence("CTRL+F1"));
    actionAPropos->setShortcut(QKeySequence("CTRL+I"));

    //Fenetre de dialogue pour l'aide
    QDialog *fenaide = new QDialog(zoneCentrale);
    QVBoxLayout *layoutaide = new QVBoxLayout;
    QLabel *labelaide = new QLabel("La bataille navale, appelée aussi touché-coulé, est un jeu de société dans lequel deux joueurs doivent placer "
                                   "des navires sur une grille tenue secrète et tenter de « toucher » les navires adverses.\n"
                                   "Le gagnant est celui qui parvient à torpiller complètement les navires de l'adversaire avant que tous les siens "
                                   "ne le soient.\n\nLa bataille navale oppose deux joueurs qui s'affrontent.\nChacun a une flotte composée de"
                                   " 5 bateaux, qui sont les suivants : 1 porte-avion (5 cases), 1 croiseur (4 cases), 1 contre torpilleur (3 cases), "
                                   "1 sous-marin (3 cases), 1 torpilleur (2 cases).\n\nAu début du jeu, chaque joueur place ses bateaux sur sa grille. "
                                   "\nCelle-ci est toujours numérotée de A à J horizontalement et de 1 à 10 verticalement.\nUn à un, les joueurs vont tirer "
                                   "sur une case de l'adversaire. Par exemple 'B3' ou encore 'H8'.\nLe but est donc de couler les bateaux adverses",fenaide);
    labelaide->setFont(maPolice);
    layoutaide->addWidget(labelaide);
    fenaide->setLayout(layoutaide);

    //Fenetre de dialogue pour l'"A Propos"
    QDialog *fenapropos = new QDialog(zoneCentrale);
    QVBoxLayout *layoutapropos = new QVBoxLayout;
    QLabel *labelapropos = new QLabel("Ce logiciel a été crée par Cédric D.\n\n2016\nTous droits réservés",fenaide);
    labelapropos->setFont(maPolice);
    layoutapropos->addWidget(labelapropos);
    fenapropos->setLayout(layoutapropos);

    //Création et définition des widgets utiles à l'application
    m_boutonOK = new QPushButton("OK", this);
    m_boutonQuit = new QPushButton("Quitter",this);
    m_boutonRejouer = new QPushButton("Nouvelle partie",this);
    m_boutonSolution= new QPushButton("Afficher la solution",this);
    m_boutonSolutionCache= new QPushButton("Cacher la solution",this);
    m_lineedit= new QLineEdit;

    m_grilleHaut= new QTableWidget(N,N,this);
    m_grilleHaut->setFixedSize(420,270);
    m_grilleHaut->resizeColumnsToContents();
    m_grilleHaut->resizeRowsToContents();
    m_grilleBas= new QTableWidget(N,N,this);
    m_grilleBas->setFixedSize(420,270);
    m_grilleBas->resizeColumnsToContents();
    m_grilleBas->resizeRowsToContents();

    m_grilleHautOrdi= new QTableWidget(N,N,this);
    m_grilleHautOrdi->setFixedSize(420,270);
    m_grilleHautOrdi->resizeColumnsToContents();
    m_grilleHautOrdi->resizeRowsToContents();
    m_grilleBasOrdi= new QTableWidget(N,N,this);
    m_grilleBasOrdi->setFixedSize(420,270);
    m_grilleBasOrdi->resizeColumnsToContents();
    m_grilleBasOrdi->resizeRowsToContents();

    m_navDetruitHaut = new QTextEdit;
    m_navDetruitHaut->setFont(QFont("Arial",9));
    m_navDetruitHaut->setReadOnly(true);
    m_navDetruitHaut->setFixedSize(300,270);

    m_navDetruitBas = new QTextEdit;
    m_navDetruitBas->setFont(QFont("Arial",9));
    m_navDetruitBas->setReadOnly(true);
    m_navDetruitBas->setFixedSize(300,270);

    //Appel aux fonctions d'initialisation pour la création et le remplissage des grilles
    initHeaderTab();
    init();

    //Création des layouts et organisation des widgets dans la fenêtre
    QHBoxLayout *layoutH= new QHBoxLayout();
    layoutH->addWidget(m_boutonOK,0);
    layoutH->addWidget(m_boutonRejouer,1);
    layoutH->addWidget(m_boutonQuit,2);
    layoutH->addWidget(m_boutonSolution,3);
    layoutH->addWidget(m_boutonSolutionCache,4);

    QGridLayout *layout= new QGridLayout();
    layout->addWidget(m_grilleHaut,0,0);
    layout->addWidget(m_grilleBas,1,0);
    layout->addWidget(m_lineedit,2,0);
    layout->addLayout(layoutH,3,0);
    layout->addWidget(m_navDetruitHaut,0,1);
    layout->addWidget(m_navDetruitBas,1,1);
    layout->addWidget(m_grilleHautOrdi,0,2);
    layout->addWidget(m_grilleBasOrdi,1,2);

    //Interactions avec l'utilisateur (appui sur un bouton, selections des paramètres ...)
    connect(actionNvlPartie,SIGNAL(triggered(bool)),this,SLOT(rejouer()));
    connect(actionOptions,SIGNAL(triggered(bool)),this,SLOT(options()));
    connect(actionParametres,SIGNAL(triggered(bool)),this,SLOT(parametreUtilisateur()));
    connect(actionQuitter,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(actionAide,SIGNAL(triggered(bool)),fenaide,SLOT(exec()));
    connect(actionAPropos,SIGNAL(triggered(bool)),fenapropos,SLOT(exec()));

    connect(m_boutonOK,SIGNAL(clicked(bool)),this,SLOT(algo()));
    connect(m_boutonQuit,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_boutonRejouer,SIGNAL(clicked(bool)),this,SLOT(rejouer()));
    connect(m_boutonSolution,SIGNAL(clicked(bool)),this,SLOT(grilleSolution()));
    connect(m_boutonSolutionCache,SIGNAL(clicked(bool)),this,SLOT(grilleSolutionCache()));

    connect(m_options.getboutonOK(),SIGNAL(clicked()),this,SLOT(rejouer()));
    connect(&m_paramUtil,SIGNAL(paramUtilisateurOK()),this,SLOT(rejouer()));

    zoneCentrale->setLayout(layout);
    setCentralWidget(zoneCentrale);
}

BatailleNavaleFen::~BatailleNavaleFen()
{
    while(TabchoixUtilisateurIdentique.size()!=0)
    {
        TabchoixUtilisateurIdentique.pop_back();
    }
    ordinateur->videTabChoixOrdiIdentique();

    while(algorithmeIA.tabAlgoIA.size()!=0)
    {
        algorithmeIA.tabAlgoIA.pop_back();
    }

    delete grilleBas;
    delete grilleHaut;
    delete grilleBasOrdi;
    delete grilleHautOrdi;
    delete utilisateur;
    delete ordinateur;
}

//A chaque appui sur le bouton "OK", on lance l'algorithme de l'application
void BatailleNavaleFen::algo()
{
    QTableWidgetItem *itemBas;
    QTableWidgetItem *itemHaut;
    QTableWidgetItem *itemBasOrdi;
    QTableWidgetItem *itemHautOrdi;
    itemBas = new QTableWidgetItem();
    itemHaut = new QTableWidgetItem();
    itemBasOrdi = new QTableWidgetItem();
    itemHautOrdi = new QTableWidgetItem();

    utilisateur->setChoixUtilisateur(m_lineedit->displayText().toStdString());

    //On teste si le choix entré par l'utilisateur est correct
    if(!utilisateur->testchoixUtilisateur())
    {
        QMessageBox::critical(this,"Bataille Navale","Veuillez entrer une coordonnée correcte ");
        m_lineedit->clear();
    }
    else
    {
        //Puis on teste si les coordonnées de l'utilisateur n'ont pas déjà étaient entrées précédemment
        if(utilisateur->testchoixUtilisateurIdentique(TabchoixUtilisateurIdentique))
        {
            QMessageBox::critical(this,"Bataille Navale","Vous avez déjà entré cette coordonnée ");
            m_lineedit->clear();
        }
        else
        {
            //Partie 2 joueurs (Humain vs Ordinateur)
            if(m_options.getSelection_2JvsOrdi())
            {
                algo2JUtilisateur(itemHaut,itemBasOrdi);
                algo2JOrdinateur(itemHautOrdi,itemBas);
            }
            //Partie 1 joueur
            else{
                algo1J(itemHaut);
            }
        }
    }
}

//Permet d'effacer tous les éléments de la partie en cours, puis de créer une nouvelle partie
void BatailleNavaleFen::rejouer()
{
    m_lineedit->clear();
    m_navDetruitHaut->clear();
    m_navDetruitBas->clear();

    m_boutonOK->setEnabled(true);
    while(algorithmeIA.tabAlgoIA.size()!=0)
    {
        algorithmeIA.tabAlgoIA.pop_back();
    }
    while(TabchoixUtilisateurIdentique.size()!=0)
    {
        TabchoixUtilisateurIdentique.pop_back();
    }
    ordinateur->videTabChoixOrdiIdentique();
    init();
}

//Permet de sélectionner le mode de jeu (1 joueur avec grille visible ou cachée et 2 joueurs)
void BatailleNavaleFen::options()
{
    m_options.setWindowModality(Qt::ApplicationModal);
    m_options.show();
}

//Permet de sélectionner le placement automatique ou manuel des navires sur la grille
void BatailleNavaleFen::parametreUtilisateur()
{
    m_paramUtil.setWindowModality(Qt::ApplicationModal);
    m_paramUtil.show();
}

//Affiche la solution (grille de l'adversaire)
void BatailleNavaleFen::grilleSolution()
{
    m_boutonSolution->setEnabled(false);
    m_boutonSolutionCache->setEnabled(true);
    if(m_options.getSelection_1JEC())
    {
        m_grilleBas->show();
    }
    else
        if(m_options.getSelection_2JvsOrdi())
        {
            m_grilleHautOrdi->show();
            m_grilleBasOrdi->show();
        }
}

//Cache la solution (grille de l'adversaire)
void BatailleNavaleFen::grilleSolutionCache()
{
    m_boutonSolution->setEnabled(true);
    m_boutonSolutionCache->setEnabled(false);
    if(m_options.getSelection_1JEC())
    {
        m_grilleBas->hide();
    }
    else
        if(m_options.getSelection_2JvsOrdi())
        {
            m_grilleHautOrdi->hide();
            m_grilleBasOrdi->hide();
        }
}

//  SLOT ré-implantant (closeEvent) lors de la fermeture de l'application (croix rouge)
void BatailleNavaleFen::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this,"Bataille navale",tr("Voulez-vous quitter?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

//Fonction d'initialisation des paramètres, appelée dans le constructeur ou pour une nouvelle partie
void BatailleNavaleFen::init()
{
    QTableWidgetItem *itemBas=nullptr;
    QTableWidgetItem *itemHaut=nullptr;
    QTableWidgetItem *itemBasOrdi=nullptr;
    QTableWidgetItem *itemHautOrdi=nullptr;
    m_grilleHaut->show();
    m_grilleBas->show();
    m_grilleHautOrdi->hide();
    m_grilleBasOrdi->hide();
    m_navDetruitHaut->show();
    m_navDetruitBas->show();
    m_boutonSolution->show();
    m_boutonSolutionCache->show();

    grilleBas = new Grille();
    grilleHaut = new Grille();
    grilleBasOrdi = new Grille();
    grilleHautOrdi = new Grille();

    //Partie 2 joueurs
    if(m_options.getSelection_2JvsOrdi())
    {
        init2JUtilisateur(itemBas,itemHautOrdi);
        init2JOrdinateur(itemBasOrdi,itemHaut);
        m_boutonSolution->setEnabled(true);
        m_boutonSolutionCache->setEnabled(false);
    }
    else{
        //Partie 1 joueur
        init1J(itemBas,itemHaut);
        m_navDetruitBas->hide();
        m_boutonSolution->setEnabled(false);
        if(m_options.getSelection_1JEC())
        {
            m_grilleBas->hide();
            m_boutonSolution->setEnabled(true);
            m_boutonSolutionCache->setEnabled(false);
        }
        else
        {
            m_boutonSolution->hide();
            m_boutonSolutionCache->hide();
        }
    }
}

//Création de l'entête des grilles
void BatailleNavaleFen::initHeaderTab()
{
    int x(0);
    string tw[N]={"A","B","C","D","E","F","G","H","I","J"};
    QTableWidgetItem *twi;
    for (x=0; x<N; x++)
    {
        twi= new QTableWidgetItem();
        m_grilleHaut->setHorizontalHeaderItem(x,twi);
        m_grilleBas->setHorizontalHeaderItem(x,twi);
        m_grilleHautOrdi->setHorizontalHeaderItem(x,twi);
        m_grilleBasOrdi->setHorizontalHeaderItem(x,twi);
        twi->setText(QString::fromStdString(tw[x]));
        twi->setFlags(twi->flags() ^ Qt::ItemIsEditable);
    }
}

//1 joueur: création des grilles avec placement aléatoire des navires sur la grille du bas de l'utilisateur
void BatailleNavaleFen::init1J(QTableWidgetItem *itemBas,QTableWidgetItem *itemHaut)
{
    int i(0), j(0);
    grilleBas->initTabNavires(tabNavires);

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            itemBas = new QTableWidgetItem();
            itemHaut = new QTableWidgetItem();

            m_grilleBas->setItem(i,j,itemBas);
            m_grilleHaut->setItem(i,j,itemHaut);

            itemBas->setText(QString::fromStdString(grilleBas->getGrille(i,j)));
            itemBas->setFlags(itemBas->flags() ^ Qt::ItemIsEditable);
            itemBas->setTextAlignment(5);

            itemHaut->setText(QString::fromStdString(grilleHaut->getGrille(i,j)));
            itemHaut->setFlags(itemHaut->flags() ^ Qt::ItemIsEditable);
            itemHaut->setTextAlignment(5);
         }
    }
    m_navDetruitHaut->insertPlainText("Navires détruits: \n\n" );
    grilleBas->initTabTaille(tabTaille,tabNavires);
}

//2 joueurs: création des grilles avec placement des navires sur la grille du bas de l'utilisateur
void BatailleNavaleFen::init2JUtilisateur(QTableWidgetItem *itemBas,QTableWidgetItem *itemHautOrdi)
{
    int k(0),i(0),j(0);
    srand(time(nullptr));

    //Si l'utilisateur choisit l'option "placement automatique", les navires seront placés aléatoirement
    if(m_paramUtil.getPlacementAuto())
    {
        grilleBas->initTabNavires(tabNavires);
    }
    else
    {
        //Sinon l'utilisateur choisit l'emplacement de chacun des ses navires
        QVector<Navire> tabN;
        tabN=m_paramUtil.getNavires();

        for(k=0;k<NB_NAVIRES;k++)
        {
            tabNavires[k]=tabN[k];
            grilleBas->placeNavire(&tabNavires[k]);
        }
    }

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            itemBas = new QTableWidgetItem();
            itemHautOrdi = new QTableWidgetItem();

            m_grilleBas->setItem(i,j,itemBas);
            m_grilleHautOrdi->setItem(i,j,itemHautOrdi);

            itemBas->setText(QString::fromStdString(grilleBas->getGrille(i,j)));
            itemBas->setFlags(itemBas->flags() ^ Qt::ItemIsEditable);
            itemBas->setTextAlignment(5);

            itemHautOrdi->setText(QString::fromStdString(grilleHautOrdi->getGrille(i,j)));
            itemHautOrdi->setFlags(itemHautOrdi->flags() ^ Qt::ItemIsEditable);
            itemHautOrdi->setTextAlignment(5);
         }
    }
    m_navDetruitHaut->insertPlainText("Navires détruits (Ordinateur): \n\n" );
    m_navDetruitBas->insertPlainText("Navires détruits (Joueur): \n\n" );
    grilleBas->initTabTaille(tabTaille,tabNavires);
}

//2 joueurs: création des grilles avec placement aléatoire des navires sur la grille du bas de l'ordinateur
void BatailleNavaleFen::init2JOrdinateur(QTableWidgetItem *itemBasOrdi,QTableWidgetItem *itemHaut)
{
    int i(0),j(0);
    grilleBasOrdi->initTabNavires(tabNaviresOrdi);

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            itemBasOrdi = new QTableWidgetItem();
            itemHaut = new QTableWidgetItem();

            m_grilleBasOrdi->setItem(i,j,itemBasOrdi);
            m_grilleHaut->setItem(i,j,itemHaut);

            itemBasOrdi->setText(QString::fromStdString(grilleBasOrdi->getGrille(i,j)));
            itemBasOrdi->setFlags(itemBasOrdi->flags() ^ Qt::ItemIsEditable);
            itemBasOrdi->setTextAlignment(5);

            itemHaut->setText(QString::fromStdString(grilleHaut->getGrille(i,j)));
            itemHaut->setFlags(itemHaut->flags() ^ Qt::ItemIsEditable);
            itemHaut->setTextAlignment(5);
         }
    }
    grilleBasOrdi->initTabTaille(tabTailleOrdi,tabNaviresOrdi);
    algorithmeIA.index=0;
    algorithmeIA.nb=0;
    algorithmeIA.flag=false;
}

//1 joueur: algorithme de l'utilisateur
void BatailleNavaleFen::algo1J(QTableWidgetItem *itemHaut)
{
    coordonnees coord;
    int i(0);

    //On stocke les coordonnées entrées par l'utilisateur dans un tableau
    TabchoixUtilisateurIdentique.push_back(m_lineedit->displayText().toStdString());
    //On tranforme les coordonnées du type string en type coordonnées
    coord=utilisateur->choixUtilisateur();
    m_grilleHaut->setItem(coord.y,coord.x,itemHaut);
    itemHaut->setText(QString::fromStdString(grilleBas->getGrille(coord.y,coord.x))); //pour afficher "X"
    itemHaut->setTextAlignment(5);

    //On teste si les coordonnées entrées permettent de "toucher" un navire
    if(utilisateur->testCoordonnees(coord,grilleHaut,grilleBas))
    {
        itemHaut->setBackground(QBrush(Qt::green));
        for(i=0;i<NB_NAVIRES;i++)
        {
            //On teste lequel des navires a été "touché"
            if(tabNavires[i].getPlacementGrille(coord.x,coord.y)=="X")
            {
                tabTaille[i]=tabTaille[i]-1;
                //On teste si le navire "touché" est détruit ou non
                if(tabTaille[i]==0)
                {
                    tabNavires[i].setDestruction(true);
                    QMessageBox::information(this,"Bataille Navale",QString::fromStdString(tabNavires[i].getNom()) + " détruit");
                    m_navDetruitHaut->insertPlainText(QString::fromStdString(tabNavires[i].getNom()) + " (taille=" +
                                                          QString::number(tabNavires[i].getTaille()) + ")\n");
                }
            }
        }
        //Si tous les navires sont détruits, la partie se termine
        if(utilisateur->partieTerminee(tabNavires))
        {
            QMessageBox::information(this,"Bataille Navale","Félicitations !!! Partie terminée");
            m_boutonOK->setEnabled(false);
            m_lineedit->clear();
        }
    }
    else
    {
        itemHaut->setBackground(QBrush(Qt::red));
    }
    m_lineedit->clear();
}

//2 joueurs: algorithme de l'utilisateur
void BatailleNavaleFen::algo2JUtilisateur(QTableWidgetItem *itemHaut,QTableWidgetItem *itemBasOrdi)
{
    coordonnees coord;
    int i(0);

    //On stocke les coordonnées entrées par l'utilisateur dans un tableau
    TabchoixUtilisateurIdentique.push_back(m_lineedit->displayText().toStdString());
    //On tranforme les coordonnées du type string en type coordonnées
    coord=utilisateur->choixUtilisateur();
    m_grilleHaut->setItem(coord.y,coord.x,itemHaut);
    m_grilleBasOrdi->setItem(coord.y,coord.x,itemBasOrdi);
    itemHaut->setText(QString::fromStdString(grilleBasOrdi->getGrille(coord.y,coord.x))); //pour afficher "X"
    itemHaut->setTextAlignment(5);
    itemBasOrdi->setText(QString::fromStdString(grilleBasOrdi->getGrille(coord.y,coord.x))); //pour afficher "X"
    itemBasOrdi->setTextAlignment(5);

    //On teste si les coordonnées entrées permettent de "toucher" un navire de l'ordinateur
    if(utilisateur->testCoordonnees(coord,grilleHaut,grilleBasOrdi))
    {
        itemHaut->setBackground(QBrush(Qt::green));
        itemBasOrdi->setBackground(QBrush(Qt::cyan));
        for(i=0;i<NB_NAVIRES;i++)
        {
            //On teste lequel des navires de l'ordinateur a été "touché"
            if(tabNaviresOrdi[i].getPlacementGrille(coord.x,coord.y)=="X")
            {
                tabTailleOrdi[i]=tabTailleOrdi[i]-1;
                //On teste si le navire "touché" est détruit ou non
                if(tabTailleOrdi[i]==0)
                {
                    tabNaviresOrdi[i].setDestruction(true);
                    QMessageBox::information(this,"Bataille Navale","TOUCHE COULE (Ordinateur) -> " + QString::fromStdString(tabNaviresOrdi[i].getNom()) + " détruit");
                    m_navDetruitHaut->insertPlainText(QString::fromStdString(tabNaviresOrdi[i].getNom()) + " (taille=" +
                                                          QString::number(tabNaviresOrdi[i].getTaille()) + ")\n");
                }
                else
                {
                    QMessageBox::information(this,"Bataille Navale","TOUCHE (Ordinateur) -> " + QString::fromStdString(tabNaviresOrdi[i].getNom()));
                }
            }
        }
        //Si tous les navires de l'ordinateur sont détruits, la partie se termine et un message de victoire apparait
        if(utilisateur->partieTerminee(tabNaviresOrdi))
        {
            QMessageBox::information(this,"Bataille Navale","Félicitation !!! Vous avez gagné la partie");
            m_boutonOK->setEnabled(false);
            m_lineedit->clear();
        }
    }
    else
    {
        itemHaut->setBackground(QBrush(Qt::red));
        itemBasOrdi->setBackground(QBrush(Qt::cyan));
    }
    m_lineedit->clear();
}

//2 joueurs: algorithme de l'ordinateur
void BatailleNavaleFen::algo2JOrdinateur(QTableWidgetItem *itemHautOrdi,QTableWidgetItem *itemBas)
{
    if(!utilisateur->partieTerminee(tabNaviresOrdi))
    {
        string CoordAleaOrdi;
        coordonnees coordOrdi;
        int i(0);

        //Si un navire a été "touché", on pratique l'algorithme de l'intelligence artificielle
        if(algorithmeIA.tabAlgoIA.size()!=0)
        {
            do{
                CoordAleaOrdi=ordinateur->AlgoIAOrdi(algorithmeIA);
            }while(!ordinateur->testchoixOrdinateur(CoordAleaOrdi));
        }
        //Sinon l'ordinateur choisi aléatoirement une coordonnée (qui n'a pas été choisie précédemment)
        else
        {
            CoordAleaOrdi=ordinateur->CoordonneesAleaOrdi();
        }

        //On tranforme les coordonnées du type string en type coordonnées
        ordinateur->setChoixOrdinateur(CoordAleaOrdi);
        coordOrdi=ordinateur->choixOrdinateur();

        m_grilleHautOrdi->setItem(coordOrdi.y,coordOrdi.x,itemHautOrdi);
        m_grilleBas->setItem(coordOrdi.y,coordOrdi.x,itemBas);
        itemHautOrdi->setText(QString::fromStdString(grilleBas->getGrille(coordOrdi.y,coordOrdi.x))); //pour afficher "X"
        itemHautOrdi->setTextAlignment(5);
        itemBas->setText(QString::fromStdString(grilleBas->getGrille(coordOrdi.y,coordOrdi.x))); //pour afficher "X"
        itemBas->setTextAlignment(5);

        //On teste si les coordonnées de l'ordinateur permettent de "toucher" un navire de l'utilisateur
        if(ordinateur->testCoordonneesOrdinateur(coordOrdi,grilleBas))
        {
            //On stocke la coordonnée dans un tableau dynamique, qui sera utilisé pour l'algorithme de l'I.A
            algorithmeIA.tabAlgoIA.push_back(CoordAleaOrdi);
            algorithmeIA.index=0;
            if(algorithmeIA.tabAlgoIA.size()>=2)
            {
                algorithmeIA.nb++;
            }
            algorithmeIA.flag=false;

            ordinateur->placeCoordonneesOrdinateur(coordOrdi,grilleHautOrdi,grilleBas);
            itemHautOrdi->setBackground(QBrush(Qt::green));
            itemBas->setBackground(QBrush(Qt::cyan));
            for(i=0;i<NB_NAVIRES;i++)
            {
                //On teste lequel des navires de l'utilisateur a été "touché"
                if(tabNavires[i].getPlacementGrille(coordOrdi.x,coordOrdi.y)=="X")
                {
                    tabTaille[i]=tabTaille[i]-1;
                    //On teste si le navire "touché" est détruit ou non
                    if(tabTaille[i]==0)
                    {
                        //Si le navire est détruit, on enlève tous les élements du tableau pour que l'algorithme ne s'effectue pas
                        while(algorithmeIA.tabAlgoIA.size()!=0)
                        {
                            algorithmeIA.tabAlgoIA.pop_back();
                        }
                        algorithmeIA.index=0;
                        algorithmeIA.nb=0;

                        tabNavires[i].setDestruction(true);
                        QMessageBox::information(this,"Bataille Navale","TOUCHE COULE (Joueur) -> " + QString::fromStdString(tabNavires[i].getNom()) + " détruit");
                        m_navDetruitBas->insertPlainText(QString::fromStdString(tabNavires[i].getNom()) + " (taille=" +
                                                          QString::number(tabNavires[i].getTaille()) + ")\n");
                    }
                    else
                    {
                        QMessageBox::information(this,"Bataille Navale","TOUCHE (Joueur) -> " + QString::fromStdString(tabNaviresOrdi[i].getNom()));
                    }
                }
            }

            //Si tous les navires de l'utilisateur sont détruits, la partie se termine et un message de défaite apparait
            if(utilisateur->partieTerminee(tabNavires))
            {
                QMessageBox::information(this,"Bataille Navale","Dommage !!! Vous avez perdu la partie");
                m_boutonOK->setEnabled(false);
                m_lineedit->clear();
            }
        }
        else
        {
            itemHautOrdi->setBackground(QBrush(Qt::red));
            itemBas->setBackground(QBrush(Qt::cyan));
        }
    }
}
