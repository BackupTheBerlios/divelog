TEMPLATE = app

CONFIG   = qt warn_on debug
DEFINES  = QT_FATAL_ASSERT

INCLUDEPATH = /usr/local/include

LIBS     = -lUDCF
HEADERS  = mainwidget.h  profilefield.h  myscrollbar.h UDCF.h
SOURCES  = main.cpp  mainwidget.cpp  profilefield.cpp  myscrollbar.cpp

TARGET   = divelog