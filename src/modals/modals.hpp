#pragma once

typedef enum {
    NO_MODAL = 0,

    ABOUT_IM_MINI,
    ABOUT_MINIPRO,
    ABOUT_IMGUI,

    CREATE_CHIP,

    UPDATE_FIRMWARE,

    PROGRAMMER_WRITE,
    PROGRAMMER_READ
} ModalEnum;

void SetModalState(ModalEnum newState);
void RenderModals();