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

void return_book(Buku *books, int book_count, Peminjaman *loans, int loan_count) {
    int id_buku;
    printf("ID Buku: ");
    scanf("%d", &id_buku);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char today[11];
    strftime(today, sizeof(today), "%d-%d--%d", tm);
    for (int i = 0; i < loan_count; i++) {
        if (loans[i].id_buku == id_buku && strcmp(loans[i].tanggal_kembali, "None") == 0) {
            strcpy(loans[i].tanggal_kembali, today);
            // Hitung denda (sederhana: asumsikan hari penuh)
            struct tm pinjam_tm = {0};
            sscanf(loans[i].tanggal_pinjam, "%d-%d-%d", &pinjam_tm. tm_year, &pinjam_tm. tm_mon, &pinjam_tm. tm_mday);
            time_t pinjam_time = mktime(&pinjam_tm);
            int days_diff = (t - pinjam_time) / (60 * 60 * 24);
            int days_late = days_diff - MAX_LOAN_DAYS;
            loans[i].denda = (days_late > 0) ? days_late * FINE_PER_DAY : 0;
            // Update status buku
            for (int j = 0; j < book_count; j++) {
                if (books[j].id == id_buku) {
                    strcpy(books[j].status, "Tersedia");
                }
            }
            save_books(books, book_count);
            save_loans(loans, loan_count);
            printf("Buku dikembalikan. Denda: Rp %.0f\n", loans[i].denda);
            return;
        }
    }
    printf("Peminjaman tidak ditemukan.\n");
}
