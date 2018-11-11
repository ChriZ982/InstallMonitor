out_dir="build"
version=${TRAVIS_TAG:-"local"}
compilerflags="-std=c++17 -Wall -Wextra"
linkerflags="-lstdc++fs"

mkdir -p ${out_dir}/release ${out_dir}/debug
clang++ ${compilerflags} -target x86_64-linux src/*.cpp -o ${out_dir}/debug/InstallMonitor-${version}-linux-x64 ${linkerflags}
clang++ ${compilerflags} -target i386-linux src/*.cpp -o ${out_dir}/debug/InstallMonitor-${version}-linux-x86 ${linkerflags}
clang++ ${compilerflags} -Ofast -target x86_64-linux src/*.cpp -o ${out_dir}/release/InstallMonitor-${version}-linux-x64 ${linkerflags}
clang++ ${compilerflags} -Ofast -target i386-linux src/*.cpp -o ${out_dir}/release/InstallMonitor-${version}-linux-x86 ${linkerflags}