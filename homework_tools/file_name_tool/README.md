# file_naming_tool

`file_naming_tool` is a simple C++ command-line program that prepares your Comp Sci assignments for submission.

It:

- Prefixes all `.cpp` and `.h` files with your Unique ID  
  Example: `luggage.cpp` → `your_uid_luggage.cpp`
- Prevents double-prefixing
- Creates a zip file named:

  ```
  your_uid_Project_Name.zip
  ```

- Leaves your original files untouched

---

# How It Works

If your folder contains:

```
luggage.h
luggage.cpp
main.cpp
```

And your Unique ID is:

```
your_uid
```

Running:

```bash
file_naming_tool "Module 5 Assignment"
```

Creates:

```
your_uid_Module_5_Assignment.zip
```

Inside the zip:

```
your_uid_luggage.h
your_uid_luggage.cpp
your_uid_main.cpp
```

---

# Requirements

- C++17 compatible compiler
- `zip` utility installed

macOS includes `zip` by default.  
Linux may require installation.  
Windows users are encouraged to use WSL for best compatibility.

---

# macOS Setup

## Compile

Open Terminal in the folder containing `file_naming_tool.cpp`:

```bash
clang++ -std=c++17 -O2 file_naming_tool.cpp -o file_naming_tool
```

## Install (optional but recommended)

```bash
sudo mv file_naming_tool /usr/local/bin/
```

## Run

From any folder containing your assignment files:

```bash
file_naming_tool "Project Name"
```

---

# Linux (Ubuntu / Debian)

## Install dependencies

```bash
sudo apt update
sudo apt install -y g++ zip
```

## Compile

```bash
g++ -std=c++17 -O2 file_naming_tool.cpp -o file_naming_tool
```

## Install (optional)

```bash
sudo mv file_naming_tool /usr/local/bin/
```

## Run

```bash
file_naming_tool "Project Name"
```

---

# Windows (Recommended: WSL)

WSL provides a Linux environment inside Windows and works best with this tool.

## Install tools inside WSL

```bash
sudo apt update
sudo apt install -y g++ zip
```

## Compile

```bash
g++ -std=c++17 -O2 file_naming_tool.cpp -o file_naming_tool
```

## Optional: Move to PATH

```bash
sudo mv file_naming_tool /usr/local/bin/
```

## Run

```bash
file_naming_tool "Project Name"
```

---

# Windows (Native Visual Studio)

## Compile using Developer Command Prompt

Open "Developer Command Prompt for VS" and run:

```bash
cl /std:c++17 /EHsc file_naming_tool.cpp
```

This creates:

```
file_naming_tool.exe
```

## Add to PATH

Move the executable to a folder such as:

```
C:\Tools
```

Add `C:\Tools` to your system PATH:

1. Press Win + R  
2. Type `sysdm.cpl`  
3. Open Environment Variables  
4. Edit `Path`  
5. Add `C:\Tools`  
6. Restart terminal  

## Run

```powershell
file_naming_tool "Project Name"
```

Note: Windows does not include the `zip` command by default.  
You may need to install 7-Zip or use WSL instead.

---

# Using with VS Code

1. Open your assignment folder in VS Code.
2. Open the integrated terminal (Terminal → New Terminal).
3. Run:

```bash
file_naming_tool "Project Name"
```

If the tool was installed to PATH correctly, it will work inside VS Code’s terminal automatically.

---

# First Run

On first use, the tool will prompt for your Unique ID.

It saves the ID in a file named:

```
.submit_config
```

On future runs, it will confirm the stored ID before continuing.

You do not need to recompile if your ID changes.

---

# Summary

Workflow for students:

1. Finish assignment.
2. Open terminal in assignment folder.
3. Run:

```bash
file_naming_tool "Assignment Name"
```

4. Upload the generated zip file.

Simple and consistent for every submission.
