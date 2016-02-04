# ![Aura - Traversée immersive](doc/logo.png)

### Méthodologie
- La branche `master` contient une version stable du projet
- La branche `develop` contient la version de développement du projet.
Lors de votre travail, utilisez la branche `develop`.  
Pour chaque sprint, un "pull request" sera ouvert, puis mergé à la fin du sprint dans la branche master. Aussi, un tag sera ajouté au commit lors du merge.

### Cloner le projet
```
git clone git@github.com:MIUQAM/aura.git
cd aura
git checkout develop
```

### Télécharger les ressources audio 
Les ressources audio sont stockées séparément de ce repository.  
Il vous faut installer [Git LFS](https://git-lfs.github.com/).  
Sur Mac : `brew install git-lfs`.  
Sur Windows : [en bas, Windows AMD64](https://github.com/github/git-lfs/releases/latest).  
Une fois Git LFS installé, exécuter la commande suivante :
```
git lfs pull
```

### Schéma de communication visuel
![Schéma de communication visuel](doc/schema_visuel.png)

### Schéma de connexions
![Schéma de connexions](doc/schema_connexions.png)
(cliquer pour élargir)