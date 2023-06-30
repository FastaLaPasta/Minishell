# 🐚 **Minishell** 🐚

**_readline_** : lis ce qu’on écrit sur l’entrée Standard, malloc donc a free;

EXEMPLE : 

	char* input;
	input = readline("Entrez une chaîne : ");
	if (!input)
	{
	    /*L'utilisateur a appuyé sur CTRL + D pour quitter le programme. */
	    printf("\n");
	    break;
	 }


**_rl_clear_history_** : Cette fonction supprime toutes les entrées de l’historique.

EXEMPLE : 

	rl_clear_history(); (is simple)

**_rl_on_new_line_** : Permet de se replacer sur one nouvelle ligne en supprimant tous ce qui a été entrée sur la ligne actuel; Juste a appelé; PARFAIT POUR CTRL+C

**_rl_replace_line_** : replace la ligne actuel avec une de notre choix;

EXEMPLE : 

	rl_replace_line(“nouvelle ligne”, 0); 0 étant la taille de la nouvelle ligne, mettre 0 calcul automatiquement la taille de la ligne;

**_rl_redisplay_** : Permet d’afficher la ligne de commande, a utiliser après un rl_replace_line. Attention elle ne deplace pas le curseur vers une nouvelle ligne; Juste 				   appelé.

				 


**_add_history_** : ajoute a la fin de l’historique l’entré lu;

EXEMPLE :
	
	add_history(char *input);

# 📡 🛰️ **== SIGNAL ==** 🛰 📡

**_wait3_** : attend jusqu’à ce qu’un fils finisse et récupère info.
**_wait4_** : attend jusqu’à ce qu’un fils “id” finisse et stocker les informations sur l’utilisation des processus sytème.


**_signal_** : cette fonction receptionne un numéro de signal a gérer (premier argument), qui sera alors traité par la fonction approprié (second argument). A noté qu'on préfère utiliser la fonction sigaction pour plus de précision.

EXEMPLE :

		void (*signal(int signum, void (*handler)(int)))(int);
		// Spécifier la fonction de gestion pour SIGINT
	signal(SIGINT, signal_handler);

		// Boucle infinie pour maintenir le programme en cours d'exécution
		while(1)
		{
			printf("En attente du signal SIGINT...\n");
			sleep(1);
		}

**_sigaction_** : La fonction sigaction permet de gérer des signaux comme la fonction signal, mais permet de spécifier des optons avancées pour le traitement des signaux comme : la possibilité de bloquer d'autre signaux,la possibilité de specifier une nouvelle action pour le signal ou  de specifier des indicateurs de comportement pour la gestion du signal. Elle prend en arguments une ou plusieurs structure afin de récupérer les signaux et les gérers.

**_sigemptyset_** : Cette fonction permet de vider un ensemble de signaux, on peut par exemple lui passer une structure contenant d'ancier signaux afin qu'elle la vide pour pouvoir ensuite en mettre de nouveaux. Pour finalements gérer les nouveaux signaux avec sigaction (au hasard). A noté que l'ensemble de signaux passer a la fonction doit être initialiser.

EXEMPLE :
		
	    struct sigaction sa;
	    sigset_t myset;

	    // Initialise myset à vide
	    sigemptyset(&myset);

**_kill_** : La fonction kill permet d'envoyer un signal a un processus ou a un groupe de processus, elle prend en paramètre l'identifiant du processus ou du groupe de processus à qui le signal foit etre envoyé, aisni que le numéro du signal à envoyer.

EXEMPLE :
		
		pid_t pid = /* ... */;
    
	        // Envoie un signal SIGTERM au processus identifié par pid
	        if (kill(pid, SIGTERM) == -1)
		{
	        	perror("kill");
		        exit(EXIT_FAILURE);
	        }

# 📂 **== CHANGE DIRECTORY FUNCTION ==** 📂

**_getcwd_** : getcwd est utilisé pour obtenir le chemin absolu vers le repertoir de travail actuel de l'application en cours d'execution, il prend en parametre une chaine de caractere qui va acceuillir le chemin, et en second parametre la taille maximum de la chaine.

EXEMPLE :
		
		char buf[1024];
	        if (getcwd(buf, sizeof(buf)) != NULL)
		{
		    printf("Le répertoire de travail actuel est : %s\n", buf);
	        }


**_chdir_** : chdir est utilisées pour changer le répertoire de travail courant. Elle prend en entrée un seul argument qui est une chaine de caractères représentant le chemin absolu/relatif du répertoire de destination.

EXEMPLE :
		
		if (chdir("/home/user/Documents") == 0)
        		printf("Le répertoire de travail courant a été modifié avec succès.\n");

**_stat_** : La focntion stat permet de récupérer des informations sur un fichier ou un repertoire. Elle prend en entrée le nom du fichier ou du repertoire en question, ainsi qu'un estrucure stat qui sera remplie navec les infos.

EXEMPLE :
		
		 struct stat file_stat;
		    const char* file_path = "/path/to/file.txt";

		    if (stat(file_path, &file_stat) != 0)
		    {
			perror("stat() a échoué");
			return 1;
		    }

