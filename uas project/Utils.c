#include "perpustakaan.h"

void load_books(Buku **books, int *count) {
    FILE *file = fopen("data/books.txt", "r");
    if (!file) {
        printf("File books.txt tidak ditemukan. Membuat baru.\n");
        return;
    }
    char line[256];
    *count = 0;
    while (fgets(line, sizeof(line), file)) {
        *books = realloc(*books, (*count + 1) * sizeof(Buku));
        sscanf(line, "%d,%99[^,],%99[^,],%49[^,],%19[^\n]",
               &(*books)[*count].id, (*books)[*count].judul,
               (*books)[*count].penulis, (*books)[*count].kategori, (*books)[*count].status);
        (*count)++;
    }
    fclose(file);
}

void save_books(Buku *books, int count) {
    FILE *file = fopen("data/books.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n", books[i].id, books[i].judul, books[i].penulis, books[i].kategori, books[i].status);
    }
    fclose(file);
}

void load_members(Anggota **members, int *count) {
    FILE *file = fopen("data/members.txt", "r");
    if (!file) {
        printf("File members.txt tidak ditemukan. Membuat baru.\n");
        return;
    }
    char line[256];
    *count = 0;
    while (fgets(line, sizeof(line), file)) {
        *members = realloc(*members, (*count + 1) * sizeof(Anggota));
        sscanf(line, "%d,%99[^,],%99[^\n]",
               &(*members)[*count].id, (*members)[*count].nama, (*members)[*count].email);
        (*count)++;
    }
    fclose(file);
}

void save_members(Anggota *members, int count) {
    FILE *file = fopen("data/members.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s\n", members[i].id, members[i].nama, members[i].email);
    }
    fclose(file);
}

void load_loans(Peminjaman **loans, int *count) {
    FILE *file = fopen("data/loans.txt", "r");
    if (!file) {
        printf("File loans.txt tidak ditemukan. Membuat baru.\n");
        return;
    }
    char line[256];
    *count = 0;
    while (fgets(line, sizeof(line), file)) {
        *loans = realloc(*loans, (*count + 1) * sizeof(Peminjaman));
        sscanf(line, "%d,%d,%10[^,],%10[^,],%f",
               &(*loans)[*count].id_buku, &(*loans)[*count].id_member,
               (*loans)[*count].tanggal_pinjam, (*loans)[*count].tanggal_kembali, &(*loans)[*count].denda);
        (*count)++;
    }
    fclose(file);
}

void save_loans(Peminjaman *loans, int count) {
    FILE *file = fopen("data/loans.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%d,%s,%s,%.0f\n", loans[i].id_buku, loans[i].id_member,
                loans[i].tanggal_pinjam, loans[i].tanggal_kembali, loans[i].denda);
    }
    fclose(file);
}

int login() {
    char username[50], password[50];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    FILE *file = fopen("data/librarians.txt", "r");
    if (!file) {
        printf("File librarians.txt tidak ditemukan.\n");
        return 0;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char u[50], p[50];
        sscanf(line, "%49[^,],%49[^\n]", u, p);
        if (strcmp(username, u) == 0 && strcmp(password, p) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
