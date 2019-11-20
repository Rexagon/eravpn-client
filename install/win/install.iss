#define MyAppName "EraVPN Client"
#define MyAppVersion "1.0"
#define MyAppPublisher "EraVPN"
#define MyAppURL "https://eravpn.com/"
#define MyAppExeName "app.exe"

[Setup]
AppId={{DECDEDFE-5C4B-4831-AAF8-AF600C46CE67}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
ArchitecturesInstallIn64BitMode=x64
AllowNoIcons=yes
LicenseFile=..\..\LICENSE

OutputDir=.\
OutputBaseFilename=eravpn_setup
SetupIconFile=..\..\res\images\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "ru"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Types]
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "main"; Description: "EraVPN"; Types: custom; Flags: fixed
Name: "driver"; Description: "TAP-Windows Driver"; Types: custom;
Name: "cpp"; Description: "Microsoft Visual C++ Redistributable"; Types: custom;

[Files]
Source: "..\..\build\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: ".\*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\tap-windows.exe"; DestDir: "{app}\redist"; Check: IsComponentSelected('driver'); Flags: ignoreversion
Source: ".\VC_redist.x64.exe"; DestDir: "{app}\redist"; Check: IsComponentSelected('cpp'); Flags: ignoreversion

[Registry]
Root: HKCU; Subkey: "Software\{#MyAppPublisher}\{#MyAppName}"; ValueType: string; ValueName: "language"; ValueData: "{code:GetAppLanguage}"
Root: HKCU; Subkey: "Software\{#MyAppPublisher}\{#MyAppName}"; Flags: uninsdeletekey

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\redist\tap-windows.exe"; Check: IsComponentSelected('driver'); Flags: runascurrentuser
Filename: "{app}\redist\VC_redist.x64.exe"; Check: IsComponentSelected('cpp'); Flags: runascurrentuser
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall runascurrentuser skipifsilent

[UninstallDelete]
Type: filesandordirs; Name: "{localappdata}\{#MyAppPublisher}\{#MyAppName}"

[Code]
function GetAppLanguage(Param: string): string;
begin
  Result := ActiveLanguage;
end;