**_lstat_** : comme Stat mais récupère des infos sur un liens symbolique.

**_fstat_** : Comme stat mais prend un file descriptor a la place d'un nom de fichier.

**_unlink_** : permet de supprimer un fichier du système de fichiers.

**_opendir_** : permet d'ouvrir un répertoire du système de fichiers pour pouvoir accéder aux fichiers qu'il contient.

**_readdir_** : permet de lire les entrées d'un répertoire du système de fichiers ouvert avec la fonction opendir().

**_closedir_** : permet de fermer un répertoire ouvert avec la fonction opendir() et libère les ressources associées.

**_ioctl_** : (Input/Output Control) est une fonction de bas niveau en C utilisée pour communiquer avec des périphériques ou des fichiers spéciaux dans les systèmes d'exploitation de type Unix. Elle permet d'envoyer des commandes spécifiques à un périphérique ou à un fichier spécial pour contrôler son comportement ou pour récupérer des informations sur son état.

**_getenv_** : permet de récupérer la valeur d'une variable d'environnement. Les variables d'environnement sont des variables globales stockées dans le système d'exploitation, qui contiennent des informations telles que le nom d'utilisateur, le répertoire de travail actuel, le chemin de recherche des programmes, etc.

# 💻 **== TERMINAL ==** 💻

**_isatty_** : permet de vérifier si un descripteur de fichier correspond à un terminal interactif. Elle renvoie 1 si le descripteur de fichier est associé à un terminal interactif, et 0 sinon.

**_ttyname_** : permet de récupérer le nom du terminal associé à un descripteur de fichier. Elle renvoie une chaîne de caractères contenant le nom du terminal, ou un pointeur NULL si le descripteur de fichier n'est pas associé à un terminal.

**_ttyslot_** : permet de récupérer l'index du terminal associé à un descripteur de fichier dans la base de données des terminaux.

**_tcsetattr_** : permet de configurer les attributs d'un terminal en utilisant les termios.

**_tcgetattr_** : permet d'obtenir les attributs d'un terminal en utilisant la structure termios.

**_tgetent_** : permet de lire les informations de la base de données des terminaux "termcap". Cette base de données contient des informations sur les capacités de contrôle de différents terminaux, telles que la couleur, la position du curseur, la saisie semi-automatique, etc.

**_tgetflag_** :  permet de récupérer une capacité du terminal à partir de la base de données "termcap". Cette fonction est utilisée pour interroger la base de données "termcap" sur une capacité particulière du terminal, telle que la prise en charge de la couleur ou du contrôle de flux.

**_tgetnum_** : permet de récupérer une capacité numérique du terminal à partir de la base de données "termcap". Cette fonction est utilisée pour interroger la base de données "termcap" sur une capacité numérique particulière du terminal, telle que la largeur ou la hauteur de l'écran.

**_tgetstr_** : permet de récupérer une capacité de chaîne de caractères du terminal à partir de la base de données "termcap". Cette fonction est utilisée pour interroger la base de données "termcap" sur une capacité de chaîne de caractères particulière du terminal, telle que la séquence de contrôle pour effacer l'écran ou pour changer la couleur du texte.

**_tgoto_** : permet de construire une séquence de contrôle pour déplacer le curseur à une position donnée sur l'écran en utilisant la base de données "termcap". Cette fonction est utilisée pour construire des séquences de contrôle dynamiques qui peuvent déplacer le curseur à différentes positions de l'écran.

**_tputs_** : permet d'envoyer des séquences de contrôle à un terminal, en utilisant la base de données "termcap". Cette fonction est utilisée pour envoyer des séquences de contrôle statiques ou dynamiques qui peuvent modifier l'apparence ou le comportement du terminal.




Les méta-caractères (ou métacaractères) sont des caractères spéciaux qui ont une signification particulière dans l'interprétation des commandes dans un shell. Voici les principaux méta-caractères utilisés dans les shells Unix :

    * : Représente n'importe quelle chaîne de caractères, y compris une chaîne vide.
    ? : Représente un caractère quelconque.
    [] : Permet de spécifier une liste de caractères possibles, par exemple [a-z] pour toutes les lettres minuscules de l'alphabet latin.
    ~ : Représente le répertoire personnel de l'utilisateur.
    $ : Indique une variable d'environnement, par exemple $HOME pour le répertoire personnel de l'utilisateur.
    ; : Sépare plusieurs commandes sur une même ligne.
    | : Permet de rediriger la sortie d'une commande vers l'entrée d'une autre commande.
    > : Redirige la sortie standard d'une commande vers un fichier, en écrasant le contenu existant.
    >> : Redirige la sortie standard d'une commande vers un fichier, en ajoutant le contenu à la fin du fichier existant.
    < : Redirige l'entrée standard d'une commande à partir d'un fichier.

Il est important de prendre en compte ces méta-caractères lors de l'écriture de commandes dans un shell pour éviter des erreurs d'interprétation.
