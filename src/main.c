#include <cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <X11/Xlib.h>
#include <kplot.h>
#include <gtk/gtk.h>
// Custom structure that holds pointers to widgets and user variables
typedef struct {
    // Add pointers to widgets below
    GtkWidget *drawing_area;
} app_widgets;
    
static void do_drawing(cairo_t *cr)
{
    struct kpair	 points1[10], points2[10];
	struct kdata	*d1, *d2;
	struct kplot	*p;
	//cairo_surface_t	*surf;
	size_t		 i;
	//cairo_t		*cr;
	//cairo_status_t	 st;
    
    d1 = d2 = NULL;
    p = NULL;
    
    for (i = 0; i < 10; i++) {
		points1[i].x = points1[i].y = (double)i * 1000;
		points2[i].x = points2[i].y = (double)i * -1000;
	}
    
    	if (NULL == (d1 = kdata_array_alloc(points1, 50))) {
		perror(NULL);
		goto out;
	} else if (NULL == (d2 = kdata_array_alloc(points2, 50))) {
		perror(NULL);
		goto out;
	} else if (NULL == (p = kplot_alloc(NULL))) {
		perror(NULL);
		goto out;
	} else if ( ! kplot_attach_data(p, d1, KPLOT_LINES, NULL)) {
		perror(NULL);
		goto out;
	} else if ( ! kplot_attach_data(p, d2, KPLOT_POINTS, NULL)) {
		perror(NULL);
		goto out;
	}
    
    kdata_destroy(d1);
	kdata_destroy(d2);
	d1 = d2 = NULL;
    
    //surf = cairo_image_surface_create
	//	(CAIRO_FORMAT_ARGB32, 600, 400);

	//st = cairo_surface_status(surf);
	//if (CAIRO_STATUS_SUCCESS != st) {
	//	fprintf(stderr, "%s", cairo_status_to_string(st));
	//	cairo_surface_destroy(surf);
	//	kplot_free(p);
	//}

	//cr = cairo_create(surf);
	//cairo_surface_destroy(surf);

	//st = cairo_status(cr);
	//if (CAIRO_STATUS_SUCCESS != st) {
	//	fprintf(stderr, "%s", cairo_status_to_string(st));
	//	cairo_destroy(cr);
	//	kplot_free(p);

	//}
    
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
	cairo_rectangle(cr, 0.0, 0.0, 600.0, 400.0);
	cairo_fill(cr);
	kplot_draw(p, 600.0, 400.0, cr);
    
    //st = cairo_surface_write_to_png
	//	(cairo_get_target(cr), "example1.png");

	//if (CAIRO_STATUS_SUCCESS != st) {
	//	fprintf(stderr, "%s", cairo_status_to_string(st));
	//	cairo_destroy(cr);
	//	kplot_free(p);
	//}

	//cairo_destroy(cr);
out:
	kplot_free(p);
	kdata_destroy(d1);
	kdata_destroy(d2);
    //cairo_set_source_rgb(cr, 0, 0, 0);
    //cairo_select_font_face(cr,"Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    //cairo_set_font_size(cr, 40.0);
    
    //cairo_move_to(cr, 10.0, 50.0);
    //cairo_show_text(cr, "Hello world");
    }
    
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, app_widgets* widgets)
{
    do_drawing(cr);
    return FALSE;
    }
    
int main(int argc, char *argv[])
{
    GtkBuilder      *builder; 
    GtkWidget       *window;
    // Instantiate structure, allocating memory for it
    app_widgets     *widgets = g_slice_new(app_widgets);
    
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    widgets->drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
    
     // Widgets pointer are passed to all widget handler functions as the user_data parameter
    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show_all(window);                
    gtk_main();
    // Free up widget structure memory
    g_slice_free(app_widgets, widgets);

    return 0;
}

// Dummy handler function
/*void x(GtkButton *button, app_widgets *app_wdgts)
{
}*/

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
