# Devis 4

## Information sur le programme

Programme:        devis3

Date:             17/04/2024

Auteur:           Félix St-Gelais

Pltform matériel: Arduino UNO

Pltform develop : Arduino 2.0.3

Description:      "Programme simplie qui permet de controller le robot."

Fonctionnalités:

- Controle du mouvement (avant, arrière, tourner droite et gauche)
- Controle des dels (rouge, vert, bleu et blanc)
- Arrèt automatique à proximité d'un obstacle, et buzz.
- Détection de la distance au prochain obstacle directement à l'avant du robot.

Notes:

- Ce patron d'entête a été fournit par le département de génie physique du cégep André Laurendeau.
- Ce projet arduino a été généré à l'aide de l'outil [pio_to_arduino](https://github.com/cidit/pio_to_arduino).
  - *Les librairies sont donc notées dans le fichier `libraries.txt`.*
- La detection des obstacle est faite avec les pare chocs infrarouge à l'avant du robot.
  
## Inspirations et credits

Le code pour le senseur ultrason, les dels, et tout ce qui est i2c (donc, par extension les bumpers et le buzzer) ont étés fait à l'aide des fichiers d'exemple du robot trouvés sur waveshare.

## Materiel et composants

- kit Alphabot2-AR
- Arduino UNO
