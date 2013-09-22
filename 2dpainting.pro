QT          += opengl

HEADERS     = \
              helper.h \
              widget.h \
              window.h \
    fourier.h \
    microphone.h \
    notesgrid.h
SOURCES     = \
              helper.cpp \
              main.cpp \
              widget.cpp \
              window.cpp \
    fourier.cpp \
    microphone.cpp \
    notesgrid.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS 2dpainting.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/2dpainting
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
simulator: warning(This example might not fully work on Simulator platform)

unix|win32: LIBS += -lfftw3

unix|win32: LIBS += -lpulse-simple

unix|win32: LIBS += -lpulse
