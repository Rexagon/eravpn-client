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
  !define MUI_LANGDLL_ALLLANGUAGES

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\..\LICENSE"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "Russian"

;--------------------------------
;Installer Sections

Section "EraVPN Client" SEC0000
  SetOutPath "$INSTDIR"

  File /r ..\..\build\*
  File "*.dll"

  ;Store installation folder
  WriteRegStr HKCU "Software\EraVPN\EraVPN Client" "Install_Dir" $INSTDIR

  CreateShortcut "$DESKTOP\EraVPN.lnk" "$INSTDIR\app.exe"

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

Section "TAP-Windows Driver"
  SetOutPath $INSTDIR\redist

  File "tap-windows.exe"
  ExecWait "$INSTDIR\redist\tap-windows.exe"
SectionEnd

Section "Microsoft Visual C++ Redistributable"
  SetOutPath $INSTDIR\redist

  File "VC_redist.x64.exe"
  ExecWait "$INSTDIR\redist\VC_redist.x64.exe"
SectionEnd

;--------------------------------
;Reserve Files

  !insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Installer Functions

Function .onInit
  SectionSetFlags ${SEC0000} 17
  !insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  RMDir /r "$LocalAppdata\EraVPN\EraVPN Client"

  RMDir /r "$INSTDIR"

  Delete "$DESKTOP\EraVPN.lnk"

  DeleteRegKey HKCU "Software\EraVPN\EraVPN Client"

SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE

FunctionEnd
