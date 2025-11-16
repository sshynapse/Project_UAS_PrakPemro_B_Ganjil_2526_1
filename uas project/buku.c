#include "perpustakaan.h"

void add_book(Buku **books, int *count) {
    *books = realloc(*books, (*count + 1) * sizeof(Buku));
    Buku *new_book = &(*books)[*count];
    new_book->id = *count + 1;
    printf("Judul: ");
    fgets(new_book->judul, sizeof(new_book->judul), stdin);
    new_book->judul[strcspn(new_book->judul, "\n")] = 0;
    printf("Penulis: ");
    fgets(new_book->penulis, sizeof(new_book->penulis), stdin);
    new_book->penulis[strcspn(new_book->penulis, "\n")] = 0;
    printf("Kategori: ");
    fgets(new_book->kategori, sizeof(new_book->kategori), stdin);
    new_book->kategori[strcspn(new_book->kategori, "\n")] = 0;
    strcpy(new_book->status, "Tersedia");
    (*count)++;
    save_books(*books, *count);
    printf("Buku ditambahkan.\n");
}

void delete_book(Buku **books, int *count) {
    int id;
    printf("ID Buku: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++) {
        if ((*books)[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                (*books)[j] = (*books)[j + 1];
            }
            (*count)--;
            *books = realloc(*books, *count * sizeof(Buku));
            save_books(*books, *count);
            printf("Buku dihapus.\n");
            return;
        }
    }
    printf("Buku tidak ditemukan.\n");
}

void edit_book(Buku *books, int count) {
    int id;
    printf("ID Buku: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (books[i].id == id) {
            printf("Judul baru: ");
            fgets(books[i].judul, sizeof(books[i].judul), stdin);
            books[i].judul[strcspn(books[i].judul, "\n")] = 0;
            printf("Penulis baru: ");
            fgets(books[i].penulis, sizeof(books[i].penulis), stdin);
            books[i].penulis[strcspn(books[i].penulis, "\n")] = 0;
            printf("Kategori baru: ");
            fgets(books[i].kategori, sizeof(books[i].kategori), stdin);
            books[i].kategori[strcspn(books[i].kategori, "\n")] = 0;
            save_books(books, count);
            printf("Buku diedit.\n");
            return;
        }
    }
    printf("Buku tidak ditemukan.\n");
}

void view_books(Buku *books, int count) {
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Judul: %s, Penulis: %s, Kategori: %s, Status: %s\n",
               books[i].id, books[i].judul, books[i].penulis, books[i].kategori, books[i].status);
    }
}

void categorize_books(Buku *books, int count, const char *kategori) {
    printf("Buku dalam kategori %s:\n", kategori);
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].kategori, kategori) == 0) {
            printf("ID: %d, Judul: %s\n", books[i].id, books[i].judul);
        }
    }
}

void search_books(Buku *books, int count, const char *query, const char *by) {
    printf("Hasil pencarian:\n");
    for (int i = 0; i < count; i++) {
        char *field = (strcmp(by, "judul") == 0) ? books[i].judul :
                      (strcmp(by, "penulis") == 0) ? books[i].penulis : books[i].kategori;
        if (strstr(field, query) != NULL) {
            printf("ID: %d, Judul: %s, Penulis: %s, Kategori: %s\n",
                   books[i].id, books[i].judul, books[i].penulis, books[i].kategori);
        }
    }
}