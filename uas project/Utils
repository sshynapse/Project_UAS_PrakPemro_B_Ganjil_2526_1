#include "perpustakaan.h"

void borrow_book(Buku *books, int book_count, Peminjaman **loans, int *loan_count, Anggota *members, int member_count) {
    int id_buku, id_member;
    printf("ID Buku: ");
    scanf("%d", &id_buku);
    printf("ID Anggota: ");
    scanf("%d", &id_member);
    // Cek apakah anggota ada
    int member_exists = 0;
    for (int i = 0; i < member_count; i++) {
        if (members[i].id == id_member) {
            member_exists = 1;
            break;
        }
    }
    if (!member_exists) {
        printf("Anggota tidak ditemukan.\n");
        return;
    }
    // Cek buku tersedia
    for (int i = 0; i < book_count; i++) {
        if (books[i].id == id_buku && strcmp(books[i].status, "Tersedia") == 0) {
            strcpy(books[i].status, "Dipinjam");
            *loans = realloc(*loans, (*loan_count + 1) * sizeof(Peminjaman));
            Peminjaman *new_loan = &(*loans)[*loan_count];
            new_loan->id_buku = id_buku;
            new_loan->id_member = id_member;
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            strftime(new_loan->tanggal_pinjam, sizeof(new_loan->tanggal_pinjam), "%Y-%m-%d", tm);
            strcpy(new_loan->tanggal_kembali, "None");
            new_loan->denda = 0;
            (*loan_count)++;
            save_books(books, book_count);
            save_loans(*loans, *loan_count);
            printf("Buku dipinjam.\n");
            return;
        }
    }
    printf("Buku tidak tersedia.\n");
}
