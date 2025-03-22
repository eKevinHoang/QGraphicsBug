# Qt Bug Report: `setCursor()` Stops Working & Hover Event Issue  

## 📝 Overview  
This repository contains a minimal example to demonstrate two Qt bugs:  
1. **Hover event does not trigger in a ~10px area at the bottom edge of a `RectItem`**  
2. **`setCursor()` stops working after interacting with a messagebox using the keyboard**  

## 🛠 Environment  
- **Qt Version:** 6.8.2  
- **OS:** macOS Sequoia 15.3.2  
- **Compiler:** Apple Clang 16.0.0 (clang-1600.0.26.6)  

## 🔧 Build & Run Instructions
```sh
git clone https://github.com/eKevinHoang/QGraphicsBug.git
cd QGraphicsBug
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
./build/QGraphicsBug
```

## 🚀 Steps to Reproduce  

### **Bug 1: Hover event does not trigger in a ~10px area at the bottom edge of `RectItem`**  
1. **Run the app.** *(See [Build Instructions](#-build-instructions) above.)*  
2. Move the mouse to the edges of the pre-drawn `RectItem` objects and observe the cursor.  
   - ✅ **Expected:** The cursor changes correctly based on `ResizeDirection`.  
3. Zoom in and out freely using the mouse wheel. *(Do not move or resize the application window.)*  
4. Move the mouse again to the edges of the `RectItem` objects.  
   - ❌ **Issue:** The **bottom ~10px region does not trigger hover events**. Even debug messages inside `hoverMoveEvent()` do not appear.

---

### **Bug 2: `setCursor()` stops working after interacting with a messagebox**  
1. **Start from step 1 of Bug 1**, or launch the app normally.  
2. **Pan the image** by holding `Command` and dragging the mouse.  
   - ✅ **Expected:** The cursor should change to a **hand cursor (`Qt::OpenHandCursor`)** while panning.  
3. Press `Command + Z` to trigger a **messagebox**.  
4. Interact with the messagebox using the **keyboard** (e.g., press `Space` or `Tab` to navigate buttons).  
5. Try panning the image again.  
   - ❌ **Issue:** The cursor remains **stuck as an arrow (`Qt::ArrowCursor`)**, even after clicking on the scene
🔹 **Note:** This issue does not always occur, but it is **fairly easy to reproduce**.  
🔹 **Hypothesis:** This may be due to a **Qt UI thread synchronization issue** when handling cursor updates after modal dialogs.  

---
