// tabs.c
#include "tabs.h"

void create_new_tab(GtkNotebook *notebook, GtkWidget *entry) {
    // Create a new WebKitWebView for the tab
    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_widget_set_size_request(GTK_WIDGET(web_view), 800, 600);
    webkit_web_view_load_uri(web_view, "https://search.brave.com/");

    // Create a label for the tab
    static int tab_count = 1;
    char tab_label[16];
    snprintf(tab_label, sizeof(tab_label), "Tab %d", tab_count++);

    // Add the web view as a new tab
    gtk_notebook_append_page(notebook, GTK_WIDGET(web_view), gtk_label_new(tab_label));
    gtk_widget_show_all(GTK_WIDGET(web_view));

    // Switch to the new tab
    gtk_notebook_set_current_page(notebook, gtk_notebook_page_num(notebook, GTK_WIDGET(web_view)));
}