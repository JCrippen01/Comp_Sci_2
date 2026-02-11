# 🚀 Doxy Stamp – Quick Start Guide

This guide is for beginner students who just want to download and use the Doxy Stamping Tool as quickly as possible.

---

# What This Tool Does

It scans your current folder for C++ files and replaces the `<doxy>` tag with a formatted Doxygen header.

You will be prompted for:

* Date (auto-detected)
* Assignment name
* Which files to stamp

---

# 🖥 macOS / Linux Quick Start

## 1️ Download the file

You can download directly in Terminal:

```bash
curl -O https://raw.githubusercontent.com/YOUR_USERNAME/Comp_Sci_2/main/homework_tools/Doxy_Stamp/doxy_stamp.cpp
```

Or click `doxy_stamp.cpp` on GitHub and download it manually.

---

## 2️ Compile

Open Terminal and navigate to where the file was downloaded:

```bash
cd Downloads
```

Compile:

```bash
g++ -std=c++20 doxy_stamp.cpp -o doxy_stamp
```

---

## 3️ Use the Tool

Go to your assignment folder:

```bash
cd ~/Comp_Sci_2/Assignment3
```

Run the tool:

```bash
/path/to/doxy_stamp
```

If it is in the same folder:

```bash
./doxy_stamp
```

Follow the prompts.

---

#  Windows (MinGW) Quick Start

## 1️ Download

Download `doxy_stamp.cpp` from GitHub.

---

## 2️ Compile

Open Command Prompt and navigate to the folder:

```bash
g++ -std=c++20 doxy_stamp.cpp -o doxy_stamp.exe
```

---

## 3️ Run

```bash
doxy_stamp.exe
```

Follow the prompts.

---

#  How To Use Inside Your C++ Files

At the top of your `.cpp` or `.h` file, add:

```cpp
<doxy>
```

When the tool runs, it will replace that tag with a formatted header.

---

# Example Output

Before:

```cpp
<doxy>

#include <iostream>
```

After:

```cpp
/**
 * ************************************************************
 * @file Destination.cpp
 * @author your_uid
 * @date 2026-02-11
 * @brief Assignment Name
 * ************************************************************
 */

#include <iostream>
```

---

# That’s It

1. Add `<doxy>`
2. Run the tool
3. Approve files
4. Done

You now have clean, consistent documentation headers for your assignments.
