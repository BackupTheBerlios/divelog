TEMPLATE = app

CONFIG   += qt thread debug
DEFINES  = QT_FATAL_ASSERT

INCLUDEPATH = /usr/local/include

MOC_DIR     = .moc
OBJECTS_DIR = .objects

LIBS     = -lUDCF -lm

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
           DiveComputerNotFoundException.h\
           DiverVO.h\
           DiverSO.h\
           DiveVO.h\
           DiveSO.h\
           FillingStationVO.h\
           DiveTypeVO.h\
           DiveComputerVO.h\
           DiverNotFoundException.h\
           DiveNotFoundException.h\
           DiveProfileVO.h\
           DiveListVO.h\
           DiveListViewItem.h

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
           DiveComputerNotFoundException.cpp\
           DiverVO.cpp\
           DiverSO.cpp\
           DiveVO.cpp\
           DiveSO.cpp\
           FillingStationVO.cpp\
           DiveTypeVO.cpp\
           DiveComputerVO.cpp\
           DiverNotFoundException.cpp\
           DiveNotFoundException.cpp\
           DiveProfileVO.cpp\
           DiveListVO.cpp\
           DiveListViewItem.cpp

INTERFACES = MainWidgetBaseFrm.ui\
             NewDiverBaseFrm.ui\
             InfoAreaBaseFrm.ui\
             NewDiveComputerBaseFrm.ui\
             NewDiveTypeBaseFrm.ui\
             NewFillingStationBaseFrm.ui\
             AboutLicenseBaseFrm.ui


TARGET   = divelog
