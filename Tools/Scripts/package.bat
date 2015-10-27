call git clean -fdx

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

cd Tools\Scripts
call npm install .
call node setup.js --no-color --no-progress-bars

cd build
call npm install .
call node build.js
call node test.js
rmdir node_modules /Q /S
cd ..\..\..

exit /B %ERRORLEVEL%
