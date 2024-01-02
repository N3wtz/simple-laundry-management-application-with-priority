#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct untuk menyimpan data pesanan
typedef struct {
    char nama[50];
    char noHP[15];
    float berat;
    int prioritas;
    float harga;
} Pesanan;

// Struct untuk node dalam tree pelanggan
typedef struct treeNode {
    Pesanan data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

// Struct untuk stack
typedef struct {
    Pesanan data[100];
    int top;
} Stack;

// Struct untuk queue
typedef struct {
    Pesanan data[100];
    int front;
    int rear;
} Queue;

// Fungsi untuk membuat node baru dalam tree pelanggan
TreeNode* createNode(Pesanan data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->data.nama, data.nama);
    strcpy(newNode->data.noHP, data.noHP);
    newNode->data.berat = data.berat;
    newNode->data.prioritas = data.prioritas;
    newNode->data.harga = data.harga;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fungsi untuk menambahkan node ke dalam tree pelanggan
TreeNode* insertNode(TreeNode* root, Pesanan data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data.prioritas < root->data.prioritas) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
        return root;
    }
}

// Fungsi untuk menampilkan data pesanan dari tree (in-order traversal terbalik)
void displayTreeReverse(TreeNode* root) {
    if (root != NULL) {
        displayTreeReverse(root->right);
        printf("Nama: %s\n", root->data.nama);
        printf("No HP: %s\n", root->data.noHP);
        printf("Berat: %.2f kg\n", root->data.berat);
        printf("Tingkat Prioritas: %d\n", root->data.prioritas);
        printf("Harga: %.2f\n\n", root->data.harga);
        displayTreeReverse(root->left);
    }
}

// Fungsi untuk menampilkan list jadwal pesanan berdasarkan prioritas
void displayPrioritasSchedule(TreeNode* root) {
    printf("=== List Jadwal Pesanan Berdasarkan Prioritas ===\n");
    displayTreeReverse(root);
}


// Fungsi untuk membuat stack baru
Stack createStack() {
    Stack stack;
    stack.top = -1;
    return stack;
}

// Fungsi untuk memeriksa apakah stack kosong
int isStackEmpty(Stack stack) {
    return stack.top == -1;
}

// Fungsi untuk memeriksa apakah stack penuh
int isStackFull(Stack stack) {
    return stack.top == 99;
}

// Fungsi untuk menambahkan pesanan ke dalam stack
void push(Stack* stack, Pesanan data) {
    if (isStackFull(*stack)) {
        printf("Stack penuh!\n");
    } else {
        stack->data[++stack->top] = data;
    }
}

// Fungsi untuk menghapus pesanan dari stack
Pesanan pop(Stack* stack) {
    if (isStackEmpty(*stack)) {
        printf("Stack kosong!\n");
        Pesanan emptyPesanan;
        emptyPesanan.berat = -1;
        return emptyPesanan;
    } else {
        return stack->data[stack->top--];
    }
}

// Fungsi untuk membuat queue baru
Queue createQueue() {
    Queue queue;
    queue.front = -1;
    queue.rear = -1;
    return queue;
}

// Fungsi untuk memeriksa apakah queue kosong
int isQueueEmpty(Queue queue) {
    return queue.front == -1;
}

// Fungsi untuk memeriksa apakah queue penuh
int isQueueFull(Queue queue) {
    return (queue.rear + 1) % 100 == queue.front;
}

// Fungsi untuk menambahkan pesanan ke dalam queue
void enqueue(Queue* queue, Pesanan data) {
    if (isQueueFull(*queue)) {
        printf("Queue penuh!\n");
    } else {
        if (isQueueEmpty(*queue)) {
            queue->front = 0;
        }
        queue->rear = (queue->rear + 1) % 100;
        queue->data[queue->rear] = data;
    }
}

// Fungsi untuk menghapus pesanan dari queue
Pesanan dequeue(Queue* queue) {
    if (isQueueEmpty(*queue)) {
        printf("Queue kosong!\n");
        Pesanan emptyPesanan;
        emptyPesanan.berat = -1;
        return emptyPesanan;
    } else {
        Pesanan data = queue->data[queue->front];
        if (queue->front == queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        } else {
            queue->front = (queue->front + 1) % 100;
        }
        return data;
    }
}

// Fungsi untuk mengurutkan pesanan berdasarkan harga (menggunakan bubble sort)
void sortPesananByHarga(Pesanan pesanan[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pesanan[j].harga < pesanan[j + 1].harga) {
                Pesanan temp = pesanan[j];
                pesanan[j] = pesanan[j + 1];
                pesanan[j + 1] = temp;
            }
        }
    }
}

