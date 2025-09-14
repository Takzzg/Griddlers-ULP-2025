# Griddlers-ULP-2025

This is a re-upload of an old repo from 2016 (which was a mess)

Born from an university assignment, the goal wass to recreate a simple version of the griddlers game (or nonogram, Picross, Paint by Numbers, etc...) as a console application.

<img width="979" height="512" alt="imagen" src="https://github.com/user-attachments/assets/82547d69-9e3f-4cbc-bddf-28508b51e931" />
<img width="979" height="512" alt="imagen" src="https://github.com/user-attachments/assets/1366fe47-93dd-48d2-9398-447126af8eff" />
<img width="979" height="512" alt="imagen" src="https://github.com/user-attachments/assets/8f3d0fa2-f7e1-41a8-b30d-3b97ed21a5e5" />

## Regarding the re-upload

This solution was created from scratch as a C++ Console App using Visual Studio 2022 <br/>
The whole source code for the project can be found inside `Griddlers-ULP.cpp`. <br/>
You can also get a .exe build from the releases page (https://github.com/Takzzg/Griddlers-ULP-2025/releases)

Some minimal changes have been done in order to simplify the code base and allow it running with modern compilers:
- Commented out `#include "stdafx.h"` (file removed)
- Change deprecated function calls
  * `getch()` -> `_getch()`
  * `kbhit()` -> `_kbhit()`
- easter egg re-discovered
