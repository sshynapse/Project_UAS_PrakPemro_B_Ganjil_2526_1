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

    int choice;
    while (1) {
        printf("\n=== Menu Perpustakaan ===\n");
        printf("1. Tambah Buku\n2. Hapus Buku\n3. Edit Buku\n4. Lihat Buku\n5. Kategorikan Buku\n6. Cari Buku\n");
        printf("7. Pinjam Buku\n8. Kembali Buku\n9. Daftar Anggota\n10. Riwayat Peminjaman\n11. Ranking Buku\n12. Statistik\n13. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);
        getchar();  // Clear newline

        switch (choice) {
            case 1: add_book(&books, &book_count); break;
            case 2: delete_book(&books, &book_count); break;
            case 3: edit_book(books, book_count); break;
            case 4: view_books(books, book_count); break;
            case 5: {
                char kategori[50];
                printf("Kategori: ");
                fgets(kategori, sizeof(kategori), stdin);
                kategori[strcspn(kategori, "\n")] = 0;
                categorize_books(books, book_count, kategori);
                break;
            }
            case 6: {
                char query[100], by[20];
                printf("Query: ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = 0;
                printf("Berdasarkan (judul/penulis/kategori): ");
                fgets(by, sizeof(by), stdin);
                by[strcspn(by, "\n")] = 0;
                search_books(books, book_count, query, by);
                break;
            }
            case 7: borrow_book(books, book_count, &loans, &loan_count, members, member_count); break;
            case 8: return_book(books, book_count, loans, loan_count); break;
            case 9: view_members(members, member_count); break;
            case 10: {
                int id_member;
                printf("ID Anggota: ");
                scanf("%d", &id_member);
                view_loan_history(loans, loan_count, id_member);
                break;
            }
            case 11: book_ranking(loans, loan_count); break;
            case 12: statistics(book_count, member_count, loan_count); break;
            case 13: {
                free(books);
                free(members);
                free(loans);
                printf("Terima kasih!\n");
                return 0;
            }
            default: printf("Pilihan tidak valid.\n");
        }
    }
    return 0;
}
