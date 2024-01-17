#include <stdio.h>
#include <json-glib/json-glib.h>
#include "my_example.h"

// G_DEFINE_TYPE will add typedef _MyExample MyExample;
// Hence we need to define _MyExample without the typedef

struct _MyExample {
    GObject parent_instance;
    gchar* title;
    gchar* json_file_path;
};

// C style, .h has the declaration (G_DECLARE_...), .c has the definition (G_DEFINE...)
G_DEFINE_TYPE (MyExample, my_example, G_TYPE_OBJECT)

// static declarations
static void my_example_class_init(MyExampleClass *cls);
static void my_example_init(MyExample *self);
static void my_example_dispose(GObject *obj);
static void my_example_finalize(GObject *obj);


// required functions for class init / instance init
static void my_example_class_init(MyExampleClass *cls) {
    GObjectClass *object_cls = G_OBJECT_CLASS(cls);

    object_cls->dispose = my_example_dispose;
    object_cls->finalize = my_example_finalize;
}

static void my_example_init(MyExample *self) {
    self->title = g_strdup("Default example title");

}

// destructor
static void my_example_dispose(GObject *obj) {
    MyExample *self = (MyExample *)obj;

    g_clear_pointer(&self->title, g_free);
    g_clear_pointer(&self->json_file_path, g_free);
    G_OBJECT_CLASS(my_example_parent_class)->dispose(obj);

}

static void my_example_finalize(GObject *obj) {
    G_OBJECT_CLASS(my_example_parent_class)->finalize(obj);
}

// implement getters and setters
const gchar *my_example_get_title(MyExample *self) {
    return self->title;
}

void my_example_set_title(MyExample *self, const gchar *title) {
    g_free(self->title);
    self->title = g_strdup(title);
}

const gchar *my_example_get_json_file_path(MyExample *self) {
    return self->json_file_path;
}

void my_example_set_json_file_path(MyExample *self, const gchar *path) {
    g_free(self->json_file_path);
    self->json_file_path = g_strdup(path);
}


static void my_example_dump_json_data(MyExample *self) {
    GError          *error = NULL;
    JsonParser      *parser = NULL;
    JsonNode        *root = NULL;
    gchar           *data = NULL;
    JsonReader      *reader;
    const gchar     *info;

    if (!g_file_get_contents(self->json_file_path, &data, NULL, &error)) {
        g_warning(G_STRLOC ": Unable to open json file path %s error(%s)",
                  self->json_file_path, error ? error->message : "unknown");
        if (error) {
            g_error_free(error);
        }
        return;
    }

    parser = json_parser_new();

    if (json_parser_load_from_data(parser, data, -1, &error)) {
        root = json_parser_get_root(parser);
        if (!root) {
             g_warning(G_STRLOC ": Error getting the root");
             return;
        }
        reader = json_reader_new(root);

        json_reader_read_member(reader, "settings");

        json_reader_read_member(reader, "debug");
        info = json_reader_get_string_value (reader);
        g_print("debug is: %s\n", info);
        json_reader_end_member (reader);


        json_reader_read_member (reader, "user_set");
        g_print("For user_set node: \n");
        json_reader_read_member (reader, "summary");
        info = json_reader_get_string_value(reader);
        g_print("summary is: %s\n", info);
        json_reader_end_member (reader);

        json_reader_read_member (reader, "component");
        info = json_reader_get_string_value(reader);
        g_print("component is: %s\n", info);
        json_reader_end_member (reader);

        json_reader_end_member (reader); // end user_set
        json_reader_end_member (reader); // end settings

        g_object_unref(reader);
    }

    g_object_unref(parser);
    g_free(data);
}

// allocate object
MyExample *my_example_new(void) {
    return g_object_new(MY_EXAMPLE_TYPE, 0);
}

int main() {
    const gchar *json_path = "./config.json";
    MyExample *exm = my_example_new();
    my_example_set_title(exm, "Get Json Data");
    my_example_set_json_file_path(exm, json_path);
    printf("====  %s  =====\n", my_example_get_title(exm));

    my_example_dump_json_data(exm);
    return 0;
}
