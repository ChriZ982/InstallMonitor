out_dir="build"
version=${TRAVIS_TAG:-"local"}
compilerflags="-std=c++17 -Wall -Wextra -Ofast"
linkerflags="-lstdc++fs"

mkdir $out_dir
clang++ $compilerflags src/*.cpp -o $out_dir/InstallMonitor-$version-linux-x64 $linkerflags
