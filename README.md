# Ballsy
Game with big balls.


# Building
Linux build:
```
mkdir build
cd build
cmake ..
make
```

Requires Allegro5 installed

Android build:
```
mkdir build-android
cd build-android
cmake .. -DWANT_ANDROID=1 -D
make
```

Requires Allegro5 libs built for android installed.
Use [Running Allegro application on Android wiki](https://wiki.allegro.cc/index.php?title=Running_Allegro_applications_on_Android) to
setup your enviorment, for now the build scripts relies on some the enviorment variables they suggest ($TC for android-toolchain).
May change that to a cmake parameter at some point.
