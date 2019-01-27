# Installation Windows

## prérequis

*****MinGw/Msys: ***** [download](https://sourceforge.net/projects/mingw/files/latest/download)

  - installer msys et mingw32 en suivant les instructions de l'installer

Avec une installation dans C:/MinGw/

Ajouter C:/MinGw/bin dans le path
Cela permet d'utiliser gcc et d'avoir comme contexte C:\MinGw\

*****Libraries: *****

 Pour chaque dossier dll/ include/ et lib/, copier le contenu

  - include/ => C:\MinGW\include
  - lib/ => C:\MinGW\lib
  - dll/ dans le dossier de l'exe

  ## usage

  Depuis une invite de commande à la racine du projet:

  `mingw32-make.exe [cmd]`
