#ifndef OPTIONSFEN_HPP
#define OPTIONSFEN_HPP

#include <QApplication>
#include <QtWidgets>

class OptionsFen: public QWidget
{
Q_OBJECT

public:
    OptionsFen();

public slots:
    void ouvrirDialogue();

private:
    QRadioButton *m_1JEntrainementVisible;
    QRadioButton *m_1JEntrainementCache;
    QRadioButton *m_2JvsOrdi;
    QPushButton *m_boutonOK;

public:
    bool getSelection_1JEV();
    bool getSelection_1JEC();
    bool getSelection_2JvsOrdi();
    QPushButton* getboutonOK();
};

#endif // OPTIONSFEN_HPP
