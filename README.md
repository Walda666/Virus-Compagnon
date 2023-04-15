# Virus Compagnon

## Description
Virus de type compagnon crée dans le cadre d'un projet scolaire (ULR).

Le fichier MediaPlayer.exe infecte tous les exécutables du même répertoire à son lancement en se dupliquant. Puis à chaque lancement d'un programme infecté, une nouvelle infection se lance sur les nouveaux exe non infectés du répertoire.

Le tout se déroulant en arrière-plan pour ne pas éveiller les soupçons de l'utilisateur.

## Contenu
Ce projet contient : 
- le virus/lecteur de médias principal 'MediaPlayer.exe'
- 5 mini-programmes de test
- plusieurs images pour tester le lecteur de médias
- 2 fichiers .glade permettant de faire fonctionner les interfaces graphiques
- un fichier d'installation 'install.sh'



## Mini-programmes

5 <b>mini</b>-programmes sont présents pour tester ce virus : 

1. MonPG1 : Convertisseur de taille : mètres -> pieds
1. MonPG2 : Calculatrice avec interface graphique
1. MonPG3 : Utilitaire retournant le mot le plus long d'une phrase
1. MonPG4 : Mini-jeu du Juste Prix 
1. MonPG5 : Utilitaire permettant de calculer une moyenne


## Installation & lancement

Pour installer le bot, procédez comme tel :
- Commenter les lignes non-nécessaires du fichier install.sh (apt update & upgrade)
- Entrer la commande suivante pour compiler les 6 programmes :

```bash
./install.sh
```

Puis, pour lancer un programme, entrer la commande suivante :
```bash
./'nomProgramme'.sh
```

## Ajouts possibles
Nous n'avons pas eu assez de temps pour finir ce projet comme nous le souhaitions. Les modifications que nous aurions aimé effectuer sont les suivantes :
- Recadrer les images dans le lecteur de médias pour permettre autre chose que des .png.
- Réaliser des mini-programmes plus avancés et avec plus d'interfaces graphiques.
- Réaliser une version obfusquée et assombrie du code pour masquer la partie virale.

## Ateurs
Ce projet à été réalisé avec l'aide de [Romain Piet](https://github.com/Jhyiin)