#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include "tabs.h"

// Callback to update the address bar when the page load finishes
static void load_changed(WebKitWebView *web_view, WebKitLoadEvent load_event, GtkEntry *entry) {
    if (load_event == WEBKIT_LOAD_FINISHED) {
        const gchar *uri = webkit_web_view_get_uri(web_view);
        gtk_entry_set_text(entry, uri);
    }
}

// Callback to navigate to the URL in the address bar
static void go_to_url(GtkEntry *entry, WebKitWebView *web_view) {
    const gchar *url = gtk_entry_get_text(entry);
    webkit_web_view_load_uri(web_view, url);
}

// Callback to create a new tab when the button is clicked
static void new_tab_clicked(GtkButton *button, gpointer user_data) {
    GtkNotebook *notebook = GTK_NOTEBOOK(g_object_get_data(G_OBJECT(button), "notebook"));
    GtkWidget *entry = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "entry"));
    create_new_tab(notebook, entry);
}

// Callback to update the web view and signals when switching tabs
static void switch_page(GtkNotebook *notebook, GtkWidget *page, guint page_num, GtkEntry *entry) {
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(page);
    const gchar *uri = webkit_web_view_get_uri(web_view);
    gtk_entry_set_text(entry, uri);

    // Reconnect signals to the current web view
    g_signal_handlers_disconnect_by_func(entry, G_CALLBACK(go_to_url), NULL);
    g_signal_connect(entry, "activate", G_CALLBACK(go_to_url), web_view);
    g_signal_handlers_disconnect_by_func(web_view, G_CALLBACK(load_changed), NULL);
    g_signal_connect(web_view, "load-changed", G_CALLBACK(load_changed), entry);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_title(GTK_WINDOW(window), "Keith-ified Browser");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create vertical box layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create toolbar (horizontal box) for entry and buttons
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    // Create address bar
    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(toolbar), entry, TRUE, TRUE, 0);

    // Create "New Tab" button
    GtkWidget *new_tab_button = gtk_button_new_with_label("+");
    gtk_box_pack_start(GTK_BOX(toolbar), new_tab_button, FALSE, FALSE, 0);

    // Create notebook for tabs
    GtkWidget *notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

    // Store references for callbacks
    g_object_set_data(G_OBJECT(new_tab_button), "notebook", notebook);
    g_object_set_data(G_OBJECT(new_tab_button), "entry", entry);

    // Connect signals
    g_signal_connect(new_tab_button, "clicked", G_CALLBACK(new_tab_clicked), NULL);
    g_signal_connect(notebook, "switch-page", G_CALLBACK(switch_page), entry);

    // Create the first tab
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_widget_set_size_request(GTK_WIDGET(web_view), 800, 600);
    webkit_web_view_load_uri(web_view, "https://search.brave.com/");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), GTK_WIDGET(web_view), gtk_label_new("Tab 1"));
    gtk_widget_show_all(GTK_WIDGET(web_view));

    // Connect initial signals for the first tab
    g_signal_connect(entry, "activate", G_CALLBACK(go_to_url), web_view);
    g_signal_connect(web_view, "load-changed", G_CALLBACK(load_changed), entry);

    // Show everything
    gtk_widget_show_all(window);

    // Start GTK main loop
    gtk_main();
    return 0;
}

// Implementation of create_new_tab (if not in tabs.c)
void create_new_tab(GtkNotebook *notebook, GtkWidget *entry) {
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_widget_set_size_request(GTK_WIDGET(web_view), 800, 600);
    webkit_web_view_load_uri(web_view, "https://search.brave.com/");

    static int tab_count = 2; // Start at 2 since Tab 1 is initial
    char tab_label[16];
    snprintf(tab_label, sizeof(tab_label), "Tab %d", tab_count++);

    gtk_notebook_append_page(notebook, GTK_WIDGET(web_view), gtk_label_new(tab_label));
    gtk_widget_show_all(GTK_WIDGET(web_view));

    // Switch to the new tab
    gtk_notebook_set_current_page(notebook, gtk_notebook_page_num(notebook, GTK_WIDGET(web_view)));
}