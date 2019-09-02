#include "paramutil.hpp"

ParamUtil::ParamUtil(): QWidget()
{
    //Création et définition des widgets utiles à l'application
    QGroupBox *groupbox = new QGroupBox("Placement des navires sur la grille", this);
    QLabel *labelintro = new QLabel(" ");

    m_placementAuto = new QRadioButton("Placement automatique");
    m_placementManuel = new QRadioButton("Placement manuel");
    m_placementAuto->setFont(QFont("Arial",9,60,false));
    m_placementManuel->setFont(QFont("Arial",9,60,false));
    m_placementAuto->setChecked(true);

    QLabel *labelNom_n1 = new QLabel("PORTE_AVIONS (taille 5)");
    QLabel *labelNom_n2 = new QLabel("CROISEUR (taille 4)");
    QLabel *labelNom_n3 = new QLabel("CONTRE_TORPILLEURS (taille 3)");
    QLabel *labelNom_n4 = new QLabel("SOUS_MARIN (taille 3)");
    QLabel *labelNom_n5 = new QLabel("TORPILLEUR (taille 2)");

    QStringList listcoordXY;
    listcoordXY << "A1" << "A2" << "A3" << "A4" << "A5" << "A6" << "A7" << "A8"<< "A9" << "A10"
                << "B1" << "B2" << "B3" << "B4" << "B5" << "B6" << "B7" << "B8"<< "B9" << "B10"
                << "C1" << "C2" << "C3" << "C4" << "C5" << "C6" << "C7" << "C8"<< "C9" << "C10"
                << "D1" << "D2" << "D3" << "D4" << "D5" << "D6" << "D7" << "D8"<< "D9" << "D10"
                << "E1" << "E2" << "E3" << "E4" << "E5" << "E6" << "E7" << "E8"<< "E9" << "E10"
                << "F1" << "F2" << "F3" << "F4" << "F5" << "F6" << "F7" << "F8"<< "F9" << "F10"
                << "G1" << "G2" << "G3" << "G4" << "G5" << "G6" << "G7" << "G8"<< "G9" << "G10"
                << "H1" << "H2" << "H3" << "H4" << "H5" << "H6" << "H7" << "H8"<< "H9" << "H10"
                << "I1" << "I2" << "I3" << "I4" << "I5" << "I6" << "I7" << "I8"<< "I9" << "I10"
                << "J1" << "J2" << "J3" << "J4" << "J5" << "J6" << "J7" << "J8"<< "J9" << "J10";

    QStringList listorientation;
    listorientation << "haut" << "bas" << "gauche" << "droite";

    int i(0);
    for(i=0;i<NB_NAVIRES;i++)
    {
        m_coordXY.push_back(new QComboBox(this));
        m_coordXY[i]->addItems(listcoordXY);
        m_coordXY[i]->setEnabled(false);
        m_orientation.push_back(new QComboBox(this));
        m_orientation[i]->addItems(listorientation);
        m_orientation[i]->setEnabled(false);
    }

    m_boutonOK = new QPushButton("OK",this);
    m_placementManuelOK = false;

    //Création du layout et organisation des widgets dans la fenêtre
    QGridLayout *navirelayout = new QGridLayout;
    navirelayout->addWidget(labelNom_n1,0,0);
    navirelayout->addWidget(m_coordXY[0],0,1);
    navirelayout->addWidget(m_orientation[0],0,2);
    navirelayout->addWidget(labelNom_n2,1,0);
    navirelayout->addWidget(m_coordXY[1],1,1);
    navirelayout->addWidget(m_orientation[1],1,2);
    navirelayout->addWidget(labelNom_n3,2,0);
    navirelayout->addWidget(m_coordXY[2],2,1);
    navirelayout->addWidget(m_orientation[2],2,2);
    navirelayout->addWidget(labelNom_n4,3,0);
    navirelayout->addWidget(m_coordXY[3],3,1);
    navirelayout->addWidget(m_orientation[3],3,2);
    navirelayout->addWidget(labelNom_n5,4,0);
    navirelayout->addWidget(m_coordXY[4],4,1);
    navirelayout->addWidget(m_orientation[4],4,2);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_placementAuto);
    layout->addWidget(m_placementManuel);
    layout->addWidget(labelintro);
    layout->addLayout(navirelayout);
    layout->addWidget(m_boutonOK);

    this->setFixedSize(310,270);
    groupbox->setLayout(layout);
    this->hide();

    //Interactions avec l'utilisateur (appui sur un bouton)
    connect(m_placementAuto,SIGNAL(toggled(bool)),this,SLOT(parametresNonVisible()));
    connect(m_placementManuel,SIGNAL(toggled(bool)),this,SLOT(parametresVisible()));
    connect(m_boutonOK,SIGNAL(clicked()),this,SLOT(selectionCoordonnees()));
}

