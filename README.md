# projetSACAlexis
Voici le projet SAC de Alexis

## C'est quoi?
C'est un projet PlatformIO qui gère le séchage pour l'entreprise Les Meubles Dubé inc.
Il est conçu pour fonctionner sur un microcontrôleur ESP32 avec plusieurs librairies, ceux-ci étant incluses dans le fichier platformio.ini

## Demande du client

Le principe est le suivant. Lorsque l'ouvrier place le bois dans le four, il referme la porte et actionne un bouton « Démarrage » pour démarrer le processus. C'est alors que le compte à rebours commence. Si la température n'est pas dans plage convenue (température donnée plus ou moins 10%), le compte à rebours arrête et repart à la bonne température.

Chaque four est connecté à un service WEB et il est possible de choisir un type de bois prédéfini. Vous devez obtenir les caractéristiques tels que le temps de séchage et la température nécessaire pour le séchage en utilisant un service WEB (nodeJs). Voir les fiches du service WEB qui suivent.




