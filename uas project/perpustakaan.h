#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definisi struct
typedef struct {
    int id;
    char judul[100];
    char penulis[100];
    char kategori[50];  // Fiksi, Non-Fiksi, Komik, Majalah, Referensi
    char status[20];    // Tersedia, Dipinjam
} Buku;

typedef struct {
    int id;
    char nama[100];
    char email[100];
} Anggota;

typedef struct {
    int id_buku;
    int id_member;
    char tanggal_pinjam[11];  // Format YYYY-MM-DD
    char tanggal_kembali[11]; // Format YYYY-MM-DD atau "None"
    float denda;
} Peminjaman;

// Konstanta
#define MAX_LOAN_DAYS 7
#define FINE_PER_DAY 1000.0

// Prototipe fungsi dari utils.c
void load_books(Buku **books, int *count);
void save_books(Buku *books, int count);
void load_members(Anggota **members, int *count);
void save_members(Anggota *members, int count);
void load_loans(Peminjaman **loans, int *count);
void save_loans(Peminjaman *loans, int count);
int login();

// Prototipe fungsi dari buku.c
void add_book(Buku **books, int *count);
void delete_book(Buku **books, int *count);
void edit_book(Buku *books, int count);
void view_books(Buku *books, int count);
void categorize_books(Buku *books, int count, const char *kategori);
void search_books(Buku *books, int count, const char *query, const char *by);

// Prototipe fungsi dari anggota.c
void register_member(Anggota **members, int *count);
void view_members(Anggota *members, int count);

// Prototipe fungsi dari peminjaman.c
void borrow_book(Buku *books, int book_count, Peminjaman **loans, int *loan_count, Anggota *members, int member_count);
void return_book(Buku *books, int book_count, Peminjaman *loans, int loan_count);
void view_loan_history(Peminjaman *loans, int loan_count, int id_member);
void book_ranking(Peminjaman *loans, int loan_count);
void statistics(int book_count, int member_count, int loan_count);  // Fitur tambahan

#endif
