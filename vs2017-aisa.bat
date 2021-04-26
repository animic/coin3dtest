pushd %~dp0

SET PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE;%PATH%
SET PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE;%PATH%
SET PATH=F:\SDK\Qt\msvc2017_64\bin;%PATH%

SET OpenCV_DIR=F:\SDK\opencv-install

devenv.exe .

popd