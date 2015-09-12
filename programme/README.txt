Programme pour compiler et générer automatiquement le script de la revue

Le script à exécuter est le script run.sh
> bash run.sh

Les fichiers à modifier sont dans le dossier original
- META.tex : contient les macros latex pour plusieurs raccoursis 
(voir exemple initial et commantaires dans le fichier)
- NOMS.tex : reprend les noms et photo des profs/personnages ainsi 
que des lieux
- TRAME.tex : contient la trame globale de l'histoire
- ACTE_0.tex : contient le texte de l'acte 0
- ACTE_1.tex : contient le texte de l'acte 1
- ...

Un backup automatique de la dernière version du jour est effectuée 
vers le dossier backup. Le backup est daté.

Le dossier génération contient tout les fichiers nécessaires pour 
générer les fichiers. Normalement rien à bouger dedans sauf pour 
rajouter d'autre fonctionnalités.

