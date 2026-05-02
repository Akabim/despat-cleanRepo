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
