# Dictionary Manager

This is a console application written in C for the BME "Programming Fundamentals" course. It functions as a complete multilingual dictionary manager. The system uses a **linked list** to manage multiple bilingual dictionaries and supports full CRUD (Create, Read, Update, Delete) operations for both dictionaries and the word pairs they contain.

The project is built with a modular structure in C and features manual memory management with `debugmalloc.h` for leak detection.

## 📚 Features

### Dictionary Management
* List and select from all available dictionaries.
* Create new bilingual dictionaries (e.g., "english_hungarian").
* Delete existing dictionaries from the list.
* Load a dictionary from a custom-formatted `.txt` file.
* Save a dictionary back to a `.txt` file.

### Word Pair Management
* List all word pairs within a selected dictionary.
* Add new word pairs.
* Modify existing word pairs (first, second, or both words).
* Delete specific word pairs.

### Utilities
* **QUIZ Mode:** Practice vocabulary from a selected dictionary. The app tracks correct/incorrect answers.
* **ASCII Art:** Custom ASCII art logo for the text-based UI.
* **Error Handling:** Robust input validation (e.g., checking for numbers in names, menu bounds).

---

## 🛠️ Technical Implementation

* **Language:** C (using `stdio.h`, `stdlib.h`, `string.h`, `stdbool.h`).
* **Architecture:** Modular design separating logic into:
    * `main.c`: Main application loop and menu handling.
    * `lista_muveletek.c`: Linked list management (add/delete/find nodes).
    * `szotar_muveletek.c`: Dictionary-specific operations (add/edit/delete words).
    * `seged.c`: UI helpers, console clearing, and input validation.
* **Core Data Structure:**
    * The primary data structure is a **linked list** (`struct Lista`) where each node represents one dictionary.
    * Each dictionary `struct Szotar` stores its two languages (`char *nyelv1`, `char *nyelv2`).
    * Word pairs are stored in a **static 3D array** (`char szoparok_tomb[2][1000][50+1]`) within each `Szotar` struct, with a hard-coded capacity of 1000 pairs.
* **Memory Management:**
    * All dictionary nodes (`Lista`) and language names are dynamically allocated using `malloc`.
    * Includes `debugmalloc.h` for memory leak and error detection.
    * A `L_Felszabadit` function handles the cleanup of the entire linked list on exit.

---

## 📂 Modular Folder Structure
To enhance clarity and professional organization, the project files are structured into dedicated directories:
* **`src/`**: Contains all C source files (`.c`).
* **`include/`**: Contains all header files (`.h`), defining the public interfaces and data structures.
* **`data/`**: Stores example dictionary files (e.g., `magyar_olasz.txt`).
* **`build/`**: The output directory for compiled object files and the final executable.

---

## ⚙️ Compilation & Execution

The project requires the **GCC** compiler. Compilation can be achieved either through direct compiler calls or using the build automation tool `make`.

### A. Direct GCC Compilation (Recommended for Minimal Environments like MINGW/Git Bash)
This method explicitly links all source files and is the most reliable if build tools are missing.

1.  **Create Build Directory:** The output directory must exist before compilation:
    ```bash
    mkdir build
    ```

2.  **Compile and Link:** Execute the following command from the project root. The `-Iinclude` flag is crucial as it tells the compiler where to find the header files.
    ```bash
    gcc -Wall -Wextra -std=c99 -g -Iinclude src/main.c src/lista_muveletek.c src/szotar_muveletek.c src/seged.c -o build/dictionary_manager.exe
    ```

3.  **Run Application:**
    ```bash
    ./build/dictionary_manager.exe
    ```
    
### B. Build Automation (Ideal Method: Requires GNU Make)
If the **GNU Make** utility is installed and configured, the process is simpler using the included `Makefile`:
```bash
make
./build/dictionary_manager.exe
```
Use make clean to remove compiled files and the build/ directory.

---

## 🖥️ Controls & Menus

The application operates on a two-tiered menu system.

**Main Menu:**
* `[0]` Select Dictionary (leads to Sub-Menu)
* `[1]` Create New Dictionary
* `[2]` Delete Dictionary
* `[3]` Load from File
* `[4]` Exit

**Dictionary Sub-Menu (after selecting a dictionary):**
* `[0]` List Word Pairs
* `[1]` Save to File
* `[2]` Add Word Pair
* `[3]` Modify Word Pair
* `[4] `Delete Word Pair
* `[5]` Start QUIZ
* `[6]` Back to Main Menu

## 💾 File Persistence Format

The program uses a strict, custom format for saving and loading dictionaries.

* **Filename Convention:**
    * Must be in the format `lang1_lang2` or `lang1_lang2.txt`.
    * The program prevents loading a file if a dictionary with that language pair (in that specific order) already exists.
* **File Content Format:**
    * A single line of text containing all data, using `;` and `,` as delimiters.
    * **Format:** `nyelv1;nyelv2;szo1_nyelv1,szo1_nyelv2;szo2_nyelv1,szo2_nyelv2;...`
    * **Example:** `magyar;olasz;alma,mela;korte,pera;kutya,cane;macska,gatto;`
