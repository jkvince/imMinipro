#pragma once

typedef enum {
    NO_MODAL = 0,

    PROGRAMMER_WRITE,
    PROGRAMMER_READ,

    UPDATE_FIRMWARE,

    CREATE_CHIP,

    ABOUT_IM_MINI,
    ABOUT_MINIPRO,
    ABOUT_IMGUI,
    ABOUT_NATIVEFILEDIALOG

} ModalEnum;

void SetModalState(ModalEnum newState);
void RenderModals();