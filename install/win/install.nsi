;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"
  !include x64.nsh

;--------------------------------
;General

  ;Name and file
  Name "EraVPN Client"
  OutFile "eravpn_setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES64\EraVPN Client"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\EraVPN Client" "Install_Dir"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\..\LICENSE"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "Russian"

;--------------------------------
;Installer Sections

Section ""
  SetOutPath "$INSTDIR"

  File /r ..\..\build\*

  ;Store installation folder
  WriteRegStr HKCU "Software\EraVPN\EraVPN Client" "Install_Dir" $INSTDIR

  CreateShortcut "$DESKTOP\EraVPN.lnk" "$INSTDIR\app.exe"

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  RMDir /r "$LocalAppdata\EraVPN\EraVPN Client"

  RMDir /r "$INSTDIR"

  Delete "$DESKTOP\EraVPN.lnk"

  DeleteRegKey HKCU "Software\EraVPN\EraVPN Client"

SectionEnd
