TEMPLATE = app

CONFIG   = qt debug
DEFINES  = QT_FATAL_ASSERT

INCLUDEPATH = /usr/local/include /usr/include/mysql

MOC_DIR     = .moc
OBJECTS_DIR = .objects

LIBS     = -lUDCF -lsqlplus -lmysqlclient 

HEADERS  = mainwidget.h\
           profilefield.h\
           myscrollbar.h\
           divelogdao.h\
           UDCF.h\
           newdiverfrm.h\
           infoareafrm.h\
           newfillingstationfrm.h\
           newdivetypefrm.h\
           newdivecomputerfrm.h

SOURCES  = main.cpp\
           mainwidget.cpp\
           profilefield.cpp\
           myscrollbar.cpp\
           divelogdao.cpp\
           newdiverfrm.cpp\
           infoareafrm.cpp\
           newfillingstationfrm.cpp\
           newdivetypefrm.cpp\
           newdivecomputerfrm.cpp
           

INTERFACES = newdiverbasefrm.ui\
             infoareabasefrm.ui\
             newdivecomputerbasefrm.ui\
             newdivetypebasefrm.ui\
             newfillingstationbasefrm.ui


TARGET   = divelog