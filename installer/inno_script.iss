; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{BEAE8D96-9FCB-4EEF-A518-EFA3B6136CAD}
AppName=Arduino EEG
AppVersion=0.0.1
;AppVerName=Arduino EEG 0.0.1
AppPublisher=Ragged Genes
AppPublisherURL=https://github.com/raggedgenes/ARDUINO_EEG
AppSupportURL=https://github.com/raggedgenes/ARDUINO_EEG
AppUpdatesURL=https://github.com/raggedgenes/ARDUINO_EEG
DefaultDirName={pf}\Arduino EEG
DefaultGroupName=Arduino EEG
OutputDir=D:\RandD\ARD_EEG\installer
OutputBaseFilename=Arduino_EEG_setup
;SetupIconFile=D:\RandD\NODEJS\electron-boilerplate\app\img\logo.png
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\RandD\ARD_EEG\release\ARD_EEG.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\CPPLibraries\fftw-3.3.4-dll32\libfftw3-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\CPPLibraries\fftw-3.3.4-dll32\libfftw3f-3.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Arduino EEG"; Filename: "{app}\ARD_EEG.exe"
Name: "{commondesktop}\Arduino EEG"; Filename: "{app}\ARD_EEG.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\ARD_EEG.exe"; Description: "{cm:LaunchProgram,Arduino EEG}"; Flags: nowait postinstall skipifsilent
