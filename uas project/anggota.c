#include "perpustakaan.h"

/* tambah satu buku ke books.txt */
void simpanBuku_tambah(Buku buku) {
    FILE *fp = fopen("data/books.txt", "a");
    if (!fp) { printf("Gagal membuka file books.txt untuk menambahkan.\n"); return; }
    fprintf(fp, "%d|%s|%s|%s|%d|%d\n",
            buku.id, buku.judul, buku.penulis, buku.kategori, buku.tersedia, buku.dipinjamCount);
    fclose(fp);
}

/* Baca semua buku ke array (aman) */
void bacaBukuDariFile(Buku daftarBuku[], int *jumlah) {
    FILE *fp = fopen("data/books.txt", "r");
    *jumlah = 0;
    if (!fp) return;
    Buku b;
    while (fscanf(fp, " %d|%99[^|]|%99[^|]|%99[^|]|%d|%d",
                  &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.dipinjamCount) == 6) {
        b.judul[MAX_STR-1] = '\0'; b.penulis[MAX_STR-1] = '\0'; b.kategori[MAX_STR-1] = '\0';
        daftarBuku[*jumlah] = b;
        (*jumlah)++;
        if (*jumlah >= MAX_BOOKS) break;
        int c; while ((c = fgetc(fp)) != EOF && c != '\n');
    }
    fclose(fp);
}

/* Tulis semua buku ke file */
void tulisSemuaBukuKeFile(Buku daftarBuku[], int jumlah) {
    FILE *fp = fopen("data/books.txt", "w");
    if (!fp) { printf("Gagal menulis file books.txt\n"); return; }
    for (int i = 0; i < jumlah; ++i) {
        Buku *b = &daftarBuku[i];
        fprintf(fp, "%d|%s|%s|%s|%d|%d\n",
                b->id, b->judul, b->penulis, b->kategori, b->tersedia, b->dipinjamCount);
    }
    fclose(fp);
}

/* Tambah buku */
void tambahBuku() {
    Buku buku;
    printf("\n=== TAMBAH BUKU ===\n");
    printf("ID Buku: ");
    if (scanf("%d", &buku.id) != 1) { clearBuffer(); printf("Input ID tidak valid.\n"); return; }
    clearBuffer();
    printf("Judul: "); fgets(buku.judul, MAX_STR, stdin); buku.judul[strcspn(buku.judul, "\n")] = 0;
    printf("Penulis: "); fgets(buku.penulis, MAX_STR, stdin); buku.penulis[strcspn(buku.penulis, "\n")] = 0;
    printf("Kategori (Fiksi/Non-Fiksi/Komik/Majalah/Referensi): ");
    fgets(buku.kategori, MAX_STR, stdin); buku.kategori[strcspn(buku.kategori, "\n")] = 0;
    buku.tersedia = 1; buku.dipinjamCount = 0;

    Buku arr[MAX_BOOKS]; int n=0; bacaBukuDariFile(arr, &n);
    for (int i=0;i<n;i++) if (arr[i].id == buku.id) { printf("ID sudah ada. Gunakan ID lain.\n"); return; }
    simpanBuku_tambah(buku);
    printf("Buku berhasil ditambahkan!\n");
}

/* Tampilkan daftar buku */
void tampilkanDaftarBuku() {
    FILE *fp = fopen("data/books.txt", "r");
    if (!fp) { printf("Belum ada data buku.\n"); return; }
    Buku buku;
    printf("\n=== DAFTAR BUKU ===\n");
    printf("ID | Judul | Penulis | Kategori | Status | Dipinjam\n");
    printf("--------------------------------------------------------\n");
    while (fscanf(fp, " %d|%99[^|]|%99[^|]|%99[^|]|%d|%d",
                  &buku.id, buku.judul, buku.penulis, buku.kategori, &buku.tersedia, &buku.dipinjamCount) == 6) {
        printf("%d | %s | %s | %s | %s | %d\n",
               buku.id, buku.judul, buku.penulis, buku.kategori,
               buku.tersedia ? "Tersedia" : "Dipinjam", buku.dipinjamCount);
        int c; while ((c = fgetc(fp)) != EOF && c != '\n');
    }
    fclose(fp);
}

