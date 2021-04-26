pushd %~dp0


cmake -G "Visual Studio 15 2017 Win64"  ^
      -DCMAKE_TOOLCHAIN_FILE=E:/SDK/vc/scripts/buildsystems/vcpkg.cmake ^
	    -DPython3_EXECUTABLE=E:\\SDK\\vc\\installed\\x64-windows\\tools\\python3\\python.exe ^
      -DCMAKE_INSTALL_PREFIX:PATH=../install ^
	    .

popd
