#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

// Initialisation des widgets GTK + char* permettant de stocker les chiffres/opérandes à afficher

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button0;
GtkWidget	*button1;
GtkWidget	*button2;
GtkWidget	*button3;
GtkWidget	*button4;
GtkWidget	*button5;
GtkWidget	*button6;
GtkWidget	*button7;
GtkWidget	*button8;
GtkWidget	*button9;
GtkWidget	*buttonP;
GtkWidget	*buttonM;
GtkWidget	*buttonD;
GtkWidget	*buttonF;
GtkWidget	*buttonCE;
GtkWidget	*buttonEgal;

GtkWidget	*label1;
GtkBuilder	*builder; 
GtkListStore	*liststore1;
GtkAdjustment	*adjustment2;

char textPrint[100] = "";
int pointeur = 0;
int isResultPrint = 0;


int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk
 
	builder = gtk_builder_new_from_file ("calculatrice.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button0 = GTK_WIDGET(gtk_builder_get_object(builder, "button0"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
	button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
	button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
	button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
	button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
	button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
	button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
	buttonP = GTK_WIDGET(gtk_builder_get_object(builder, "buttonP"));
	buttonM = GTK_WIDGET(gtk_builder_get_object(builder, "buttonM"));
	buttonF = GTK_WIDGET(gtk_builder_get_object(builder, "buttonF"));
	buttonD = GTK_WIDGET(gtk_builder_get_object(builder, "buttonD"));
	buttonCE = GTK_WIDGET(gtk_builder_get_object(builder, "buttonCE"));
	buttonEgal = GTK_WIDGET(gtk_builder_get_object(builder, "buttonEgal"));	

	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));

	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
}

void calcule() {
	 // Par défaut
	 char part1[15] = "";
	 char part2[15] = "";
	 char operateur = '+';
	 int ptr1 = 0;
	 int ptr2 = 0;
	 int x = 0;

	// On sépare : partie gauche dans part1, partie droite dans part2 et opérateur dans operateur

    for (x = 0; x < strlen(textPrint); x++) {
        if (textPrint[x] == '*' || textPrint[x] == '+' || textPrint[x] == '-' || textPrint[x] == '/') {
            operateur = textPrint[x];
			break;
		} else {
			part1[ptr1] = textPrint[x];
			ptr1++;
		}
	}
	for (int y = x+1; y < strlen(textPrint); y++) {
		part2[ptr2] = textPrint[y];
		ptr2++;
	}

	// Selon l'opérateur : on calcule l'int résultat
	int result;
	if(operateur == '+') result = atoi(part1) + atoi(part2);
	if(operateur == '-') result = atoi(part1) - atoi(part2);
	if(operateur == '*') result = atoi(part1) * atoi(part2);
	if(operateur == '/') result = atoi(part1) / atoi(part2);
	
	// Clear tableau + affichage du résultat
	pointeur = 0;
	memset(textPrint, '\0', sizeof(textPrint));
	sprintf(textPrint, "%i", result);
	gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) textPrint);

	// Boolean permettant de clear le tableau à l'appui de la prochaine touche
	isResultPrint = 1;	
}

// Affiche le tableau de char, avec la touche cliquée en +
void affiche(char c) {
	if(isResultPrint) {
		pointeur = 0;
		memset(textPrint, '\0', sizeof(textPrint));
		isResultPrint = 0;
	}
	
	textPrint[pointeur] = c;
	pointeur++;
	gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) textPrint);
}

void on_button0_clicked (GtkButton *b) {
	affiche('0');
}
void on_button1_clicked (GtkButton *b) {
	affiche('1');
}
void on_button2_clicked (GtkButton *b) {
	affiche('2');
}
void on_button3_clicked (GtkButton *b) {
	affiche('3');
}
void on_button4_clicked (GtkButton *b) {
	affiche('4');
}
void on_button5_clicked (GtkButton *b) {
	affiche('5');
}
void on_button6_clicked (GtkButton *b) {
	affiche('6');
}
void on_button7_clicked (GtkButton *b) {
	affiche('7');
}
void on_button8_clicked (GtkButton *b) {
	affiche('8');
}
void on_button9_clicked (GtkButton *b) {
	affiche('9');
}
void on_buttonP_clicked (GtkButton *b) {
	affiche('+');
}
void on_buttonM_clicked (GtkButton *b) {
	affiche('-');
}
void on_buttonD_clicked (GtkButton *b) {
	affiche('/');
}
void on_buttonF_clicked (GtkButton *b) {
	affiche('*');
}
// Clear affichage et textPrint
void on_buttonCE_clicked (GtkButton *b) {
	pointeur = 0;
	memset(textPrint, '\0', sizeof(textPrint));
	gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) textPrint);
}
// Affiche la réponse
void on_buttonEgal_clicked (GtkButton *b) {
	calcule();
}
