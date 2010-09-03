TEMPLATE = app
TARGET = ndk_costume_contest_main
QT += network sql
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS = DialogAccess.h   \
          MasterMain.h     \
	  MasterStatus.h   \
	  DialogNewEntry.h \
	  DialogModEntry.h \
	  DialogDeleteEntry.h \
	  DBUtility.h      \
	  DescriptionUtil.h \
	  DialogAddJudge.h \
	  DialogDeleteJudge.h \
	  DialogGuestJudgeForm.h
SOURCES = main.cpp           \
          DialogAccess.cpp   \
	  MasterMain.cpp     \
	  MasterStatus.cpp   \
	  DialogNewEntry.cpp \
	  DialogModEntry.cpp \
	  DialogDeleteEntry.cpp \
	  DescriptionUtil.cpp \
	  DialogAddJudge.cpp \
	  DialogDeleteJudge.cpp \
	  DialogGuestJudgeForm.cpp

RESOURCES = ndk_costume_contest.qrc
