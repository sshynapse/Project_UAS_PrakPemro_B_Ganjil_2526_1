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

