TEMPLATE = app

CONFIG   = qt debug
DEFINES  = QT_FATAL_ASSERT

INCLUDEPATH = /usr/local/include /usr/include/mysql

MOC_DIR     = .moc
OBJECTS_DIR = .objects

LIBS     = -lUDCF -lsqlplus -lmysqlclient 

HEADERS  = MainWidget.h\
           ProfileField.h\
           MyScrollBar.h\
           DivelogDAO.h\
           UDCF.h\
           NewDiverFrm.h\
           InfoAreaFrm.h\
           NewFillingStationFrm.h\
           NewDiveTypeFrm.h\
           NewDiveComputerFrm.h\
           DivelogDAOException.h\
           DiveComputerNotFoundException.h

SOURCES  = main.cpp\
           MainWidget.cpp\
           ProfileField.cpp\
           MyScrollBar.cpp\
           DivelogDAO.cpp\
           NewDiverFrm.cpp\
           InfoAreaFrm.cpp\
           NewFillingStationFrm.cpp\
           NewDiveTypeFrm.cpp\
           NewDiveComputerFrm.cpp\
           DivelogDAOException.cpp\
           DiveComputerNotFoundException.cpp
           

INTERFACES = NewDiverBaseFrm.ui\
             InfoAreaBaseFrm.ui\
             NewDiveComputerBaseFrm.ui\
             NewDiveTypeBaseFrm.ui\
             NewFillingStationBaseFrm.ui


TARGET   = divelog