#include "../graphics.h"
#include "../../lua.h"
#include "../../util.h"

#include <raylib.h>

// Window

defun(toggleFullscreen);
defun(setTargetFPS);

// Drawing

defun(setDrawColor);
defun(clearBackground);
defun(drawCircle);
defun(drawRect);
defun(drawText);

// Input

defun(isKeyDown);
defun(isKeyUp);

defun(isMouseButtonPressed);
defun(isMouseButtonReleased);
defun(isMouseButtonDown);
defun(isMouseButtonUp);

defun(getMousePos);
