TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    documentParser.cpp \
    indexer.cpp \
    wordobject.cpp \
    stemmingalgorithm.cpp \
    queryprocessor.cpp \
    userinterface.cpp \
    indexhandler.cpp

HEADERS += \
    HashNode.h \
    documentParser.h \
    HashTable.h \
    avltree.h \
    avlnode.h \
    indexer.h \
    wordobject.h \
    common_lang_constants.h \
    debug_logic.h \
    english_stem.h \
    safe_math.h \
    stemming.h \
    stemmingalgorithm.h \
    string_util.h \
    utilities.h \
    queryprocessor.h \
    userinterface.h \
    indexhandler.h
