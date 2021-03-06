# Aura
## Procédure Aura régie

n.b.: les noms des différents ordinateurs ne reflètent pas de leur utilisation réelle.

### Lancement de chaque partie
- Ordinateur _PHOTON_ (**JAUNE**) : 
	- Lancer le fichier ```touchdesigner/start_regie.bat```
- Ordinateur _VISUEL_ (**VERT**) : 
	- Lancer le fichier ```touchdesigner/start_projection.bat``` 
- Ordinateur _REALMOTION_ (**NOIR**) : 
	- Lancer _Watchout Display_. Noter l'IP.
- Ordinateur _AUDIO_ (**ROUGE**) : 
	- Ouvrir le logiciel _Iannix_. Aller dans _Fichier_ > _Ouvrir_ et ouvrir le fichier ```max/other/Mouvement AURA to scale.iannix```. Cliquer sur _Play_
	- Ouvrir le fichier ```max/AURA_MAX_Projet.maxproj``` dans _Max MSP_.
	- Baisser le son master (tout en bas à droite de la fenêtre de _Max MSP_) au plus bas, puis allumer le moteur audio.
- Ordinateur _ALIENWARE_ :
	- Ouvrir le fichier ```watchout/aura_clocher_rectorat.watch``` dans _WATCHOUT Production_
	- Aller dans _Media_ > _Live_


### Overview ordinateurs
- Ordinateur _PHOTON_ (**JAUNE**) : gère les communications entre les différentes parties
- Ordinateur _VISUEL_ (**VERT**) : roule le rendu de la projection du clocher ainsi que de la projection du rectorat.
- Ordinateur _REALMOTION_ (**NOIR**) : procède à l'acquisition des sorties vidéos de _VISUEL_ dans le logiciel _Watchout Display_.
- Ordinateur _AUDIO_ (**ROUGE**) : roule l'intégralité du son du projet.
- Ordinateur _ALIENWARE_ : roule le fichier de contrôle _WATCHOUT PRODUCTION_


### Branchements ordinateurs
n.b.: Se référer au [schéma de connexions](README.md#schema-de-connexions) pour plus de détails
- Ordinateur _PHOTON_ (**JAUNE**) : 
	- 1 ethernet
	- 1 sortie vidéo écran
- Ordinateur _VISUEL_ (**VERT**) : 
	- 1 ethernet
	- 1 sortie vidéo écran
	- 2 sorties vidéo écrans virtuels (acquisition)
- Ordinateur _REALMOTION_ (**NOIR**) : 
	- 1 ethernet
	- 1 acquisition vidéo
	- 1 sortie vidéo écran
	- 4 sorties vidéo :
		1. Clocher haut
		2. Clocher milieu
		3. Clocher bas
		4. Rectorat 
- Ordinateur _AUDIO_ (**ROUGE**) : 
	- 1 ethernet
	- 1 sortie vidéo écran
	- 1 MOTU USB branchée dans
		- 2 snakes
- Ordinateur _ALIENWARE_ :
	- 1 ethernet
