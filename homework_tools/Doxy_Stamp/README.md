# Doxy Stamp

A simple CLI utility that automatically inserts a formatted Doxygen header into C++ source files.

The tool detects the current system date, confirms it with the user, and replaces a `<doxy>` tag in your file with a boxed documentation header.

---

# Features

* Scans the current directory for C++ source/header files
* Prompts you file-by-file to choose which files to stamp
* Auto-detects system date and asks for confirmation
* Allows manual date override
* Prompts for assignment name once, then uses it for all stamped files
* Replaces `<doxy>` with a formatted header
* Targets common C++ file types only (`.cpp`, `.cc`, `.cxx`, `.h`, `.hpp`, `.hxx`)
* Works on macOS, Linux, and Windows
* Lightweight — no dependencies beyond the C++ standard library

---

# Example Output

If your file contains:

```cpp
<doxy>

#include <iostream>
```

After running the tool:

```cpp
/**
 * ************************************************************
 * @file Destination.cpp
 * @author your_uid
 * @date 2026-02-11
 * @brief Assignment 3 - Destination Class
 * ************************************************************
 */

#include <iostream>
```

---

# Installation

---

## macOS / Linux

### 1. Compile

```bash
g++ -std=c++20 stamp.cpp -o doxy_stamping_tool
```

### 2. Move to system PATH

```bash
sudo mv doxy_stamping_tool /usr/local/bin/
```

If `/usr/local/bin` does not exist:

```bash
sudo mkdir -p /usr/local/bin
sudo mv doxy_stamping_tool /usr/local/bin/
```

### 3. Make executable (if needed)

```bash
chmod +x /usr/local/bin/doxy_stamping_tool
```

### 4. Verify installation

```bash
doxy_stamping_tool
```

If it runs from any directory, installation is complete.

---

## Windows (Command Prompt or PowerShell)

### 1. Compile

If using MinGW:

```bash
g++ -std=c++20 stamp.cpp -o doxy_stamping_tool.exe
```

### 2. Create tools directory

Create a folder:

```
C:\tools
```

### 3. Move executable

Move:

```
doxy_stamp.exe
```

to:

```
C:\tools
```

### 4. Add to PATH

1. Press Win + R
2. Type: `sysdm.cpl`
3. Go to Advanced → Environment Variables
4. Edit "Path" under User Variables
5. Add:

```
C:\tools
```

6. Restart terminal

### 5. Test

```

doxy_stamping_tool
```

---

## Visual Studio (Windows Users)

### Option A — Run From Developer Command Prompt

1. Open "x64 Native Tools Command Prompt for VS"
2. Navigate to folder containing `stamp.cpp`
3. Compile:

```bash
cl /std:c++20 stamp.cpp
```

4. Move the generated `.exe` to `C:\tools`
5. Add `C:\tools` to PATH (see Windows section above)

---

### Option B — Build Inside Visual Studio

1. Create a new Console Application project
2. Replace `main.cpp` with the tool code
3. Build project
4. Locate compiled `.exe` in:

```
ProjectFolder\x64\Debug\
```

5. Move `.exe` to `C:\tools`
6. Add `C:\tools` to PATH

---

# Usage

1. Add `<doxy>` near the top of each C++ file you want to stamp:

```cpp
<doxy>

#include <iostream>
```

2. `cd` into your assignment/project folder:

```bash
cd ~/CS2/Assignment3
```

3. Run the tool:

```bash
doxy_stamping_tool
```

4. Follow the prompts. The tool will scan the current directory and ask about each C++ file it finds:

```
Detected today's date: 2026-02-11
Is this correct? (y/n): y
Enter assignment name: Assignment 3 - Destination

Scanning current directory...

Stamp file: Destination.cpp ? (y/n): y
Destination.cpp stamped successfully.

Stamp file: Destination.h ? (y/n): y
Destination.h stamped successfully.

Stamp file: main.cpp ? (y/n): n

Done.
```

5. Open the files you stamped — the `<doxy>` tag will be replaced with the header.

---

# Notes

* The tool only modifies files containing `<doxy>`
* It overwrites the file after replacement
* If the tag is not found, no changes are made
* Date format: `YYYY-MM-DD`

---

# Recommended Workflow

For each assignment:

1. Add `<doxy>` at top of file
2. Run `doxy_stamp`
3. Enter assignment name
4. Submit clean, consistent documentation

---

# Future Improvements (Optional Ideas)

* Accept filename as command-line argument
* Auto-detect all `.cpp` files in directory
* Prevent double stamping
* Add author name prompt
* Add template customization

---

# Hard Coding a Unique ID

If you would like to permanently embed your student ID or unique identifier into the tool (instead of prompting for it), you can hard code it directly in the source file.

Inside your C++ program, locate the section where the Doxygen header is built. You likely have a line similar to:

```cpp
stamp += " * @author your_uid
";
```

To hard code your own unique ID, simply replace `your_uid` with your identifier:

```cpp
stamp += " * @author YOUR_UNIQUE_ID
";
```

For example:

```cpp
stamp += " * @author 1234567
";
```

Recompile the program after making the change:

```bash
g++ -std=c++20 stamp.cpp -o doxy_stamping_tool
```

After recompiling, every stamped file will automatically include your unique ID without additional prompts.

If you prefer to make the ID configurable but still default to your own, you could instead define a constant at the top of your file:

```cpp
const std::string AUTHOR_ID = "1234567";
```

And then use:

```cpp
stamp += " * @author " + AUTHOR_ID + "
";
```

This keeps the code clean and makes future updates easier.

---

You have built a lightweight developer documentation utility that can be installed system-wide and used across projects.
