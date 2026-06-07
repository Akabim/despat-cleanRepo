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

# Technical Design Document: Balatro Chain of Responsibility & Skip Reward System

## 1. Project Overview
This project is a modular gameplay system inspired by *Balatro*, implementing hand detection, scoring, blind progression, and a skip reward system. The primary goal is to demonstrate the use of Design Patterns to create an extensible and maintainable runtime architecture.

## 2. Architectural Design Patterns

### 2.1 State Pattern (Blind Progression)
Used to manage the progression between different "Blinds" (Small Blind, Big Blind, and Boss Blind).

- **Implementation**: `BlindState` (Abstract Interface), `SmallBlindState`, `BigBlindState`, `BossBlindState`.
- **Logic**: Each state defines its own target score and reward money. The `createNextState()` method handles the transition, including incrementing the **Ante** when moving from a Boss Blind back to a Small Blind.
- **Benefit**: Decouples the progression logic from the main game loop, making it easy to add new types of blinds (e.g., special Boss Blinds).

### 2.2 Command Pattern (Skip Reward System)
Used to implement the deferred execution of rewards when a player chooses to "SKIP" a blind.

- **Implementation**: `RewardCommand` (Abstract Interface), `BonusHandCommand`, `FreePlayingCardCommand`.
- **Deferred Execution**: Commands are created by a `BlindState` but stored in a `RewardCommandManager` rather than being executed immediately.
- **Timing**: Commands are associated with a `RewardTiming` (Start, NextBlind, NextAnte) and executed only when the specific timing condition is met in the game loop.

### 2.3 Chain of Responsibility (Hand Detection)
Used to detect 13 different types of poker hands in a priority-based sequence.

- **Implementation**: `HandChecker` (Base Class) and 13 concrete checkers (e.g., `RoyalFlushChecker`, `FlushChecker`, etc.).
- **Logic**: Each checker evaluates if the current hand matches its criteria; if not, it passes the request to the `nextChecker` in the chain.

## 3. Core Components

### 3.1 GameSessionState (Runtime State)
A centralized object that tracks the current state of the game session:
- **Ante**: Current difficulty level.
- **Hands Remaining**: Number of plays left for the current blind.
- **Money**: Player's current currency.
- **Deck**: Current cards available in the session.

### 3.2 RewardCommandManager
Manages the lifecycle of reward commands:
- **addCommand()**: Stores a command with its associated timing.
- **executeCommands()**: Checks the timing and triggers the `execute()` method of the commands, passing the `GameSessionState` for modification.

### 3.3 RewardFactory
A simple Factory pattern used to instantiate `RewardCommand` objects based on string tags, simplifying the creation process within the `BlindState`.

## 4. Gameplay Flow

1. **Start Blind**: The system queries the `BlindManager` for the current `BlindState`.
2. **Player Action**:
   - **PLAY**: The player plays hands. `HandChecker` chain detects the hand, `JokerManager` modifies the score, and results are compared against the target score.
   - **SKIP**: The `BlindState` generates a `RewardCommand`. This command is registered in the `RewardCommandManager`.
3. **Resolution**:
   - If cleared, the system moves to the `nextState()`.
   - If skipped, the system immediately moves to the `nextState()`.
4. **Reward Execution**: At the start of the next phase (e.g., `NextBlind`), the `RewardCommandManager` executes all pending commands that match the current timing.

## 5. Collaboration & Git Workflow
The project was developed using a collaborative Git strategy:
- **Feature Branching**: Distinct features were developed on separate branches (e.g., `sultan`, `feature/skip-reward-command-system`).
- **Merging**: Regular merges were performed to the `abim` and eventually `main` branches.
- **Atomic Commits**: Changes were committed in small, logical chunks with descriptive messages to maintain a clean and readable history.
