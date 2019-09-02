#include "optionsfen.hpp"

OptionsFen::OptionsFen(): QWidget()
{
    //Création et définition des widgets utiles à l'application
    QGroupBox *groupbox = new QGroupBox("Mode de jeux: ", this);
    m_1JEntrainementVisible = new QRadioButton("1 joueur avec grille dévoilée");
    m_1JEntrainementCache = new QRadioButton("1 joueur avec grille cachée");
    m_2JvsOrdi = new QRadioButton("2 joueurs (vs Ordinateur)");

    //Par défaut le mode 2 joueurs est sélectionné
    m_2JvsOrdi->setChecked(true);

    m_boutonOK = new QPushButton("OK",this);

    //Création du layout et organisation des widgets dans la fenêtre
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_1JEntrainementVisible);
    layout->addWidget(m_1JEntrainementCache);
    layout->addWidget(m_2JvsOrdi);
    layout->addWidget(m_boutonOK);

    this->setFixedSize(200,150);
    groupbox->setLayout(layout);

    //Interactions avec l'utilisateur (appui sur un bouton)
    connect(m_boutonOK,SIGNAL(clicked()),this,SLOT(ouvrirDialogue()));
}

//La fenêtre se ferme lorsque l'utilisateur appuie sur le bouton "OK"
void OptionsFen::ouvrirDialogue()
{
    this->close();
}

//Accesseurs permettant de savoir lequel des choix a été sélectionné
bool OptionsFen::getSelection_1JEV()
{
    return m_1JEntrainementVisible->isChecked();
}

bool OptionsFen::getSelection_1JEC()
{
    return m_1JEntrainementCache->isChecked();
}

bool OptionsFen::getSelection_2JvsOrdi()
{
    return m_2JvsOrdi->isChecked();
}

QPushButton* OptionsFen::getboutonOK()
{
    return m_boutonOK;
}

