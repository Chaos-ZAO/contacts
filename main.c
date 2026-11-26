/*
 * 通讯录管理系统
 * 知识点对应《C程序设计》第五版：
 *   第 3 章 顺序程序设计（printf / scanf）
 *   第 4 章 选择结构（switch 菜单）
 *   第 5 章 循环结构
 *   第 6 章 数组与字符数组
 *   第 7 章 函数
 *   第 8 章 指针（数组作参数）
 *   第 9 章 结构体
 *   第 10 章 文件
 *
 * 编译：gcc main.c -o contacts
 * 运行：.\contacts
 */

#include <stdio.h>
#include <string.h>
#include <windows.h>   /* SetConsoleOutputCP / SetConsoleCP */

#define MAX_CONTACTS 100
#define NAME_LEN     21
#define PHONE_LEN    21
#define ADDR_LEN     41
#define DATA_FILE    "contacts.txt"

struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char addr[ADDR_LEN];
};

static struct Contact contacts[MAX_CONTACTS];
static int count = 0;

void show_menu(void);
void add_contact(void);
void list_contacts(void);
void search_contact(void);
void update_contact(void);
void delete_contact(void);
void save_contacts(void);
void load_contacts(void);

int main(void)
{
    int choice;
    int ch;

    /* 让 Windows 控制台用 UTF-8 显示中文，解决乱码 */
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    load_contacts();

    while (1) {
        show_menu();

        if (scanf("%d", &choice) != 1) {
            /* 输入的不是数字：清空这一行，避免无限循环 */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            printf("请输入数字选项。\n");
            continue;
        }

        /* 吃掉选项后面剩下的换行，否则会被后面的 fgets 读到 */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        switch (choice) {
        case 1:
            add_contact();
            break;
        case 2:
            list_contacts();
            break;
        case 3:
            search_contact();
            break;
        case 4:
            update_contact();
            break;
        case 5:
            delete_contact();
            break;
        case 6:
            save_contacts();
            break;
        case 0:
            save_contacts();
            printf("再见。\n");
            return 0;
        default:
            printf("没有这个选项。\n");
        }
    }
}

void show_menu(void)
{
    printf("\n========== 通讯录 ==========\n");
    printf("  1. 添加联系人\n");
    printf("  2. 显示全部\n");
    printf("  3. 查找\n");
    printf("  4. 修改\n");
    printf("  5. 删除\n");
    printf("  6. 保存到文件\n");
    printf("  0. 退出\n");
    printf("----------------------------\n");
    printf("共 %d / %d 条\n", count, MAX_CONTACTS);
    printf("请选择: ");
}

/* 读一行到 buf，并把末尾的换行去掉（fgets 会连换行一起读进来） */
static void read_line(char *buf, int size)
{
    size_t len;
    int ch;

    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        /* 没读到换行 = 输入超出了 buf 容量，剩余字符还在缓冲区里，
           必须清空，否则会被下一个 read_line 当成输入读走 */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
}

/* ================= 下面 7 个函数中，前两个已完成，其余由你自己实现 ================= */

void add_contact(void)
{
    if (count >= MAX_CONTACTS) {
        printf("通讯录已满，不能再添加（上限 %d 条）。\n", MAX_CONTACTS);
        return;
    }

    printf("姓名: ");
    read_line(contacts[count].name, NAME_LEN);
    if (contacts[count].name[0] == '\0') {
        printf("姓名不能为空，已取消添加。\n");
        return;
    }

    printf("电话: ");
    read_line(contacts[count].phone, PHONE_LEN);

    printf("地址: ");
    read_line(contacts[count].addr, ADDR_LEN);

    count++;
    printf("已添加第 %d 条记录。\n", count);
}

void list_contacts(void)
{
    int i;

    if (count == 0) {
        printf("通讯录为空。\n");
        return;
    }

    printf("\n序号 | 姓名 | 电话 | 地址\n");
    for (i = 0; i < count; i++) {
        printf("%d | %s | %s | %s\n",
               i + 1, contacts[i].name, contacts[i].phone, contacts[i].addr);
    }
}

void search_contact(void)
{
    char name[NAME_LEN];
    int i;
    int found = 0;

    if (count == 0) {
        printf("通讯录为空，没什么可查的。\n");
        return;
    }

    printf("要查找的姓名: ");
    read_line(name, NAME_LEN);

    for (i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("找到：\n");
            printf("  姓名: %s\n", contacts[i].name);
            printf("  电话: %s\n", contacts[i].phone);
            printf("  地址: %s\n", contacts[i].addr);
            found = 1;
        }
    }

    if (!found) {
        printf("没有找到名为 \"%s\" 的联系人。\n", name);
    }
}

void update_contact(void)
{
    char name[NAME_LEN];
    int i;
    int idx = -1;

    if (count == 0) {
        printf("通讯录为空，没什么可改的。\n");
        return;
    }

    printf("要修改的姓名: ");
    read_line(name, NAME_LEN);

    for (i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            idx = i;
            break;
        }
    }

    if (idx < 0) {
        printf("没有找到名为 \"%s\" 的联系人。\n", name);
        return;
    }

    printf("修改电话: ");
    read_line(contacts[idx].phone, PHONE_LEN);
    printf("修改地址: ");
    read_line(contacts[idx].addr, ADDR_LEN);
    printf("已修改 %s 的信息。\n", name);
}

void delete_contact(void)
{
    char name[NAME_LEN];
    int i, j;
    int idx = -1;

    if (count == 0) {
        printf("通讯录为空，没什么可删的。\n");
        return;
    }

    printf("要删除的姓名: ");
    read_line(name, NAME_LEN);

    for (i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            idx = i;
            break;
        }
    }

    if (idx < 0) {
        printf("没有找到名为 \"%s\" 的联系人。\n", name);
        return;
    }

    /* 把 idx 后面的元素逐个往前搬一位，结构体可以整体赋值 */
    for (j = idx; j < count - 1; j++) {
        contacts[j] = contacts[j + 1];
    }
    count--;
    printf("已删除 %s，现在共 %d 条。\n", name, count);
}

void save_contacts(void)
{
    FILE *fp;
    int i;

    fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("保存失败：无法打开文件 %s。\n", DATA_FILE);
        return;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s\n",
                contacts[i].name, contacts[i].phone, contacts[i].addr);
    }
    fclose(fp);
    printf("已保存 %d 条记录到 %s。\n", count, DATA_FILE);
}

void load_contacts(void)
{
    FILE *fp;
    char line[200];
    char *p;
    char *phone_start;

    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return;   /* 第一次运行没有文件，直接返回，不要崩溃 */
    }

    while (count < MAX_CONTACTS && fgets(line, sizeof(line), fp) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';   /* fgets 会连换行一起读进来，先去掉 */

        /* 按 '|' 把一行拆成 name、phone、addr 三段 */
        p = strchr(line, '|');
        if (p == NULL) continue;
        *p = '\0';
        strncpy(contacts[count].name, line, NAME_LEN - 1);
        contacts[count].name[NAME_LEN - 1] = '\0';

        phone_start = p + 1;
        p = strchr(phone_start, '|');
        if (p == NULL) continue;
        *p = '\0';
        strncpy(contacts[count].phone, phone_start, PHONE_LEN - 1);
        contacts[count].phone[PHONE_LEN - 1] = '\0';

        strncpy(contacts[count].addr, p + 1, ADDR_LEN - 1);
        contacts[count].addr[ADDR_LEN - 1] = '\0';

        count++;
    }
    fclose(fp);
}
