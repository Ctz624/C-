#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

typedef struct {
    char type[10];
    char description[100];
    float amount;
} Record;

Record records[MAX_RECORDS];
int record_count = 0;

void add_record() {
    if (record_count >= MAX_RECORDS) {
        printf("記錄已滿，無法新增！\n");
        return;
    }

    Record r;
    printf("請輸入類型 (income/expense): ");
    scanf("%s", r.type);
    printf("請輸入描述: ");
    getchar();
    fgets(r.description, sizeof(r.description), stdin);
    r.description[strcspn(r.description, "\n")] = 0;
    printf("請輸入金額: ");
    scanf("%f", &r.amount);

    records[record_count++] = r;
    printf("已新增一筆紀錄。\n");
}

void view_records() {
    printf("\n目前所有紀錄：\n");
    for (int i = 0; i < record_count; i++) {
        printf("%d. [%s] %s - %.2f\n", i + 1, records[i].type, records[i].description, records[i].amount);
    }
}

void calculate_summary() {
    float total_income = 0, total_expense = 0;
    for (int i = 0; i < record_count; i++) {
        if (strcmp(records[i].type, "income") == 0)
            total_income += records[i].amount;
        else if (strcmp(records[i].type, "expense") == 0)
            total_expense += records[i].amount;
    }

    printf("\n總收入：%.2f\n", total_income);
    printf("總支出：%.2f\n", total_expense);
    printf("淨餘額：%.2f\n", total_income - total_expense);
}

void save_to_file() {
    FILE *fp = fopen("finance.txt", "w");
    if (!fp) {
        printf("無法開啟檔案進行寫入！\n");
        return;
    }

    for (int i = 0; i < record_count; i++) {
        fprintf(fp, "%s|%s|%.2f\n", records[i].type, records[i].description, records[i].amount);
    }

    fclose(fp);
    printf("資料已儲存到 finance.txt。\n");
}

void load_from_file() {
    FILE *fp = fopen("finance.txt", "r");
    if (!fp) {
        printf("尚無記錄檔案可載入。\n");
        return;
    }

    record_count = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%f\n", records[record_count].type,
                  records[record_count].description, &records[record_count].amount) == 3) {
        record_count++;
    }

    fclose(fp);
    printf("已載入 %d 筆紀錄。\n", record_count);
}

int main() {
    int choice;

    load_from_file();

    do {
        printf("\n========== 個人帳本系統 ==========\n");
        printf("1. 新增收支紀錄\n");
        printf("2. 檢視所有紀錄\n");
        printf("3. 計算收支總結\n");
        printf("4. 儲存資料到檔案\n");
        printf("0. 離開系統\n");
        printf("請選擇：");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_record(); break;
            case 2: view_records(); break;
            case 3: calculate_summary(); break;
            case 4: save_to_file(); break;
            case 0: printf("再見！\n"); break;
            default: printf("無效的選項！\n");
        }
    } while (choice != 0);

    return 0;
}
