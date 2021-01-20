
# ############################################################################ #
#  _____ ___    ___   ___    _    ___ ___ _____
# |_   _/ _ \  |   \ / _ \  | |  |_ _/ __|_   _|
#   | || (_) | | |) | (_) | | |__ | |\__ \ | |
#   |_| \___/  |___/ \___/  |____|___|___/ |_|
# . . .

<!-- GENERAL -->

## GESTION VARIABLES
`SHLVL` -> Valeure évolue selon le nombre de shell ouvert						<OK>
`_` -> Dernière arguments d'une séquence										<OK>
`$?` -> Dernier code retour rencontré											<OK>

## ERREURS A CORRIGER
`ft_length_new_token` -> expand.c (invalid read) '\0'?
`ft_check_syntax` -> syntax.c (ne doit pas valider "cat >[espace apres chevron]")

## TESTS
$SHLVL :
	- Unset shlvl pour voir si ça segfault
	- Lancer plusieurs fois minishell pour voir si ça s'incrémente correctement
$? :
	- Comparer chaque erreur possible avec le vrais bash


<!----------------------------------------------------------------------------->

# SYSCALLS
- Vérifier chaque appels-systeme (mise ne place de EXIT_ERROR dans le .h)
- Trouver une structure de code qui gère EXIT(FAILLURE, SUCESS, ERROR)
- Libérer tous les allocations mémoire

# ERRNO
- Utiliser la valeure de errno pour afficher les messages
- Ne pas travailler avec errno directement mais plutôt une variable:
	ref: http://manpages.ubuntu.com/manpages/bionic/fr/man3/errno.3.html

# A GERER A LA FIN
- La cohérence variable / structure
- Les leaks mémoires
- La normes

-Astuce pour gerer le probleme de tabulations si utilisation de couleurs.
-Eventuellement bloquer le clavier lors du make (si spam de touche, cree bug d'affichage).


# ############################################################################ #
#  _____ ___ ___ _____ ___ 
# |_   _| __/ __|_   _/ __|
#   | | | _|\__ \ | | \__ \
#   |_| |___|___/ |_| |___/
# . . .

# BUILT-INS
[echo](./_Atelier/tests/echo.md) #
[cd](./_Atelier/tests/cd.md)
[pwd](./_Atelier/tests/pwd.md)
[export](./_Atelier/tests/export.md) #
[unset](./_Atelier/tests/unset.md)
[env](./_Atelier/tests/env.md) #
[exit](./_Atelier/tests/exit.md) #


# ############################################################################ #
#  ___ _   _ _  _  ___ _____ ___ ___  _  _ ___
# | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|
# | _|| |_| | .` | (__  | |  | | (_) | .` \__ \
# |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/
# . . .

<!-- COMMANDES AUTORISEES (stat_loc vaut status, variable qui recevra la valeur) -->
### <stdlib.h>
void			*malloc(size_t size);
void			free(void *ptr);
void 			exit(stat_loc);
### <fcntl.h>
`Ouvrir ou créer un descripteur de fichier`
int				open(const char *path, int oflag, ...);
### <unistd.h>
`Ecrire dans un descripteur de fichier`
ssize_t			write(int fildes, const void *buf, size_t nbyte);
`Lire dans un descripteur de fichier`
ssize_t			read(int fildes, void *buf, size_t nbyte);
`Fermer un descripteur de fichier`
int				close(int fildes);
`Créer un nouveau processus avec le même code source`
pid_t			fork(void);
`Changer le répertoire courant du processus`
int				chdir(const char *path);
`Exécuter un programme`
int				execve(const char *path, char *const argv[], char *const envp[]);
`Récupérer le chemin dans lequel on se trouve`
char			*getcwd(char *buf, size_t size);
`Créer une copie du descripteur de fichier`
int				dup(int fildes);
`Tranformer un descripteur de fichier en copiant un autre descripteur de fichier`
int				dup2(int fildes, int fildes2);
`Créer un tube pour la communication entre processus`
int				pipe(int fildes[2]);
### <sys/wait.h>
`Maintenir un PPID (pere) en vie le temps qu'un PID (fils) se termine`
pid_t			wait(int *stat_loc);
`Identique à wait (obsolète)`
pid_t			wait3(int *stat_loc, int options, struct rusage *rusage);
`Identique presque à wait (obsolète)`
pid_t			wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);
`Identique a wait mais on spécifie le processus à surveiller`
pid_t			waitpid(pid_t pid, int *stat_loc, int options);
### <signal.h>
`Initialiser la variable errno, gestion d'erreurs`
sig_t			signal(int sig, sig_t func);
`Envoyer un signal à un processus`
int				kill(pid_t pid, int sig);
### <sys/stat.h>
`Récupérer les renseignements sur le fichier pointé`
int				stat(const char *restrict path, struct stat *restrict buf);
`Identique à stat mais pour les liens symboliques`
int				lstat(const char *restrict path, struct stat *restrict buf);
`Identique à stat mais pour les descripterus de fichiers`
int				fstat(int fildes, struct stat *buf);
### <dirent.h>
`Ouvre un répertoire et retoune la premiere entrée du répertoire`
DIR				*opendir(const char *filename);
`Consulter un répertoire`
struct dirent	*readdir(DIR *dirp);
`Ferme un répertoire et le descripteur de fichier`
int				closedir(DIR *dirp);
### <stdio.h>
`Retourner le message d'erreur correspondant à errno`
char			*strerror(int errnum);
### <sys/errno.h>
`Contient le numéro d'erreur`
errno

<!-- COMMANDES UTILES -->
### <sys/types.h>
pid_t 			getpid(void);
pid_t 			getppid(void);
uid_t 			getuid(void);
gid_t 			getgid(void);