// Fungsi untuk mencari letak baju dari pelanggan di dalam stack
void searchInStack(Stack stack[], int numStacks, char nama[]) {
    int i, j;
    for (i = 0; i < numStacks; i++) {
        for (j = 0; j <= stack[i].top; j++) {
            if (strcmp(stack[i].data[j].nama, nama) == 0) {
                printf("Baju atas nama %s terletak pada Rak %c di Tumpukan %d\n", nama, 'A' + i, j + 1);
                // Menghapus pesanan dari stack
                int k;
                for (k = j; k < stack[i].top; k++) {
                    stack[i].data[k] = stack[i].data[k + 1];
                }
                stack[i].top--;
                return;
            }
        }
    }
    printf("Baju atas nama %s tidak ditemukan\n", nama);
}

int main() {
    TreeNode* pelangganTree = NULL;
    Stack stack[3];
    stack[0] = createStack();
    stack[1] = createStack();
    stack[2] = createStack();

    Queue queue = createQueue();

    int choice;
    do {
        printf("=== APLIKASI MANAJEMEN BISNIS LAUNDRY ===\n");
        printf("1. Tambah Pesanan\n");
        printf("2. List Jadwal Pesanan Berdasarkan Prioritas\n");
        printf("3. List Jadwal Pesanan Berdasarkan Harga\n");
        printf("4. Pesanan Selesai\n");
        printf("5. Letak Baju\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Pesanan newPesanan;
                printf("Nama Pelanggan: ");
                scanf(" %[^\n]", newPesanan.nama);
                printf("No HP Pelanggan: ");
                scanf(" %[^\n]", newPesanan.noHP);
                printf("Berat Pesanan (kg): ");
                scanf("%f", &newPesanan.berat);
                printf("Tingkat Prioritas (1 = Normal, 2 = VIP, 3 = VVIP): ");
                scanf("%d", &newPesanan.prioritas);

                if (newPesanan.prioritas == 1) {
                    newPesanan.harga = newPesanan.berat * 5000;
                } else if (newPesanan.prioritas == 2) {
                    newPesanan.harga = newPesanan.berat * 6000;
                } else if (newPesanan.prioritas == 3) {
                    newPesanan.harga = newPesanan.berat * 7000;
                }

                pelangganTree = insertNode(pelangganTree, newPesanan);
                enqueue(&queue, newPesanan);
                printf("Pesanan berhasil ditambahkan!\n");
                break;
            }
            case 2: {
                displayPrioritasSchedule(pelangganTree);
                break;
            }

            case 3: {
                int i = 0;
                Pesanan pesananArr[100];
                Queue tempQueue = queue;
                while (!isQueueEmpty(tempQueue)) {
                    pesananArr[i++] = dequeue(&tempQueue);
                }
                sortPesananByHarga(pesananArr, i);

                printf("=== List Jadwal Pesanan Berdasarkan Harga ===\n");
                int j;
                for (j = 0; j < i; j++) {
                    printf("Nama: %s\n", pesananArr[j].nama);
                    printf("No HP: %s\n", pesananArr[j].noHP);
                    printf("Berat: %.2f kg\n", pesananArr[j].berat);
                    printf("Tingkat Prioritas: %d\n", pesananArr[j].prioritas);
                    printf("Harga: %.2f\n\n", pesananArr[j].harga);
                }
                break;
            }
            case 4: {
                Pesanan pesananSelesai = dequeue(&queue);
                if (pesananSelesai.berat != -1) {
                    // Pesanan selesai, masukkan ke dalam stack
                    int i;
                    for (i = 0; i < 3; i++) {
                        if (stack[i].top < 4) {
                            push(&stack[i], pesananSelesai);
                            printf("Pesanan atas nama %s sudah selesai dan terletak pada Rak %c di Tumpukan %d\n", pesananSelesai.nama, 'A' + i, stack[i].top + 1);
                            break;
                        }
                    }
                } else {
                    printf("Tidak ada pesanan yang tersedia.\n");
                }
                break;
            }
            case 5: {
                char nama[50];
                printf("Masukkan Nama Pelanggan: ");
                scanf(" %[^\n]", nama);
                searchInStack(stack, 3, nama);
                break;
            }
            case 0: {
                printf("Terima kasih! Sampai jumpa lagi.\n");
                break;
            }
            default: {
                printf("Pilihan tidak valid.\n");
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
