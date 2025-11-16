#include "perpustakaan.h"

/* login pustakawan */
void loginPustakawan() {
    char user[50], pass[50];
    do {
        printf("=== LOGIN PUSTAKAWAN ===\n");
        printf("Username: ");
        scanf("%49s", user);
        printf("Password: ");
        scanf("%49s", pass);
        if (strcmp(user, "admin") == 0 && strcmp(pass, "klp1solid") == 0) {
            printf("\nLogin berhasil!\n\n");
            break;
        } else {
            printf("Login gagal! Coba lagi.\n\n");
        }
    } while (1);
}

/* menu utama */
void tampilkanMenuUtama() {
    int pilih;
    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Hapus Buku\n");
        printf("3. Edit Buku\n");
        printf("4. Lihat Daftar Buku\n");
        printf("5. Cari Buku\n");
        printf("6. Tambah Anggota\n");
        printf("7. Peminjaman Buku\n");
        printf("8. Pengembalian Buku\n");
        printf("9. Ranking Buku Populer\n");
        printf("10. Ubah durasi peminjaman maksimal\n");
        printf("11. Riwayat peminjaman anggota\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");

        if (scanf("%d", &pilih) != 1) { clearBuffer(); pilih = -1; }

        switch(pilih) {
            case 1: tambahBuku(); break;
            case 2: hapusBuku(); break;
            case 3: editBuku(); break;
            case 4: tampilkanDaftarBuku(); break;
            case 5: cariBuku(); break;
            case 6: tambahAnggota(); break;
            case 7: pinjamBuku(); break;
            case 8: kembalikanBuku(); break;
            case 9: rankingBuku(); break;
            case 10: ubahDurasiPeminjaman(); break;
            case 11: tampilkanRiwayatAnggota(); break;
            case 0: printf("Keluar dari sistem...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilih != 0);
}

int main() {
    loginPustakawan();
    tampilkanMenuUtama();
    return 0;
}
