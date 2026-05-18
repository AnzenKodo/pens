#include <windows.h>
#include <stdio.h>
#include <math.h>

#include "ui_core.h"

//=============================================================================
// GDI RENDERER
//=============================================================================

static COLORREF V4ToRGB(V4 c) {
    return RGB((BYTE)(Clamp(0.0f, c.r, 1.0f) * 255.0f),
               (BYTE)(Clamp(0.0f, c.g, 1.0f) * 255.0f),
               (BYTE)(Clamp(0.0f, c.b, 1.0f) * 255.0f));
}

static void Win32RenderUIBox(HDC hdc, UI_Box *box) {
    if (!box) return;

    RECT r = {
        (int)box->rect.p0.x,
        (int)box->rect.p0.y,
        (int)box->rect.p1.x,
        (int)box->rect.p1.y
    };

    if (box->flags & UI_BoxFlag_DrawBackground) {
        V4 bg = box->bg_color;
        
        // Simple visual feedback using animation values
        if (box->flags & UI_BoxFlag_HotAnimation) {
            bg.r += box->hot_t * 0.15f;
            bg.g += box->hot_t * 0.15f;
            bg.b += box->hot_t * 0.15f;
        }
        if (box->flags & UI_BoxFlag_ActiveAnimation) {
            bg.r -= box->active_t * 0.1f;
            bg.g -= box->active_t * 0.1f;
            bg.b -= box->active_t * 0.1f;
        }

        HBRUSH brush = CreateSolidBrush(V4ToRGB(bg));
        FillRect(hdc, &r, brush);
        DeleteObject(brush);
    }

    if (box->flags & UI_BoxFlag_DrawBorder) {
        HBRUSH brush = CreateSolidBrush(V4ToRGB(box->border_color));
        FrameRect(hdc, &r, brush);
        DeleteObject(brush);
    }

    if ((box->flags & UI_BoxFlag_DrawText) && box->string.size > 0) {
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, V4ToRGB(box->text_color));
        DrawTextA(hdc, (LPCSTR)box->string.str, (int)box->string.size, &r,
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    for (UI_Box *child = box->first; child != 0; child = child->next) {
        Win32RenderUIBox(hdc, child);
    }
}

//=============================================================================
// WIN32 PLATFORM LAYER
//=============================================================================

static B32 global_running = 1;

LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            global_running = 0;
            PostQuitMessage(0);
            return 0;
        } break;
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = Win32WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "UIGroveExampleClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0, wc.lpszClassName, "UI Core Win32 Example",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    UI_Init();

    LARGE_INTEGER perf_freq;
    QueryPerformanceFrequency(&perf_freq);
    LARGE_INTEGER last_counter;
    QueryPerformanceCounter(&last_counter);

    B32 last_mouse_down = 0;
    int click_counter = 0;
    char counter_text[64] = "Clicks: 0";

    while (global_running) {
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        LARGE_INTEGER current_counter;
        QueryPerformanceCounter(&current_counter);
        F32 dt = (F32)(current_counter.QuadPart - last_counter.QuadPart) / (F32)perf_freq.QuadPart;
        last_counter = current_counter;

        POINT mouse_pt;
        GetCursorPos(&mouse_pt);
        ScreenToClient(hwnd, &mouse_pt);
        V2 mouse_pos = { (F32)mouse_pt.x, (F32)mouse_pt.y };

        B32 mouse_down = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
        B32 mouse_pressed = mouse_down && !last_mouse_down;
        B32 mouse_released = !mouse_down && last_mouse_down;
        last_mouse_down = mouse_down;

        RECT client_rect;
        GetClientRect(hwnd, &client_rect);
        F32 window_w = (F32)(client_rect.right - client_rect.left);
        F32 window_h = (F32)(client_rect.bottom - client_rect.top);

        //---------------------------------------------------------------------
        // UI BUILD PHASE
        //---------------------------------------------------------------------
        UI_BeginBuild(dt, mouse_pos, mouse_down, mouse_pressed, mouse_released);

        UI_Width(UI_Pixels(window_w, 1.0f))
        UI_Height(UI_Pixels(window_h, 1.0f))
        {
            UI_Box *container = UI_BoxMake(UI_BoxFlag_DrawBackground, Str8Lit("MainContainer"));
            container->bg_color = (V4){0.15f, 0.15f, 0.15f, 1.0f};

            UI_Parent(container)
            UI_ChildLayoutAxis(Axis2_Y)
            {
                UI_Width(UI_Pixels(200.0f, 1.0f))
                UI_Height(UI_Pixels(40.0f, 1.0f))
                UI_BgColor(((V4){0.3f, 0.3f, 0.4f, 1.0f}))
                {
                    // Push down some padding
                    UI_BoxMake(0, Str8Lit("Pad1"))->pref_size[Axis2_Y] = UI_Pixels(20.0f, 1.0f);

                    if (UI_Button(Str8Lit("Increment Counter")).clicked) {
                        click_counter++;
                        snprintf(counter_text, sizeof(counter_text), "Clicks: %d", click_counter);
                    }

                    UI_BoxMake(0, Str8Lit("Pad2"))->pref_size[Axis2_Y] = UI_Pixels(10.0f, 1.0f);
                    
                    UI_BgColor(((V4){0.2f, 0.5f, 0.3f, 1.0f}))
                    {
                        if (UI_Button(Str8Lit("Reset")).clicked) {
                            click_counter = 0;
                            snprintf(counter_text, sizeof(counter_text), "Clicks: %d", click_counter);
                        }
                    }

                    UI_BoxMake(0, Str8Lit("Pad3"))->pref_size[Axis2_Y] = UI_Pixels(20.0f, 1.0f);

                    UI_Width(UI_Pixels(200.0f, 1.0f))
                    UI_Height(UI_Pixels(30.0f, 1.0f))
                    UI_BgColor(((V4){0.2f, 0.2f, 0.2f, 1.0f}))
                    {
                        UI_Box *label_box = UI_BoxMake(UI_BoxFlag_DrawBackground | UI_BoxFlag_DrawBorder | UI_BoxFlag_DrawText,
                                                       (String8){(U8*)counter_text, strlen(counter_text)});
                        label_box->border_color = (V4){0.5f, 0.5f, 0.5f, 1.0f};
                    }
                }
            }
        }

        UI_EndBuild();

        //---------------------------------------------------------------------
        // RENDER PHASE (Double Buffered GDI)
        //---------------------------------------------------------------------
        HDC hdc = GetDC(hwnd);
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP memBitmap = CreateCompatibleBitmap(hdc, client_rect.right, client_rect.bottom);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, memBitmap);

        // Render UI Tree
        Win32RenderUIBox(memDC, ui_state->root);

        // Blit to screen
        BitBlt(hdc, 0, 0, client_rect.right, client_rect.bottom, memDC, 0, 0, SRCCOPY);

        SelectObject(memDC, oldBitmap);
        DeleteObject(memBitmap);
        DeleteDC(memDC);
        ReleaseDC(hwnd, hdc);

        Sleep(1); // Yield CPU
    }

    return 0;
}
