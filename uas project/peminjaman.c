#include "perpustakaan.h"

/* tambah peminjaman */
void simpanPeminjaman_tambah(Peminjaman peminjam) {
    FILE *fp = fopen("data/loans.txt", "a");
    if (!fp) { printf("Gagal membuka file loans.txt\n"); return; }
    fprintf(fp, "%d|%d|%d|%s|%s|%d\n",
            peminjam.id, peminjam.idBuku, peminjam.idAnggota,
            peminjam.tanggalPinjam, peminjam.tanggalKembali, peminjam.denda);
    fclose(fp);
}

/* Baca semua peminjaman */
void bacaPeminjamDariFile(Peminjaman daftarPeminjam[], int *jumlah) {
    FILE *fp = fopen("data/loans.txt", "r");
    *jumlah = 0;
    if (!fp) return;
    Peminjaman p;
    while (fscanf(fp, " %d|%d|%d|%19[^|]|%19[^|]|%d",
                  &p.id, &p.idBuku, &p.idAnggota, p.tanggalPinjam, p.tanggalKembali, &p.denda) == 6) {
        daftarPeminjam[*jumlah] = p;
        (*jumlah)++;
        if (*jumlah >= MAX_LOANS) break;
        int c; while ((c = fgetc(fp)) != EOF && c != '\n');
    }
    fclose(fp);
}

/* Tulis semua data peminjaman anggota */
void tulisSemuaPeminjamanKeFile(Peminjaman daftarPeminjam[], int jumlah) {
    FILE *fp = fopen("data/loans.txt", "w");
    if (!fp) { printf("Gagal menulis loans.txt\n"); return; }
    for (int i=0;i<jumlah;i++) {
        Peminjaman *p = &daftarPeminjam[i];
        fprintf(fp, "%d|%d|%d|%s|%s|%d\n",
                p->id, p->idBuku, p->idAnggota, p->tanggalPinjam, p->tanggalKembali, p->denda);
    }
    fclose(fp);
}

/* Agar bisa dihitung selisih hari / denda peminjaman */
static int parseDate(const char *s, struct tm *out) {
    int d,m,y;
    if (sscanf(s, "%d-%d-%d", &d, &m, &y) != 3) return -1;
    memset(out, 0, sizeof(struct tm));
    out->tm_mday = d; out->tm_mon = m - 1; out->tm_year = y - 1900;
    return 0;
}

/* hitung denda otomatis berdasarkan konfigurasi */
int hitungDenda(const char *tglPinjam, const char *tglKembali) {
    struct tm tm1, tm2;
    if (parseDate(tglPinjam, &tm1) != 0) return 0;
    if (parseDate(tglKembali, &tm2) != 0) return 0;
    time_t t1 = mktime(&tm1), t2 = mktime(&tm2);
    if (t1 == (time_t)-1 || t2 == (time_t)-1) return 0;
    int hari = (int)difftime(t2, t1) / (60*60*24);
    int max = getMaxLoanDays();
    if (hari > max) return (hari - max) * 1000;
    return 0;
}

/* Peminjaman buku: cek buku tersedia & anggota terdaftar */
void pinjamBuku() {
    int idBuku, idAnggota;
    printf("\n=== PEMINJAMAN BUKU ===\n");
    printf("ID Buku: "); if (scanf("%d", &idBuku) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }
    printf("ID Anggota: "); if (scanf("%d", &idAnggota) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }

    Buku books[MAX_BOOKS]; int nb=0; bacaBukuDariFile(books, &nb);
    int idx = -1;
    for (int i=0;i<nb;i++) if (books[i].id == idBuku) { idx = i; break; }
    if (idx == -1) { printf("Buku tidak ditemukan.\n"); return; }
    if (books[idx].tersedia == 0) { printf("Buku sedang dipinjam.\n"); return; }

    /* cek anggota terdaftar */
    Anggota arrA[MAX_MEMBERS]; int na=0; bacaAnggotaDariFile(arrA, &na);
    int foundA=0;
    for (int i=0;i<na;i++) if (arrA[i].id == idAnggota) { foundA = 1; break; }
    if (!foundA) { printf("Anggota tidak terdaftar.\n"); return; }

    Peminjaman p;
    p.id = rand() % 100000 + 1;
    p.idBuku = idBuku; p.idAnggota = idAnggota;
    getTanggalSekarang(p.tanggalPinjam);
    strcpy(p.tanggalKembali, "-"); p.denda = 0;

    simpanPeminjaman_tambah(p);

    books[idx].tersedia = 0; books[idx].dipinjamCount += 1;
    tulisSemuaBukuKeFile(books, nb);

    printf("Buku berhasil dipinjam pada %s. ID peminjaman: %d\n", p.tanggalPinjam, p.id);
}

/* Pengembalian buku: cari peminjaman, set tanggalKembali, hitung denda, update buku */
void kembalikanBuku() {
    int idP;
    printf("\n=== PENGEMBALIAN BUKU ===\n");
    printf("Masukkan ID Peminjaman: ");
    if (scanf("%d", &idP) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }

    Peminjaman arr[MAX_LOANS]; int n=0; bacaPeminjamDariFile(arr, &n);
    int idx = -1;
    for (int i=0;i<n;i++) if (arr[i].id == idP) { idx = i; break; }
    if (idx == -1) { printf("ID peminjaman tidak ditemukan.\n"); return; }
    if (strcmp(arr[idx].tanggalKembali, "-") != 0) { printf("Sudah dikembalikan pada %s\n", arr[idx].tanggalKembali); return; }

    char tglKembali[20]; getTanggalSekarang(tglKembali);
    strncpy(arr[idx].tanggalKembali, tglKembali, sizeof(arr[idx].tanggalKembali)-1);
    arr[idx].denda = hitungDenda(arr[idx].tanggalPinjam, arr[idx].tanggalKembali);

    tulisSemuaPeminjamanKeFile(arr, n);

    Buku books[MAX_BOOKS]; int nb=0; bacaBukuDariFile(books, &nb);
    for (int i=0;i<nb;i++) if (books[i].id == arr[idx].idBuku) { books[i].tersedia = 1; break; }
    tulisSemuaBukuKeFile(books, nb);

    printf("Buku dikembalikan pada %s. Denda: Rp%d\n", arr[idx].tanggalKembali, arr[idx].denda);
}

/* Tampilkan riwayat peminjaman seorang anggota */
void tampilkanRiwayatAnggota() {
    int idA;
    printf("Masukkan ID anggota: ");
    if (scanf("%d", &idA) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }
    Peminjaman arr[MAX_LOANS]; int n=0; bacaPeminjamDariFile(arr, &n);
    int found = 0;
    printf("\n=== RIWAYAT PEMINJAMAN ANGGOTA %d ===\n", idA);
    for (int i=0;i<n;i++) {
        if (arr[i].idAnggota == idA) {
            printf("LoanID:%d | BukuID:%d | Pinjam:%s | Kembali:%s | Denda:%d\n",
                   arr[i].id, arr[i].idBuku, arr[i].tanggalPinjam, arr[i].tanggalKembali, arr[i].denda);
            found = 1;
        }
    }
    if (!found) printf("Belum ada riwayat.\n");
}
