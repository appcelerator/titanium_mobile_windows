Files in this folder are copied directory into the Windows build directory
when the Windows app is compiled:

    <project-dir>/build/windows

You can place files such as res strings or drawable files.

Files in this directory are copied directly on top of whatever files are already
in the build directory, so please be careful that your files don't clobber
essential project files or files from other modules.
