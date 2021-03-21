Comme la version OpenCV ne fonctionne pas, il faut la compiler et l'installer.

Depuis le répertoire bin:

1) lancer bin/download-opencv
Pour télécharger opencv

2) lancer bin/build-opencv
Pour compiler opencv, sur plusieurs cores via roméo possiblement

3) lancer bin/build-kokkos
Pour compiler Kokkos.

Cela installe Kokkos dans ~/kokkos-install et OpenCV dans ~/opencv-install
Ensuite, ce projet devient compilable via make.
