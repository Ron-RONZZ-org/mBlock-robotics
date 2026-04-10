Also do following exercices:

Exercice 13 : arrêt avant obstacle Faire un programme qui fait avancer le robot à une

vitesse de 128 et qui l’arrête définitivement dès qu’un obstacle est détecté en dessous
de 50 centimètres.
Exercice 14 : tourner en direction, v1 Créer une variable a. Tourner le robot à droite
jusqu’à ce que son orientation (axe z du gyroscope) atteigne la valeur donnée dans la
variable a. Tester votre programme avec différentes valeurs de la variable a, en
particulier a = 90°, 150°, 270°, et 360° (un tour complet). Il est obligatoire d’utiliser le
bloc en mode « tourner à droite » pour
cet exercice.
Exercice 15 : tourner en direction, v2 Créer une variable a. Tourner le robot à droite
jusqu’à ce que son orientation (axe z du gyroscope) atteigne la valeur donnée dans la
variable a. Tester votre programme avec différentes valeurs de la variable a, en
particulier a = 90°, 150°, 270°, et 360° (un tour complet). Il est obligatoire d’utiliser le
bloc en mode « tourner à droite », et le gyroscope pour
déterminer quand le robot s’arrête.
Questions pour le rapport : Discutez les avantages et inconvénients des deux appro-
ches au même problème en exercices 14 et 15.
Exercice 16 : tourner par angle Créer une variable a qui détermine l’angle de rotation.
Tourner le robot à droite par cet angle a trois fois de suite. Après chaque rotation par a,
arrêter le robot et allumer les LEDs pendant 1 seconde. Tester le logiciel d’abord avec a
= 90°, puis avec a = 150°. En vue des exercices suivants, implémentez une solution qui
utilise le gyroscope pour déterminer l’orientation du robot.
Exercice 17 : distance vs orientation Créer une variable a. Faire un logiciel qui tourne
le robot par 360° autour de lui-même avec des pas de a : tester avec a = 10° et a = 15°.
Pour chaque orientation, mesurer la distance avec le capteur ultrason et afficher la
distance mesurée à l’aide des LEDs (voir Exercice 9 : ultrason et LEDs). Utiliser une
intensité très basse pour les LEDs afin d’économiser de l’énergie car le moteur est très
énergivore.
Page | 26
TP Informatique Industrielle portail ISFATES & SPI
Maintenant vous allez combiner les éléments des exercices précédents pour un
programme complexe.
Exercice 18 : contourner un obstacle Faire un programme qui fait rouler le robot ave
une vitesse 128 et qui arrête provisoirement le robot dès qu’un obstacle se trouve à une
distance inférieure à 30 centimètres. Aussitôt après la période d’arrêt, le robot tourne
sur lui-même à 360° pour détecter la plus grande zone libre d’obstacle (obstacle le plus
loin). Il se dirigera ensuite vers la première zone la plus dégagée qu’il a détecté.
