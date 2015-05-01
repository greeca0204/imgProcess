; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImgDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Img.h"
LastPage=0

ClassCount=6
Class1=CImgApp
Class2=CImgDoc
Class3=CImgView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_IMGTYPE
Resource2=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_ABOUTBOX

[CLS:CImgApp]
Type=0
HeaderFile=Img.h
ImplementationFile=Img.cpp
Filter=N

[CLS:CImgDoc]
Type=0
HeaderFile=ImgDoc.h
ImplementationFile=ImgDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CImgView]
Type=0
HeaderFile=ImgView.h
ImplementationFile=ImgView.cpp
Filter=C
LastObject=ID_HIT


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=Img.cpp
ImplementationFile=Img.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_IMGTYPE]
Type=1
Class=CImgView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_READBMP
Command16=ID_FRAY
Command17=ID_HIST
Command18=ID_D
Command19=ID_P
Command20=ID_OTSU
Command21=ID_Lap
Command22=ID_EXP
Command23=ID_ERODE
Command24=ID_DILATE
Command25=ID_FILL
Command26=ID_OPEN
Command27=ID_GRAYERODE
Command28=ID_HIT
Command29=ID_VIEW_TOOLBAR
Command30=ID_VIEW_STATUS_BAR
Command31=ID_WINDOW_NEW
Command32=ID_WINDOW_CASCADE
Command33=ID_WINDOW_TILE_HORZ
Command34=ID_WINDOW_ARRANGE
Command35=ID_APP_ABOUT
CommandCount=35

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

