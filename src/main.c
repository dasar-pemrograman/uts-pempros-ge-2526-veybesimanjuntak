//12S25024 - VEYBE YOULANDA K M SIMANJUNTAK
//# M01 Warehouse Incident System

// Task 01: Register Incoming Goods

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

struct Item {
    char id[20];
    char name[50];
    int quantity;
    double price;
};

struct Item items[MAX];
int itemCount = 0;

int findItem(char *id) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].id, id) == 0) return i;
    }
    return -1;
}

int main() {
    char input[200];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "---") == 0) break;

        char *cmd = strtok(input, "#");

        if (strcmp(cmd, "receive") == 0) {
            char *id = strtok(NULL, "#");
            char *name = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");
            char *priceStr = strtok(NULL, "#");

            if (!id || !name || !qtyStr || !priceStr) continue;

            int quantity = atoi(qtyStr);
            double price = atof(priceStr);

            if (quantity <= 0) continue;
            if (findItem(id) != -1) continue;

            strcpy(items[itemCount].id, id);
            strcpy(items[itemCount].name, name);
            items[itemCount].quantity = quantity;
            items[itemCount].price = price;

            itemCount++;
        }

        else if (strcmp(cmd, "report") == 0) {
            for (int i = 0; i < itemCount; i++) {
                printf("%s|%s|%d|%.1f\n",
                       items[i].id,
                       items[i].name,
                       items[i].quantity,
                       items[i].price);
            }
        }
    }

    return 0;
}

// Task 02: Handling Shipment Errors
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

struct Item {
    char id[20];
    char name[50];
    int quantity;
    double price;
};

struct Item items[MAX];
int itemCount = 0;

int findItem(char *id) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].id, id) == 0) return i;
    }
    return -1;
}

int main() {
    char input[200];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "---") == 0) break;

        char *cmd = strtok(input, "#");

        if (strcmp(cmd, "receive") == 0) {
            char *id = strtok(NULL, "#");
            char *name = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");
            char *priceStr = strtok(NULL, "#");

            if (!id || !name || !qtyStr || !priceStr) continue;

            int quantity = atoi(qtyStr);
            double price = atof(priceStr);

            if (quantity <= 0) continue;
            if (findItem(id) != -1) continue;

            strcpy(items[itemCount].id, id);
            strcpy(items[itemCount].name, name);
            items[itemCount].quantity = quantity;
            items[itemCount].price = price;

            itemCount++;
        }

        else if (strcmp(cmd, "ship") == 0) {
            char *id = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");

            if (!id || !qtyStr) continue;

            int quantity = atoi(qtyStr);
            if (quantity <= 0) continue;

            int idx = findItem(id);
            if (idx == -1) continue;

            if (items[idx].quantity < quantity) continue;

            items[idx].quantity -=;
        }

        else if (strcmp(cmd, "restock") == 0) {
            char *id = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");

            if (!id || !qtyStr) continue;

            int quantity = atoi(qtyStr);
            if (quantity <= 0) continue;

            int idx = findItem(id);
            if (idx == -1) continue;

            items[idx].quantity += quantity;
        }

        else if (strcmp(cmd, "report") == 0) {
            for (int i = 0; i < itemCount; i++) {
                printf("%s|%s|%d|%.1f\n",
                       items[i].id,
                       items[i].name,
                       items[i].quantity,
                       items[i].price);
            }
        }
    }

    return 0;
}

// Task 03: Audit Log System

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

struct Item {
    char id[20];
    char name[50];
    int quantity;
    double price;
};

struct Log {
    int log_id;
    char item_id[20];
    char type[10];
    int quantity;
};

struct Item items[MAX];
struct Log logs[MAX];

int itemCount = 0;
int logCount = 0;
int globalLogID = 1;

int findItem(char *id) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].id, id) == 0) return i;
    }
    return -1;
}

void addLog(char *id, char *type, int quantity) {
    logs[logCount].log_id = globalLogID++;
    strcpy(logs[logCount].item_id, id);
    strcpy(logs[logCount].type, type);
    logs[logCount].quantity = quantity;
    logCount++;
}

int main() {
    char input[200];

    while (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "---") == 0) break;

        char *cmd = strtok(input, "#");

        if (strcmp(cmd, "receive") == 0) {
            char *id = strtok(NULL, "#");
            char *name = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");
            char *priceStr = strtok(NULL, "#");

            if (!id || !name || !qtyStr || !priceStr) continue;

            int quantity = atoi(qtyStr);
            double price = atof(priceStr);

            if (quantity <= 0) continue;
            if (findItem(id) != -1) continue;

            strcpy(items[itemCount].id, id);
            strcpy(items[itemCount].name, name);
            items[itemCount].quantity = quantity;
            items[itemCount].price = price;

            itemCount++;

            addLog(id, "receive", quantity);
        }

        else if (strcmp(cmd, "ship") == 0) {
            char *id = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");

            if (!id || !qtyStr) continue;

            int quantity = atoi(qtyStr);
            if (quantity <= 0) continue;

            int idx = findItem(id);
            if (idx == -1) continue;
            if (items[idx].quantity < quantity) continue;

            items[idx].quantity -= quantity;

            addLog(id, "ship", quantity);
        }

        else if (strcmp(cmd, "restock") == 0) {
            char *id = strtok(NULL, "#");
            char *qtyStr = strtok(NULL, "#");

            if (!id || !qtyStr) continue;

            int quantity = atoi(qtyStr);
            if (quantity <= 0) continue;

            int idx = findItem(id);
            if (idx == -1) continue;

            items[idx].quantity += quantity;

            addLog(id, "restock", quantity);
        }

        else if (strcmp(cmd, "report") == 0) {
            for (int i = 0; i < itemCount; i++) {
                printf("%s|%s|%d|%.1f\n",
                       items[i].id,
                       items[i].name,
                       items[i].quantity,
                       items[i].price);
            }
        }

        else if (strcmp(cmd, "audit") == 0) {
            char *id = strtok(NULL, "#");
            if (!id) continue;

            int idx = findItem(id);
            if (idx == -1) continue;

            printf("%s|%s|%d|%.1f\n",
                   items[idx].id,
                   items[idx].name,
                   items[idx].quantity,
                   items[idx].price);

            for (int i = 0; i < logCount; i++) {
                if (strcmp(logs[i].item_id, id) == 0) {
                    printf("%d|%s|%d\n",
                           logs[i].log_id,
                           logs[i].type,
                           logs[i].quantity);
                }
            }
        }
    }

    return 0;
}