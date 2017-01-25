mkdir dist
mkdir dist\\windows

cd Tools\\Scripts
call npm install .
echo Installing JSC built for Windows 10
call node setup.js -s 10.0 --no-color --no-progress-bars

cd build
call npm install .
echo Building for Windows 10
call node build.js -s 10.0 -m 14.0 -o WindowsStore-x86 -o WindowsStore-ARM --sha %1
SET BUILDLEVEL=%ERRORLEVEL%
IF %BUILDLEVEL% NEQ 0 (
	rmdir node_modules /Q /S
	exit /B %BUILDLEVEL%
)

echo Running Tests on Windows 10 Phone Emulator
call node test.js -s 10.0.10586 -p Windows10.Phone -b %2
SET TESTLEVEL=%ERRORLEVEL%

echo Copying JUnit report
cd ..\\..\\..\\dist
copy junit_report.xml junit_report_10_phone.xml
del junit_report.xml
cd ..\\Tools\\Scripts\\build

IF %TESTLEVEL% NEQ 0 (
	rmdir node_modules /Q /S
	exit /B %TESTLEVEL%
)

echo Running Tests on Windows 10 Desktop
call node test.js -s 10.0 -T ws-local -p Windows10.Store -b %2
SET TESTLEVEL=%ERRORLEVEL%

rmdir node_modules /Q /S

cd ..\\..\\..\\dist
copy junit_report.xml junit_report_10_store.xml
del junit_report.xml

exit /B %TESTLEVEL%
