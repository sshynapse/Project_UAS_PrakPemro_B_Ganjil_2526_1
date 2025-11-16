#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR 100
#define MAX_BOOKS 1000
#define MAX_MEMBERS 500
#define MAX_LOANS 1000

/* Struktur Buku */
typedef struct{
    int id;
    char judul[MAX_STR];
    char penulis[MAX_STR];
    char kategori[MAX_STR];
    int tersedia;       // 1 = tersedia, 0 = dipinjam
    int dipinjamCount;  // berapa kali dipinjam
} Buku;

/* Struktur Anggota */
typedef struct{
    int id;
    char nama[MAX_STR];
    char alamat[MAX_STR];
} Anggota;

/* Struktur Peminjaman */
typedef struct {
    int id;
    int idBuku;
    int idAnggota;
    char tanggalPinjam[20];   // "DD-MM-YYYY"
    char tanggalKembali[20];  // "-" kalo belum kembali
    int denda;
} Peminjaman;

void tampilkanMenuUtama();
void loginPustakawan();

/* buku */
void tambahBuku();
void hapusBuku();
void editBuku();
void tampilkanDaftarBuku();
void cariBuku();
void rankingBuku();

void simpanBuku_tambah(Buku buku);
void bacaBukuDariFile(Buku daftarBuku[], int *jumlah);
void tulisSemuaBukuKeFile(Buku daftarBuku[], int jumlah);

/* anggota */
void tambahAnggota();
void tampilkanAnggota();
void simpanAnggota_tambah(Anggota anggota);
void bacaAnggotaDariFile(Anggota daftarAnggota[], int *jumlah);

/* peminjaman */
void pinjamBuku();
void kembalikanBuku();
int hitungDenda(const char *tglPinjam, const char *tglKembali);
void simpanPeminjaman_tambah(Peminjaman peminjam);
void bacaPeminjamDariFile(Peminjaman daftarPeminjam[], int *jumlah);
void tulisSemuaPeminjamanKeFile(Peminjaman daftarPeminjam[], int jumlah);
void tampilkanRiwayatAnggota();

/* utils */
void getTanggalSekarang(char *buffer);
void clearBuffer();
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strcasestr(const char *haystack, const char *needle);

/* konfigurasi */
int getMaxLoanDays();
void ubahDurasiPeminjaman();

#endif
