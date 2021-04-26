pushd %~dp0

SET PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE;%PATH%
SET PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\IDE;%PATH%
SET PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE;%PATH%

SET IMPERX_HOME=C:\Program Files\Imperx\
SET PATH=%IMPERX_HOME%\Imperx Camera SDK\bin\win64_x64;%PATH%

start devenv.exe .

popd