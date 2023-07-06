# http://doc.qt.io/qt-5/qmake-variable-reference.html
CONFIG += console
QT += core widgets gui
DEFINES += QT_WIDGETS_LIB
#LIBS += 
INCLUDEPATH += .

HEADERS += paint.h \
           bboxdecorator.h \
           canvas.h  \
           circle.h \
           freehand.h \
           graphobj.h \
           line.h \
           polygon.h \
           rectangle.h \
           scene.h
SOURCES += paint.cpp \
           bboxdecorator.cpp \
           canvas.cpp \
           circle.cpp \
           freehand.cpp \
           graphobj.cpp \
           line.cpp \
           main.cpp \
           polygon.cpp \
           rectangle.cpp \
           scene.cpp

FORMS +=
