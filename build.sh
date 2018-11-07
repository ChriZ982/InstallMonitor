out_dir="build"
compilerflags="-std=c++17 -Wall -Wextra -Ofast"
linkerflags="-lstdc++fs"

mkdir $out_dir
clang++ $compilerflags InstallMonitor.cpp -o $out_dir/InstallMonitor-$TRAVIS_TAG-linux-x64 $linkerflags

ls