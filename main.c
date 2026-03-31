#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const gchar* tasks[] = {
    "夜间探索任务：一万步 禁止熟路 拍新奇的东西 探未知小店",
    "游戏探索任务：一个steam新游戏,一周目完成或者玩到一次体验足够",
    "24小时内容创作挑战任务：流程是头脑风暴 选择idea 写脚本 拍摄 剪辑 发布",
    "一日绘画任务：跟上一节绘画课程",
    "一天书籍任务：看并整理一本桌面上的书的下一章",
    "一日运动任务：八段锦 * 5",
    "七日技能叠加任务：每天一小时学习技能 例如视频剪辑 演讲训练 记忆技巧 内容创作 或其他新技能 并记录全过程",
    "独处体验日任务：独自看电影 独自泡咖啡馆 独自下馆子 独自逛博物馆 开车去附近陌生的小镇 步行漫游 骑行 不能带耳机 不碰手机",
    "一日日语任务：一节日语课程学习",
    "一日计算机任务：一个计算机概念理解 一个数据结构算法的学习-代码随想录"
};

const gchar* cat_ascii = "   /\\_/\\  \n  ( o.o ) \n   > ^ <  \n 像素小猫为你加油！";

// 弹出提示框函数
void show_msg(GtkWindow *parent, const char *msg) {
    GtkWidget *dialog = gtk_message_dialog_new(parent, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", msg);
    gtk_window_set_title(GTK_WINDOW(dialog), "提示喵");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_button_clicked(GtkWidget *widget, gpointer data) {
    GtkLabel *result_label = GTK_LABEL(data);
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);

    // 1. 获取日期
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date_str[32];
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", tm_info);

    // 2. 确定路径
    char filepath[512];
    char cwd[256];
    getcwd(cwd, sizeof(cwd)); // 获取当前程序运行的绝对路径
    snprintf(filepath, sizeof(filepath), "Daily/%s.md", date_str);

    g_print("------------------------------------------\n");
    g_print("当前运行目录: %s\n", cwd);

    // 3. 检查文件是否存在
    if (g_file_test(filepath, G_FILE_TEST_EXISTS)) {
        g_print("⚠️ 发现已有文件: %s，拦截生成！\n", filepath);
        show_msg(GTK_WINDOW(toplevel), "请完成今天任务数量已超标，明天再来喵~");
        return; 
    }

    // 4. 生成任务
    int idx = rand() % 10;
    gtk_label_set_text(result_label, tasks[idx]);

    // 5. 确保文件夹存在 (必须在 fopen 之前)
    if (!g_file_test("Daily", G_FILE_TEST_IS_DIR)) {
        if (g_mkdir_with_parents("Daily", 0777) == 0) {
            g_print("📁 成功创建了 Daily 文件夹\n");
        } else {
            g_print("❌ 无法创建 Daily 文件夹，请检查权限！\n");
        }
    }

    // 6. 写入文件
    FILE *file = fopen(filepath, "w");
    if (file) {
        fprintf(file, "今日任务内容：%s\n", tasks[idx]);
        fprintf(file, "完成时间：[待填写]\n");
        fprintf(file, "完成感悟：[待填写]\n");
        fclose(file);
        g_print("✅ 成功生成文档: %s\n", filepath);
        show_msg(GTK_WINDOW(toplevel), "今日任务已送达，已保存到 Daily 文件夹喵！");
    } else {
        g_print("❌ 写入文件失败！路径: %s\n", filepath);
        show_msg(GTK_WINDOW(toplevel), "写入文件失败，请看终端报错信息。");
    }
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window, *vbox, *title_label, *cat_label, *result_label, *button;
    srand(time(NULL));

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "支线任务生成器 V3"); // 注意这个标题
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    title_label = gtk_label_new("★ 随机支线任务生成器 ★");
    gtk_widget_set_name(title_label, "title_style");
    gtk_box_pack_start(GTK_BOX(vbox), title_label, FALSE, FALSE, 0);

    cat_label = gtk_label_new(cat_ascii);
    gtk_widget_set_name(cat_label, "cat_style");
    gtk_box_pack_start(GTK_BOX(vbox), cat_label, FALSE, FALSE, 0);

    result_label = gtk_label_new("准备好接受今日挑战了吗？");
    gtk_widget_set_name(result_label, "result_style");
    gtk_label_set_line_wrap(GTK_LABEL(result_label), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), result_label, FALSE, FALSE, 10);

    button = gtk_button_new_with_label("✨ 确 认 生 成 ✨");
    gtk_widget_set_name(button, "btn_style");
    gtk_widget_set_size_request(button, 180, 50);
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), result_label);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    GtkCssProvider *cp = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cp, 
        "#title_style { font-size: 28px; color: #FF69B4; font-weight: bold; }"
        "#cat_style { font-family: monospace; color: #666; }"
        "#result_style { font-size: 16px; color: #333; padding: 10px; }"
        "#btn_style { background: #FFB6C1; color: white; border-radius: 10px; font-weight: bold; }", -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cp), 800);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.task.v3", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
