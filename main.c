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

    if (fgets(buf, size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
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
    /*
     * 第 6 章 字符数组 + 第 8 章 指针
     * 要求：
     *   1. 读入要查找的姓名
     *   2. 用 strcmp 逐条比较
     *   3. 找到就打印完整信息；找不到提示"没有找到"
     *   4. 注意：比较前要把 fgets 读到的换行去掉，否则永远匹配不上
     */
    printf("[未实现] search_contact\n");
}

void update_contact(void)
{
    /*
     * 第 9 章 结构体
     * 要求：
     *   1. 先按姓名查找到目标记录
     *   2. 重新输入电话和地址（姓名保持不变）
     *   3. 提示修改成功
     */
    printf("[未实现] update_contact\n");
}

void delete_contact(void)
{
    /*
     * 第 6 章 数组元素移动 —— 本项目的核心算法
     * 要求：
     *   1. 按姓名找到下标 i
     *   2. 把 i 之后的元素全部往前搬一位：contacts[j] = contacts[j + 1]
     *   3. count--，并提示删除成功
     *   4. 找不到时提示"没有找到"
     */
    printf("[未实现] delete_contact\n");
}

void save_contacts(void)
{
    /*
     * 第 10 章 文件
     * 要求：
     *   1. fopen(DATA_FILE, "w")，返回 NULL 说明打开失败，必须判断
     *   2. 每行写一条记录，例如 name|phone|addr
     *   3. fclose
     * 注意：字段里如果可能有 '|'，要么换分隔符，要么读的时候特殊处理
     */
    printf("[未实现] save_contacts\n");
}

void load_contacts(void)
{
    /*
     * 第 10 章 文件
     * 要求：
     *   1. 程序启动时调用；文件不存在（fopen 返回 NULL）时直接返回，不要崩溃
     *   2. 逐行读到 count 上限为止
     *   3. 每行按 '|' 拆成三个字段，存进 contacts[count]，然后 count++
     *   4. 读到文件末尾（EOF）就停止
     */
    printf("[未实现] load_contacts\n");
}
