#-------------------------------------------------
#
# Project created by QtCreator 2012-11-15T14:36:04
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Softtech
TEMPLATE = app


SOURCES += main.cpp\
        IHM/mainwindow.cpp \
    Core/Settings.cpp \
    Core/DatabaseInfos.cpp \
    Core/Database.cpp \
    Core/Export.cpp \
    IHM/ExportDialog.cpp \
	IHM/ImportDialog.cpp \
    IHM/SettingsDialog.cpp \
    Core/Import.cpp \
    IHM/AddDialog.cpp \
    IHM/LoanDialog.cpp

HEADERS  += IHM/mainwindow.h \
    Core/Settings.h \
    Core/DatabaseInfos.h \
    Core/Database.h \
    Core/Export.h \
    IHM/ExportDialog.h \
	IHM/ImportDialog.h \
    IHM/SettingsDialog.h \
    Core/Import.h \
    IHM/AddDialog.h \
    IHM/LoanDialog.h

FORMS    += IHM/mainwindow.ui \
    IHM/ExportDialog.ui \
	IHM/ImportDialog.ui \
    IHM/SettingsDialog.ui \
    IHM/AddDialog.ui \
    IHM/LoanDialog.ui

RESOURCES += \
    Icons.qrc
