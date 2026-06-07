# Balatro Chain of Responsibility

Implementasi Chain of Responsibility Pattern dalam C++ untuk deteksi 13 jenis poker hand.

## Poker Hands
- Royal Flush
- Straight Flush
- Five of a Kind
- Flush Five
- Flush House
- Four of a Kind
- Full House
- Flush
- Straight
- Three of a Kind
- Two Pair
- Pair
- High Card

## Build & Run
```bash
mkdir build && cd build
cmake ..
make
./balatro_checker
```

## Pattern

**Chain of Responsibility**: Setiap checker mengecek apakah bisa handle hand. Jika tidak, pass ke checker berikutnya dalam chain.

Chain order: RoyalFlush → StraightFlush → FiveOfAKind → ... → HighCard

**Base Class**: `HandChecker` dengan method `checkHand()` dan `setNextChecker()`

**Language**: C++17 | **Build**: CMake

---

# Dokumen Desain Teknis (TDD): Balatro Chain of Responsibility & Sistem Reward Skip

## 1. Gambaran Proyek
Proyek ini adalah sistem gameplay modular yang terinspirasi dari *Balatro*, mengimplementasikan deteksi kombinasi kartu, penilaian (scoring), progresi blind, dan sistem hadiah (reward) saat melakukan skip. Tujuan utamanya adalah untuk mendemonstrasikan penggunaan Pola Desain (Design Patterns) untuk menciptakan arsitektur runtime yang mudah dikembangkan dan dikelola.

## 2. Pola Desain Arsitektur

### 2.1 State Pattern (Progresi Blind)
Digunakan untuk mengelola progresi antara berbagai "Blind" (Small Blind, Big Blind, dan Boss Blind).

- **Implementasi**: `BlindState` (Interface Abstrak), `SmallBlindState`, `BigBlindState`, `BossBlindState`.
- **Logika**: Setiap state mendefinisikan target skor dan uang hadiahnya sendiri. Metode `createNextState()` menangani transisi, termasuk menaikkan **Ante** saat berpindah dari Boss Blind kembali ke Small Blind.
- **Keuntungan**: Memisahkan logika progresi dari loop game utama, membuatnya mudah untuk menambahkan jenis blind baru (misal: Boss Blind khusus).

### 2.2 Command Pattern (Sistem Reward Skip)
Digunakan untuk mengimplementasikan eksekusi tertunda (deferred execution) dari hadiah ketika pemain memilih untuk "SKIP" sebuah blind.

- **Implementasi**: `RewardCommand` (Interface Abstrak), `BonusHandCommand`, `FreePlayingCardCommand`.
- **Eksekusi Tertunda**: Command dibuat oleh sebuah `BlindState` tetapi disimpan di dalam `RewardCommandManager` alih-alih dieksekusi secara langsung.
- **Timing (Waktu)**: Command dikaitkan dengan sebuah `RewardTiming` (Start, NextBlind, NextAnte) dan hanya dieksekusi ketika kondisi waktu yang spesifik terpenuhi di dalam loop game.

### 2.3 Chain of Responsibility (Deteksi Hand)
Digunakan untuk mendeteksi 13 jenis kombinasi kartu poker dalam urutan berdasarkan prioritas.

- **Implementasi**: `HandChecker` (Base Class) dan 13 checker konkret (misal: `RoyalFlushChecker`, `FlushChecker`, dll.).
- **Logika**: Setiap checker mengevaluasi apakah kartu saat ini cocok dengan kriterianya; jika tidak, ia akan mengoper permintaan tersebut ke `nextChecker` dalam rantai tersebut.

## 3. Komponen Inti

### 3.1 GameSessionState (Status Runtime)
Sebuah objek terpusat yang melacak status sesi permainan saat ini:
- **Ante**: Tingkat kesulitan saat ini.
- **Hands Remaining**: Sisa kesempatan main untuk blind saat ini.
- **Money**: Mata uang pemain saat ini.
- **Deck**: Kartu yang saat ini tersedia di sesi.

### 3.2 RewardCommandManager
Mengelola siklus hidup dari reward command:
- **addCommand()**: Menyimpan command beserta waktu eksekusinya.
- **executeCommands()**: Mengecek waktu dan memicu metode `execute()` dari command, memberikan `GameSessionState` untuk dimodifikasi.

### 3.3 RewardFactory
Sebuah pola Factory sederhana yang digunakan untuk membuat instansiasi objek `RewardCommand` berdasarkan tag string, menyederhanakan proses pembuatan di dalam `BlindState`.

## 4. Alur Gameplay

1. **Start Blind**: Sistem menanyakan `BlindState` saat ini kepada `BlindManager`.
2. **Aksi Pemain**:
   - **PLAY**: Pemain memainkan kartu. Rantai `HandChecker` mendeteksi kartu, `JokerManager` memodifikasi skor, dan hasil dibandingkan dengan target skor.
   - **SKIP**: `BlindState` menghasilkan sebuah `RewardCommand`. Command ini didaftarkan di dalam `RewardCommandManager`.
3. **Resolusi**:
   - Jika berhasil mengalahkan blind, sistem berpindah ke `nextState()`.
   - Jika di-skip, sistem segera berpindah ke `nextState()`.
4. **Eksekusi Reward**: Pada awal fase berikutnya (misal: `NextBlind`), `RewardCommandManager` mengeksekusi semua command tertunda yang cocok dengan waktu saat ini.

## 5. Kolaborasi & Alur Kerja Git
Proyek ini dikembangkan menggunakan strategi Git kolaboratif:
- **Feature Branching**: Fitur-fitur yang berbeda dikembangkan pada cabang terpisah (misal: `sultan`, `feature/skip-reward-command-system`).
- **Merging**: Penggabungan reguler dilakukan ke cabang `abim` dan pada akhirnya ke cabang `main`.
- **Atomic Commits**: Perubahan dikomit dalam bagian kecil dan logis dengan pesan deskriptif untuk menjaga riwayat yang bersih dan mudah dibaca.
