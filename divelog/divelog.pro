TEMPLATE = app

CONFIG   = qt warn_on debug
DEFINES  = QT_FATAL_ASSERT

INCLUDEPATH = /usr/local/include /usr/include/mysql

MOC_DIR     = .moc
OBJECTS_DIR = .objects

LIBS     = -lUDCF -lsqlplus 
HEADERS  = mainwidget.h  profilefield.h  myscrollbar.h divelogdao.h UDCF.h
SOURCES  = main.cpp  mainwidget.cpp  profilefield.cpp  myscrollbar.cpp divelogdao.cpp

TARGET   = divelog