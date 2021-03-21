OpenCV a été utilisé malgré le fait que la version native ne fonctionne pas.
Comme la version OpenCV ne fonctionne pas, il faut la compiler et l'installer.

---------------------------------
Etapes pour exécuter le programme
---------------------------------

A. Pré-requis environnement
---------------------------

Il faudra auparavant charger les bons modules, et les variables d'environnnement en effectuant au préalable ". setup_env && . load_modules".
Sans le ".", les modifications ne sont pas effectués dans l'environnement courant, ce que l'on souhaite.

De plus, certaines étapes nécessiteront un GPU (l'exécution) et peuvent être relativement longues.
C'est pourquoi il est recommandé de les effectuer sur un noeud de calcul.
Pour cela, on a préparé un éxecutable alloc_node qui permet d'allouer un noeud ayant les ressources souhaitées.
Il suffit de le lancer et d'effectuer les manipulations depuis le noeud qui a été alloué par le script.

B. Compiler & installer OpenCV
------------------------------

Tout est à effectuer depuis le répertoire bin.

1) lancer bin/download-opencv pour télécharger opencv

2) lancer bin/build-opencv pour configurer la compilation.

3) Compiler en lancant "make && make install" depuis le répertoire bin/opencv-build.
Cela installe OpenCV dans $HOME/opencv-install.

Comme la compilation d'OpenCV est relativement longue (plusieurs minutes),
on peut l'accélerer en l'effectuant sur un noeud de calcul avec "make -j10".

C. Compiler & installer Kokkos
------------------------------

1) lancer bin/build-kokkos
Pour compiler avec les paramètres nécessaires (architecture PASCAL60, avec CUDA) et installer Kokkos dans $HOME/kokkos-install.
Maintenant, ce projet devient compilable via make.

D. Compiler le projet
---------------------

Depuis le répertoire source, il suffit d'effectuer "make".

C. Exécuter
-----------

./ProjetKokkos help ==> affiche les tests possibles, appelable par son nom ou le numéro.
Par exemple, "./ProjetKokkos 1" lance le test n°1.
Chaque test soit compare deux implémentations, soit lance différentes versions du lissage (avec ou sans CUDA/OpenMP, Gauss-Seidel ou Jacobi).
Sans arguments, tous les tests sont lancés.

-------------------------
D. Changer les paramètres
-------------------------

Ajouter dans le Makefile comme définitions -DFILENAME=<fichier image> -DDEF_K=<k choisi>
pour changer les paramètres du lissage qui sont l'image par défaut et le nombre d'itérations à effectuer k.
