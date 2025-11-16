#include "perpustakaan.h"

int main() {
    if (!login()) {
        printf("Login gagal. Program berhenti.\n");
        return 1;
    }

    Buku *books = NULL;
    Anggota *members = NULL;
    Peminjaman *loans = NULL;
    int book_count = 0, member_count = 0, loan_count = 0;

    load_books(&books, &book_count);
    load_members(&members, &member_count);
    load_loans(&loans, &loan_count);

