#include <gtk/gtk.h>

// 계산기 상태를 저장하는 구조체
typedef struct {
    GtkWidget *entry; // 결과를 표시하는 엔트리 위젯
    double input;
    double result;   // 현재 결과 값을 저장하는 변수
    char operator;   // 현재 수행 중인 연산자를 저장하는 변수
} CalculatorData;

// 숫자 버튼이 클릭될 때 호출되는 콜백 함수
static void number_button_clicked(GtkWidget *button, gpointer data) {
    CalculatorData *calc_data = (CalculatorData *)data;

    const char *button_label = gtk_button_get_label(GTK_BUTTON(button));
    double number = atof(button_label);

    // 현재 결과 값을 가져와서 숫자를 추가
    char entry_text[50];
    snprintf(entry_text, sizeof(entry_text), "%s%s", gtk_entry_get_text(GTK_ENTRY(calc_data->entry)), button_label);

    // 결과 엔트리 업데이트
    gtk_entry_set_text(GTK_ENTRY(calc_data->entry), entry_text);
}

// 연산자 버튼이 클릭될 때 호출되는 콜백 함수
static void operator_button_clicked(GtkWidget *button, gpointer data) {
    CalculatorData *calc_data = (CalculatorData *)data;

    const char *button_label = gtk_button_get_label(GTK_BUTTON(button));
    calc_data->operator = button_label[0];

    // 현재 결과 값을 가져와서 변수에 저장
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(calc_data->entry));
    calc_data->result = atof(entry_text);

    char new_text[50];
    snprintf(new_text, sizeof(new_text), "%s%s", entry_text, button_label);

    // 결과 엔트리 업데이트
    gtk_entry_set_text(GTK_ENTRY(calc_data->entry), new_text);
}

// 등호 버튼이 클릭될 때 호출되는 콜백 함수
static void equal_button_clicked(GtkWidget *button, gpointer data) {
    CalculatorData *calc_data = (CalculatorData *)data;

    // 현재 결과 값을 가져와서 변수에 저장
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(calc_data->entry));
    const char *operator_position = strpbrk(entry_text, "+-*/");
    if (operator_position != NULL) {
        const char *number_after_operator = operator_position + 1;
        calc_data->input = atof(operator_position+1);
    }

    // 현재 연산자에 따라 계산 수행
    switch (calc_data->operator) {
        case '+':
            calc_data->result += calc_data->input;
            break;
        case '-':
            calc_data->result -= calc_data->input;
            break;
        case '*':
            calc_data->result *= calc_data->input;
            break;
        case '/':
            if (calc_data->input != 0.0) {
                calc_data->result /= calc_data->input;
            } else {
                gtk_entry_set_text(GTK_ENTRY(calc_data->entry), "Error");
                return;
            }
            break;
    }

    // 결과 엔트리에 계산 결과 표시
    char result_text[50];
    snprintf(result_text, sizeof(result_text), "%.6f", calc_data->result);
    gtk_entry_set_text(GTK_ENTRY(calc_data->entry), result_text);
}

// Clear 버튼이 클릭될 때 호출되는 콜백 함수
static void clear_button_clicked(GtkWidget *button, gpointer data) {
    CalculatorData *calc_data = (CalculatorData *)data;

    // 계산기 상태 초기화
    calc_data->result = 0.0;
    calc_data->operator = '\0';

    // 결과 엔트리 초기화
    gtk_entry_set_text(GTK_ENTRY(calc_data->entry), "");
}

// 메인 함수
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 윈도우 생성
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "간단한 계산기");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 그리드 생성
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // 결과를 표시하는 엔트리 생성
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1.0);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    // 숫자 및 연산자 버튼 생성
    const char *button_labels[] = {"7", "8", "9", "/",
                                    "4", "5", "6", "*",
                                    "1", "2", "3", "-",
                                    "0", ".", "=", "+",
                                    "clear"};

    CalculatorData calc_data;
    calc_data.entry = entry;
    calc_data.result = 0.0;
    calc_data.operator = '\0';

    for (int i = 0; i < 17; ++i) {
        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(
            i == 3 ? operator_button_clicked :
            i == 7 ? operator_button_clicked :
            i == 11 ? operator_button_clicked :
            i == 14 ? equal_button_clicked :
            i == 15 ? operator_button_clicked :
            i == 16 ? clear_button_clicked:
            number_button_clicked), &calc_data);

        gtk_grid_attach(GTK_GRID(grid), button, i % 4, 1 + i / 4, 1, 1);
    }

    // 모든 위젯을 표시
    gtk_widget_show_all(window);

    // 메인 루프 시작
    gtk_main();

    return 0;
}
