TEMPLATE = app

CONFIG   = qt warn_on debug
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
           newdiverfrm.h

SOURCES  = main.cpp\
           mainwidget.cpp\
           profilefield.cpp\
           myscrollbar.cpp\
           divelogdao.cpp\
           newdiverfrm.cpp

INTERFACES = newdiverbasefrm.ui

TARGET   = divelog