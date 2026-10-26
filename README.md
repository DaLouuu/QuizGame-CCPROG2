# QuizGame-CCPROG2 (General Knowledge Quiz Game)

A modular, interactive console-based quiz game and question bank management system developed in C for **CCPROG2** (Programming with Structured Data Types) at **De La Salle University (DLSU)**.

---

## Table of Contents
- [Project Overview](#project-overview)
- [Key Features](#key-features)
  - [1. Play Mode](#1-play-mode)
  - [2. Data Management (Admin Mode)](#2-data-management-admin-mode)
- [Frontend Evaluation](#frontend-evaluation)
- [Recommended Folder Hierarchy](#recommended-folder-hierarchy)
- [Data File Format](#data-file-format)
- [Build and Execution](#build-and-execution)
- [Default Credentials](#default-credentials)
- [Author & Academic Information](#author--academic-information)

---

## Project Overview

**QuizGame-CCPROG2** is a general knowledge quiz application designed to test players on diverse topics (such as Science, Geography, Art, Music, and History). It combines an interactive quiz runner with a robust administrative question bank system capable of reading, editing, deleting, importing, and exporting question records using formatted text files.

---

## Key Features

### 1. Play Mode
- **Topic Selection**: Dynamically scans loaded question records and categorizes them by unique topics.
- **Randomized Question Draw**: Prompts players with random questions from their chosen topic without repetition in a single draw session.
- **Instant Scoring & Feedback**: Evaluates player inputs against correct answer indices, displays immediate feedback, and calculates accumulated score totals.
- **Persistent Leaderboard**: Tracks player scores in `score.txt`, aggregates scores for returning players, and renders a sorted leaderboard table.

### 2. Data Management (Admin Mode)
- **Password-Protected Authentication**: Secures administrative privileges behind a password (`admin123`) featuring interactive terminal character masking (`*`) powered by `<conio.h>`.
- **Add Record**: Validates question prompts, prevents duplicate question/answer pairs, enforces distinct multiple-choice options, and calculates auto-incrementing topic question indices.
- **Edit Record**: Allows editing any field of an existing record (Topic, Question prompt, Multiple-choice options, or Correct answer) with real-time validation.
- **Delete Record**: Interactive record deletion with confirmation prompts and array shift re-indexing.
- **Import Data**: Parses structured question records from external text files (e.g., `GuillarteDImport.txt`, `sample-records-updated.txt`) into memory.
- **Export Data**: Sorts question records alphabetically by topic using selection sort and exports them to structured text files.

---

## Frontend Evaluation

### Does this project have a frontend?
- **Current State**: The project has an **interactive Terminal / Console User Interface (TUI / CLI)**. It does **not** have a graphical user interface (GUI) or web frontend (HTML/CSS/JavaScript).
- **Console Interface Highlights**:
  - Uses extended ASCII / IBM box-drawing characters (`╔`, `╗`, `╚`, `╝`, `═`, `║`, `╠`, `╣`) to construct decorative title screens, menus, and borders.
  - Windows console integration with `system("cls")` for clear screen transitions and `system("pause")` for paced user interactions.
  - Password input masking via `getch()` so credentials are not displayed in plaintext on screen.
- **Frontend Modernization Options (Optional Future Work)**:
  - **Desktop GUI**: Native Windows GUI (Win32 / C++ WinUI), Raylib, or SDL2 for graphics and sound.
  - **Web Frontend**: A Node.js/Express or Python backend wrapping the quiz logic with an interactive HTML5/Vanilla CSS/JavaScript frontend.

---

## Recommended Folder Hierarchy

The original repository placed all source, binary, documentation, and data files into a single root directory. To align with standard C software engineering best practices, the following modular folder hierarchy is recommended:

```text
QuizGame-CCPROG2/
├── .gitignore                      # Ignore compiled binaries, object files, and IDE artifacts
├── Makefile                        # Build automation script for compiling the project
├── README.md                       # Comprehensive project documentation
│
├── bin/                            # Output directory for compiled executables (git-ignored)
│   └── QuizGame.exe
│
├── data/                           # Question datasets and runtime files
│   ├── GuillarteDImport.txt        # Initial question bank dataset
│   ├── sample-records-updated.txt  # Extended question dataset
│   └── score.txt                   # Persistent leaderboard score data
│
├── docs/                           # Documentation and academic deliverables
│   └── GuillarteD.pdf              # Machine project test plan and test cases
│
├── include/                        # Header declarations (.h)
│   └── GuillarteDFunc.h            # Struct definitions, macros, and function prototypes
│
└── src/                            # Implementation files (.c)
    ├── GuillarteD.c                # Main entry point and main menu loop
    └── GuillarteDFunc.c            # Implementation of game logic and admin operations
```

### Key Architectural Separation of Concerns:
1. **`src/` & `include/`**: Isolates code implementation and interfaces, preventing cluttered root directories and facilitating modular multi-file builds.
2. **`data/`**: Groups text files used for persistent storage and import/export operations.
3. **`docs/`**: Retains academic requirements, specifications, and test cases separate from production code.
4. **`bin/`**: Keeps transient compilation binaries out of version control.

---

## Data File Format

Question records in `.txt` import and export files follow a standardized structured layout:

```text
<Topic>
<Question Number within Topic>
<Question Prompt Text>
<Choice 1>
<Choice 2>
<Choice 3>
<Correct Answer String>

```

*Example:*
```text
Science
1
What is the smallest unit of life?
Cell
Atom
Molecule
Cell

Geography
1
What is the capital of Canada?
Toronto
Montreal
Ottawa
Ottawa
```

---

## Build and Execution

### Prerequisites
- GCC Compiler (MinGW for Windows)
- Windows Command Prompt or PowerShell (supports `<conio.h>` and Windows console commands)

### Compilation
Compile using GCC with full warnings enabled:

```bash
gcc -Wall -Wextra GuillarteD.c -o GuillarteD.exe
```

### Running the Application
```bash
./GuillarteD.exe
```

---

## Default Credentials

| Mode | Field | Value |
| :--- | :--- | :--- |
| **Manage Data (Admin)** | Password | `admin123` |

---

## Author & Academic Information

- **Author**: Dana Louise A. Guillarte
- **Course**: CCPROG2 (Programming with Structured Data Types)
- **Section**: S23A
- **Institution**: De La Salle University (DLSU)
- **Version**: 2.0