/* Cari buku (judul/penulis/kategori) */
void cariBuku() {
    char keyword[MAX_STR];
    printf("\nMasukkan kata kunci (judul/penulis/kategori): ");
    scanf(" %[^\n]", keyword);

    FILE *fp = fopen("data/books.txt", "r");
    if (!fp) { printf("Data buku tidak ditemukan.\n"); return; }
    Buku buku; int ditemukan = 0;
    while (fscanf(fp, " %d|%99[^|]|%99[^|]|%99[^|]|%d|%d",
                  &buku.id, buku.judul, buku.penulis, buku.kategori, &buku.tersedia, &buku.dipinjamCount) == 6) {
        if (strcasestr(buku.judul, keyword) || strcasestr(buku.penulis, keyword) || strcasestr(buku.kategori, keyword)) {
            printf("Ditemukan: %d - %s | %s | %s\n", buku.id, buku.judul, buku.penulis, buku.kategori);
            ditemukan = 1;
        }
        int c; while ((c = fgetc(fp)) != EOF && c != '\n');
    }
    if (!ditemukan) printf("Buku tidak ditemukan.\n");
    fclose(fp);
}

/* Hapus buku pakai ID (kalau lagi dipinjam -> tolak) */
void hapusBuku() {
    int id;
    printf("\nMasukkan ID buku yang ingin dihapus: ");
    if (scanf("%d", &id) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }

    Buku arr[MAX_BOOKS]; int n=0; bacaBukuDariFile(arr, &n);
    int idx = -1;
    for (int i=0;i<n;i++) if (arr[i].id == id) { idx = i; break; }
    if (idx == -1) { printf("Buku tidak ditemukan.\n"); return; }
    if (arr[idx].tersedia == 0) { printf("Buku sedang dipinjam. Tidak bisa dihapus.\n"); return; }

    for (int i=idx;i<n-1;i++) arr[i] = arr[i+1];
    n--;
    tulisSemuaBukuKeFile(arr, n);
    printf("Buku dengan ID %d dihapus.\n", id);
}

/* Edit Informasi buku */
void editBuku() {
    int id;
    printf("\nMasukkan ID buku yang ingin diedit: ");
    if (scanf("%d", &id) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }
    clearBuffer();
    Buku arr[MAX_BOOKS]; int n=0; bacaBukuDariFile(arr, &n);
    int idx = -1;
    for (int i=0;i<n;i++) if (arr[i].id == id) { idx = i; break; }
    if (idx == -1) { printf("Buku tidak ditemukan.\n"); return; }

    char buf[MAX_STR];
    printf("Judul (%s): ", arr[idx].judul);
    fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(arr[idx].judul, buf, MAX_STR);

    printf("Penulis (%s): ", arr[idx].penulis);
    fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(arr[idx].penulis, buf, MAX_STR);

    printf("Kategori (%s): ", arr[idx].kategori);
    fgets(buf, MAX_STR, stdin); buf[strcspn(buf, "\n")] = 0;
    if (strlen(buf) > 0) strncpy(arr[idx].kategori, buf, MAX_STR);

    tulisSemuaBukuKeFile(arr, n);
    printf("Buku berhasil diupdate.\n");
}

/* Ranking buku dari yg paling sering dipinjam */
static int cmp_buku(const void *a, const void *b) {
    const Buku *A = a, *B = b;
    return (B->dipinjamCount - A->dipinjamCount);
}

void rankingBuku() {
    Buku arr[MAX_BOOKS]; int n=0;
    bacaBukuDariFile(arr, &n);
    if (n == 0) { printf("Belum ada data buku.\n"); return; }
    qsort(arr, n, sizeof(Buku), cmp_buku);
    printf("\n=== RANKING BUKU POPULER ===\n");
    printf("Pos | ID | Judul | Dipinjam\n");
    for (int i=0;i<n && i<10;i++) {
        printf("%d. %d | %s | %d kali\n", i+1, arr[i].id, arr[i].judul, arr[i].dipinjamCount);
    }
}