//Si l'option "placement automatique" est sélectionné, l'utilisateur ne peut pas modifier les paramètres
void ParamUtil::parametresNonVisible()
{
    int i(0);
    for(i=0;i<NB_NAVIRES;i++)
    {
        m_coordXY[i]->setEnabled(false);
        m_orientation[i]->setEnabled(false);
    }
}

//Si l'option "placement manuel" est sélectionné, l'utilisateur peut modifier les paramètres pour placer les navires
void ParamUtil::parametresVisible()
{
    int i(0);
    for(i=0;i<NB_NAVIRES;i++)
    {
        m_coordXY[i]->setEnabled(true);
        m_orientation[i]->setEnabled(true);
    }
}

//Losque l'utilisateur appuie sur le bouton "OK", on teste si les coordonnées sont correctes ou non (pour le placement manuel)
void ParamUtil::selectionCoordonnees()
{
    if(m_placementManuel->isChecked())
    {
        QVector<string> coord;
        QVector<coordonnees> c_n;
        QVector<orientation> orient;
        Grille *grilleBas = new Grille();
        Utilisateur *utilisateur = new Utilisateur();
        int navire_cpt=0;;

        while(m_navires.size()!=0)
        {
            m_navires.pop_back();
        }

        int i(0);
        for(i=0;i<NB_NAVIRES;i++)
        {
            //On crée un tableau dynamique de navire grâce aux informations données par l'utilisateur
            coord.push_back(m_coordXY[i]->currentText().toStdString());

            utilisateur->setChoixUtilisateur(coord[i]);
            c_n.push_back(utilisateur->choixUtilisateur());

            orient.push_back(grilleBas->choixOrientation(m_orientation[i]->currentIndex()));
            m_navires.push_back(Navire(grilleBas->nomNavire(i),grilleBas->tailleNavire(i),orient[i],c_n[i]));

            //On teste si les coordonnées sont exactes (si elles sont incluses dans la grille et si un navire n'est pas déjà présent)
            if((grilleBas->testcoordonneesNavire(&m_navires[i]) && grilleBas->testNaviresurGrille(&m_navires[i])))
            {
                navire_cpt++;
                grilleBas->placeNavire(&m_navires[i]);
            }
        }

        //Si toutes les coordonnées sont correctes, l'utilisateur peut continuer à jouer
        if(navire_cpt==NB_NAVIRES)
        {
            navire_cpt=0;
            QMessageBox::information(this,"Paramètres (auto/manuel)","Coordonnées correctes");
            m_placementManuelOK = true;
            emit paramUtilisateurOK();
            this->close();
        }
        //Sinon il devra rentrer de nouveau des coordonnées correctes (ou passer en placement automatique)
        else
        {
            QMessageBox::critical(this,"Paramètres (auto/manuel)","Erreur de coordonnées. Veuillez entrer des coordonnées correctes");
            m_placementManuelOK = false;
        }
        delete grilleBas;
        delete utilisateur;
    }
    else
    {
        emit paramUtilisateurOK();
        this->close();
    }
}

//Accesseurs permettant de savoir lequel des choix a été sélectionné
bool ParamUtil::getPlacementAuto()
{
    return m_placementAuto->isChecked();
}

bool ParamUtil::getPlacementManuel()
{
    return m_placementManuel->isChecked();
}

//Accesseur permettant d'obtenir le tableau de navires que l'utilisateur a placé sur la grille
QVector<Navire> ParamUtil::getNavires()
{
    return m_navires;
}

//Accesseur sur l'attribut m_boutonOK
QPushButton* ParamUtil::getboutonOK()
{
    return m_boutonOK;
}

//  SLOT ré-implantant (closeEvent) lors de la fermeture de la fenêtre (croix rouge)
void ParamUtil::closeEvent(QCloseEvent *event)
{
   event->accept();

   //Si les coordonnées du placement manuel est incorrect et qu'il quitte la fenêtre, on remet le placement automatique par défaut
   if(m_placementManuel->isChecked() && m_placementManuelOK == false){
       m_placementManuel->setChecked(false);
       m_placementAuto->setChecked(true);
   }
}
