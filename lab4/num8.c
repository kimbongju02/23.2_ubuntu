#include <gtk/gtk.h>

// 버튼 클릭 이벤트 핸들러
static void button_clicked(GtkWidget *widget, gpointer data) {
    g_print("button click\n");
}

// 프로그램 진입점
int main(int argc, char *argv[]) {
    // GTK 초기화
    gtk_init(&argc, &argv);

    // 윈도우 생성
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK program");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 버튼 생성
    GtkWidget *button = gtk_button_new_with_label("click!");
    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);

    // 버튼을 윈도우에 추가
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_container_add(GTK_CONTAINER(window), box);

    // 모든 위젯을 표시
    gtk_widget_show_all(window);

    // 메인 루프 시작
    gtk_main();

    return 0;
}

// gcc your_program.c -o your_program $(pkg-config --cflags --libs gtk+-3.0)
