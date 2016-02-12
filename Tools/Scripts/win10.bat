mkdir dist
mkdir dist\\windows

cd Tools\\Scripts
call npm install .
echo Installing JSC built for Windows 10
call node setup.js -s 10.0 --no-color --no-progress-bars

cd build
call npm install .
echo Building for Windows 10
call node build.js -s 10.0 -m 14.0 -o WindowsStore-x86
SET BUILDLEVEL=%ERRORLEVEL%
IF %BUILDLEVEL% NEQ 0 (
	rmdir node_modules /Q /S
	exit /B %BUILDLEVEL%
)
call node test.js -s 10.0 -T ws-local
SET TESTLEVEL=%ERRORLEVEL%
rmdir node_modules /Q /S
cd ..\\..\\..

cd dist
copy junit_report.xml junit_report_10.xml
cd ..

exit /B %TESTLEVEL%
