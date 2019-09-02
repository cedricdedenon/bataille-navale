QT += widgets

SOURCES += \
    bataillenavalefen.cpp \
    grille.cpp \
    main.cpp \
    navire.cpp \
    ordinateur.cpp \
    utilisateur.cpp \
    optionsfen.cpp \
    paramutil.cpp

HEADERS += \
    bataillenavalefen.hpp \
    constantes.hpp \
    grille.hpp \
    navire.hpp \
    utilisateur.hpp \
    optionsfen.hpp \
    ordinateur.hpp \
    paramutil.hpp

DISTFILES += \
    ressource.rc

RC_FILE = ressource.rc
