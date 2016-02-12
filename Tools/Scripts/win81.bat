mkdir dist
mkdir dist\\windows

cd Tools\\Scripts
call npm install .
call node setup.js --no-color --no-progress-bars

cd build
call npm install .
echo Building for Windows 8.1
call node build.js -s 8.1 -m 12.0 -o WindowsStore-x86
SET BUILDLEVEL=%ERRORLEVEL%
IF %BUILDLEVEL% NEQ 0 (
	rmdir node_modules /Q /S
	exit /B %BUILDLEVEL%
)
call node test.js -s 8.1 -T ws-local
SET TESTLEVEL=%ERRORLEVEL%
rmdir node_modules /Q /S
cd ..\\..\\..

cd dist
copy junit_report.xml junit_report_8_1.xml
cd ..

exit /B %TESTLEVEL%
