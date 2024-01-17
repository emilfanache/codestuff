#ifndef MY_EXAMPLE_H
#define MY_EXAMPLE_H

#include <glib-object.h>

G_BEGIN_DECLS

#define MY_EXAMPLE_TYPE (my_example_get_type())


//G_DECLARE_FINAL_TYPE (name of struct, prefix for the object functions, namespace, object name, inherits from...)
G_DECLARE_FINAL_TYPE (MyExample, my_example, EXAMPLE, MYEXAMPLE, GObject)

// getter & setter
const gchar *my_example_get_title(MyExample *self);
void my_example_set_title(MyExample *self, const gchar *title);
const gchar *my_example_get_json_file_path(MyExample *self);
void my_example_set_json_file_path(MyExample *self, const gchar *path);
MyExample *my_example_new(void);

G_END_DECLS

#endif /* MY_EXAMPLE_H */
