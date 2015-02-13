mkdir dist
mkdir dist\windows
mkdir dist\windows\doc

echo Generate docs
cd apidoc
call npm install .
echo Exit Code = %ERRORLEVEL%
call node ti_win_yaml.js
echo Exit Code = %ERRORLEVEL%
cd ..
robocopy apidoc\Titanium dist\windows\doc\Titanium /e

echo Copy over cli, templates, package.json
robocopy cli dist\windows\cli /e
robocopy templates dist\windows\templates /e
robocopy . dist\windows package.json

echo Native libraries
mkdir dist\windows\lib

echo TODO Limit to only copy dll/lib/winmd?
echo Titanium Windows
robocopy build\x86\Release dist\windows\lib\TitaniumWindows\x86 TitaniumWindows.*
robocopy build\ARM\Release dist\windows\lib\TitaniumWindows\ARM TitaniumWindows.*
mkdir dist\windows\lib\TitaniumWindows\include

echo HAL
robocopy build\x86\Global\TitaniumKit\HAL\Release dist\windows\lib\HAL\x86 HAL.*
robocopy build\ARM\Global\TitaniumKit\HAL\Release dist\windows\lib\HAL\ARM HAL.*
robocopy build\x86\Global\TitaniumKit\HAL dist\windows\lib\HAL\include hal_export.h

echo Titanium Kit
robocopy build\x86\Global\TitaniumKit\Release dist\windows\lib\TitaniumKit\x86 TitaniumKit.*
robocopy build\ARM\Global\TitaniumKit\Release dist\windows\lib\TitaniumKit\ARM TitaniumKit.*
robocopy build\x86\Global\TitaniumKit dist\windows\lib\TitaniumKit\include titaniumkit_export.h

echo Titanium Windows Accelerometer
robocopy build\x86\Accelerometer\Release dist\windows\lib\TitaniumWindows_Accelerometer\x86 TitaniumWindows_Accelerometer.*
robocopy build\ARM\Accelerometer\Release dist\windows\lib\TitaniumWindows_Accelerometer\ARM TitaniumWindows_Accelerometer.*
robocopy build\x86\Accelerometer dist\windows\lib\TitaniumWindows_Accelerometer\include titaniumwindows_accelerometer_export.h

echo Titanium Windows API
robocopy build\x86\API\Release dist\windows\lib\TitaniumWindows_API\x86 TitaniumWindows_API.*
robocopy build\ARM\API\Release dist\windows\lib\TitaniumWindows_API\ARM TitaniumWindows_API.*
robocopy build\x86\API dist\windows\lib\TitaniumWindows_API\include titaniumwindows_api_export.h

echo Titanium Windows Filesystem
robocopy build\x86\Filesystem\Release dist\windows\lib\TitaniumWindows_Filesystem\x86 TitaniumWindows_Filesystem.*
robocopy build\ARM\Filesystem\Release dist\windows\lib\TitaniumWindows_Filesystem\ARM TitaniumWindows_Filesystem.*
robocopy build\x86\Filesystem dist\windows\lib\TitaniumWindows_Filesystem\include titaniumwindows_filesystem_export.h

echo Titanium Windows Network
robocopy build\x86\Network\Release dist\windows\lib\TitaniumWindows_Network\x86 TitaniumWindows_Network.*
robocopy build\ARM\Network\Release dist\windows\lib\TitaniumWindows_Network\ARM TitaniumWindows_Network.*
robocopy build\x86\Network dist\windows\lib\TitaniumWindows_Network\include titaniumwindows_network_export.h

echo Titanium Windows Gesture
robocopy build\x86\Gesture\Release dist\windows\lib\TitaniumWindows_Gesture\x86 TitaniumWindows_Gesture.*
robocopy build\ARM\Gesture\Release dist\windows\lib\TitaniumWindows_Gesture\ARM TitaniumWindows_Gesture.*
robocopy build\x86\Gesture dist\windows\lib\TitaniumWindows_Gesture\include titaniumwindows_gesture_export.h

echo Titanium Windows Global
robocopy build\x86\Global\Release dist\windows\lib\TitaniumWindows_Global\x86 TitaniumWindows_Global.*
robocopy build\ARM\Global\Release dist\windows\lib\TitaniumWindows_Global\ARM TitaniumWindows_Global.*
robocopy build\x86\Global dist\windows\lib\TitaniumWindows_Global\include titaniumwindows_global_export.h

echo LayoutEngine
robocopy build\x86\LayoutEngine\Release dist\windows\lib\LayoutEngine\x86 LayoutEngine.*
robocopy build\ARM\LayoutEngine\Release dist\windows\lib\LayoutEngine\ARM LayoutEngine.*
robocopy build\x86\LayoutEngine dist\windows\lib\LayoutEngine\include layoutengine_export.h

echo Titanium Windows Platform
robocopy build\x86\Platform\Release dist\windows\lib\TitaniumWindows_Platform\x86 TitaniumWindows_Platform.*
robocopy build\ARM\Platform\Release dist\windows\lib\TitaniumWindows_Platform\ARM TitaniumWindows_Platform.*
robocopy build\x86\Platform dist\windows\lib\TitaniumWindows_Platform\include titaniumwindows_platform_export.h

echo Titanium Windows Ti
robocopy build\x86\Ti\Release dist\windows\lib\TitaniumWindows_Ti\x86 TitaniumWindows_Ti.*
robocopy build\ARM\Ti\Release dist\windows\lib\TitaniumWindows_Ti\ARM TitaniumWindows_Ti.*
robocopy build\x86\Ti dist\windows\lib\TitaniumWindows_Ti\include titaniumwindows_ti_export.h

echo Titanium Windows UI
robocopy build\x86\UI\Release dist\windows\lib\TitaniumWindows_UI\x86 TitaniumWindows_UI.*
robocopy build\ARM\UI\Release dist\windows\lib\TitaniumWindows_UI\ARM TitaniumWindows_UI.*
robocopy build\x86\UI dist\windows\lib\TitaniumWindows_UI\include titaniumwindows_ui_export.h

echo Titanium Windows Utility
robocopy build\x86\Global\Utility\Release dist\windows\lib\TitaniumWindows_Utility\x86 TitaniumWindows_Utility.*
robocopy build\ARM\Global\Utility\Release dist\windows\lib\TitaniumWindows_Utility\ARM TitaniumWindows_Utility.*
robocopy build\x86\Global\Utility dist\windows\lib\TitaniumWindows_Utility\include titaniumwindows_utility_export.h


IF %ERRORLEVEL% LEQ 4 exit /B 0
