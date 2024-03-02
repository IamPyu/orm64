#include "../graphics.h"
#include "../../lua.h"
#include "../../util.h"

// Window

defun(toggleFullscreen);
defun(setTargetFPS);

// Drawing

defun(setDrawColor);
defun(clearBackground);
defun(drawCircle);
defun(drawRect);
defun(drawText);
defun(drawTexture);
defun(drawTextureExtra);

// Input

defun(isKeyDown);
defun(isKeyUp);
defun(isKeyPressed);
defun(isKeyReleased);

defun(isMouseButtonPressed);
defun(isMouseButtonReleased);
defun(isMouseButtonDown);
defun(isMouseButtonUp);

defun(getMousePos);

// Gamepads

defun(isGamepadButtonPressed);
defun(isGamepadButtonReleased);
defun(isGamepadButtonDown);
defun(isGamepadButtonUp);
