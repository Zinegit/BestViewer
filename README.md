Présentation du projet BestViewer

J’écris ces quelques lignes afin de décrire le plus brièvement possible dans son ensemble le fonctionnement du projet bestViewer.



Mise en route

A ce jour le projet sait lire les fichiers .ply, .obj (.dat aussi à quelques corrections près) et les afficher afin de les visualiser. Les fonctions de culling implémentées permettent de calculer les triangles à envoyer à la partie GPU afin de sauvegarder de la mémoire vive. 
Le culling se fait selon 3 paramètres dont 1 est désactivé :
-le backface culling : permet l’affichage des triangles orientés vers le viewer.
-le frustum culling : permet l’affichage des triangles contenus dans le frustum.
-le occlusion culling : désactivé car trop gourmand en ressources. Il sert à cacher les triangles occultés par d’autres.
Cet occlusion culling est remplacé par le depth culling d’openGl qui cependant force la GPU à faire le travail.

Un premier mode sert uniquement à la visualisation de ces maillages. Le bouton wire permet de switcher de mode d’affichage. L’affichage des textures est possible avec le format .obj.

Lorsque le paramètre d’exécution -debug est ajouté après le chemin du fichier, de nouvelles fonctionnalités deviennent disponibles. 
Premièrement une deuxième fenêtre observer s’afficher. Il s’agit du visualiseur chargé de visualiser le viewer et l’objet afin de voir ce que voit le viewer. Il permet entre autres de vérifier que les méthodes de culling sont bien fonctionnelles.
Deuxièmement la double pression sur le bouton record permet d’enregistrer les différences d’état de chaque triangle entre deux instants. Ceci afin de récupérer un tableau récapitulant si chaque triangles est apparu/disparu/resté inchangé. La coloration de ces triangles se fait alors avec vert : pour apparu, rouge pour disparu et blanc pour inchangé.
La couleur bleue correspond à la ligne de front qui est la zone délimitant les triangles apparaissant et inchangés. Les triangles de la frontline permettent de prédire la position des triangles apparaissant. Pour l’instant le seul mode de prédiction est une prédiction parallélogrammique mais d’autres méthodes peuvent être  implémentées.
Les boutons predict all et predict step by step permettent de visualiser de manière monores la prédiction et la position réelle de chaque triangle. Il serait bien d’implémenter ces méthodes en couplant monores et multires.
La partie serveur est fonctionnelle et correspond au programme permettant de générer les fichiers de coefficients d’erreur de prédiction pour un modèle donné. Ces fichiers peuvent dès à présent, je l’espère, permettre une multitude d’analyses statistiques sur la correction de prédiction lors de la visualisation de modèle 3D.
Ces fichiers devront être récupérés par la partie cliente sur laquelle il reste du travail à faire qui est expliqué dans la partie « To do ».



To do

Ici les principales fonctionnalités dont le projet aurait besoin et que je n’ai pas eu le temps de mettre en place.
-L’application côté client consiste à déterminer les triangles grossiers apparaissant entre deux instants, à prédire la position de leurs enfants à partir d’un triangle adjacent que l’on a déjà et à chercher côté serveur les fichiers de coefficients d’erreur au format suivant : 45_186 par exemple.
Ce format signifie que le triangle grossier 45 sert à prédire le triangle 186. 
Dans ces fichiers on trouve à chaque ligne l’indice du sommet prédit ainsi que ses 3 coordonnées.

-L’affichage des triangles prédits avec les fonctions predict et predictStep ne se fait que sur le modèle monorésolution et ne tient pas compte des parents grossiers. Il faudrait par la suite faire en sorte que le calcul des 

-L’affichage des textures se fait pour l’instant avec un modèle .obj et un fichier image .dds ou .bmp. Le parseur d’obj est basique et ne peut pas lire tous les formats. De plus la partie prédiction ne marche pas sur les fichiers obj car l’ajout du paramètre texture oblige à réindexer les vecteurs de position et fait apparaître des doublons ce qui ne plait pas à la structure halfedgeMesh.

-A l’occasion, trouver un algorithme plus rapide afin d’inclure l’occlusion culling dans le code.

-Séparer le fonctionnement serveur du fonctionnement client en ajoutant un main par exemple.

-La structure variablesToShare permet le partage de variables entre le viewer et l’observer. Cette méthode n’étant pas très propre, il conviendrait de changer la façon dont l’observer accède à ces variables, notamment avec la création d’accesseurs.

Voilà une présentation brève du projet ainsi qu’une liste des tâches à réaliser dans le futur pour un fonctionnement optimal du projet bestviewer. Pour le reste, chaque fonction, chaque classe et chaque fichier est expliqué en détail et en anglais dans un fichier html généré par doxygen.



