cd apidoc
rmdir Titanium /Q /S
call npm install .
echo Exit Code = %ERRORLEVEL%
call node -v
call node ti_win_yaml.js
echo Exit Code = %ERRORLEVEL%
