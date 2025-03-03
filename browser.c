#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void load_changed(WebKitWebView *webView, WebKitLoadEvent loadEvent, GtkEntry *entry) {
    if (loadEvent == WEBKIT_LOAD_FINISHED) {
        const gchar *uri = webkit_web_view_get_uri(webView);
        gtk_entry_set_text(entry, uri);
    }
}

static void go_to_url(GtkEntry *entry, gpointer user_data) {
    WebKitWebView *webView = WEBKIT_WEB_VIEW(user_data);
    const gchar *url = gtk_entry_get_text(entry);
    webkit_web_view_load_uri(webView, url);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create vertical box layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Create address bar
    GtkWidget *entry = gtk_entry_new();

    // Create web view
    GtkWidget *webView = webkit_web_view_new();

    // Pack UI elements into the layout
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), webView, TRUE, TRUE, 0);

    // Connect signals
    g_signal_connect(entry, "activate", G_CALLBACK(go_to_url), webView);
    g_signal_connect(webView, "load-changed", G_CALLBACK(load_changed), entry);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Load default webpage
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webView), "https://search.brave.com/");
    // Your browser has been Keith-ified (insert anime gif here [])

    // Set up window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    // Start GTK main loop
    gtk_main();
    return 0;
}
