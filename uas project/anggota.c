#include "perpustakaan.h"

/* tambah anggota ke file members.txt */
void simpanAnggota_tambah(Anggota anggota) {
    FILE *fp = fopen("data/members.txt", "a");
    if (!fp) { printf("Gagal membuka file members.txt\n"); return; }
    fprintf(fp, "%d|%s|%s\n", anggota.id, anggota.nama, anggota.alamat);
    fclose(fp);
}

/* Baca semua anggota ke array */
void bacaAnggotaDariFile(Anggota daftarAnggota[], int *jumlah) {
    FILE *fp = fopen("data/members.txt", "r");
    *jumlah = 0;
    if (!fp) return;
    Anggota a;
    while (fscanf(fp, " %d|%99[^|]|%99[^\n]", &a.id, a.nama, a.alamat) == 3) {
        a.nama[MAX_STR-1] = '\0';
        a.alamat[MAX_STR-1] = '\0';
        daftarAnggota[*jumlah] = a;
        (*jumlah)++;
        if (*jumlah >= MAX_MEMBERS) break;
        int c; while ((c = fgetc(fp)) != EOF && c != '\n');
    }
    fclose(fp);
}

/* Tambah anggota baru */
void tambahAnggota() {
    Anggota a;
    printf("\n=== TAMBAH ANGGOTA ===\n");
    printf("ID Anggota: ");
    if (scanf("%d", &a.id) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }
    clearBuffer();
    printf("Nama: "); fgets(a.nama, MAX_STR, stdin); a.nama[strcspn(a.nama, "\n")] = 0;
    printf("Alamat: "); fgets(a.alamat, MAX_STR, stdin); a.alamat[strcspn(a.alamat, "\n")] = 0;

    Anggota arr[MAX_MEMBERS]; int n=0; bacaAnggotaDariFile(arr, &n);
    for (int i=0;i<n;i++) if (arr[i].id == a.id) { printf("ID anggota sudah ada.\n"); return; }

    simpanAnggota_tambah(a);
    printf("Anggota berhasil ditambahkan!\n");
}

/* Tampilkan anggota */
void tampilkanAnggota() {
    FILE *fp = fopen("data/members.txt", "r");
    if (!fp) { printf("Belum ada data anggota.\n"); return; }
    Anggota a;
    printf("\n=== DAFTAR ANGGOTA ===\n");
    printf("ID | Nama | Alamat\n");
    printf("--------------------------\n");
    while (fscanf(fp, " %d|%99[^|]|%99[^\n]", &a.id, a.nama, a.alamat) == 3) {
        a.nama[MAX_STR-1] = '\0';
        a.alamat[MAX_STR-1] = '\0';
        printf("%d | %s | %s\n", a.id, a.nama, a.alamat);
        int c; while ((c = fgetc(fp)) != EOF && c != '\n');
    }
    fclose(fp);
}
