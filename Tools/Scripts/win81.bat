mkdir dist
mkdir dist\\windows

cd Tools\\Scripts
call npm install .
echo Installing JSC built for Windows 8.1
call node setup.js --no-color --no-progress-bars

cd build
call npm install .
echo Building for Windows 8.1
call node build.js -s 8.1 -m 12.0 -o WindowsStore-x86 -o WindowsPhone-x86 -o WindowsPhone-ARM
SET BUILDLEVEL=%ERRORLEVEL%
IF %BUILDLEVEL% NEQ 0 (
	rmdir node_modules /Q /S
	exit /B %BUILDLEVEL%
)

echo Running Tests on Windows 8.1 Phone Emulator
call node test.js -p Windows8_1.Phone
SET TESTLEVEL=%ERRORLEVEL%

echo Copying JUnit report
cd ..\\..\\..\\dist
copy junit_report.xml junit_report_8_1_phone.xml
del junit_report.xml
cd ..\\Tools\\Scripts\\build

IF %TESTLEVEL% NEQ 0 (
	rmdir node_modules /Q /S
	exit /B %TESTLEVEL%
)

echo Running Tests on Windows 8.1 Desktop
call node test.js -s 8.1 -T ws-local -p Windows8_1.Store
SET TESTLEVEL=%ERRORLEVEL%

rmdir node_modules /Q /S

cd ..\\..\\..\\dist
copy junit_report.xml junit_report_8_1_store.xml
del junit_report.xml

exit /B %TESTLEVEL%
