#include <Windows.h>
#include <wingdi.h>

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    BITMAPINFO  Info;
    void        *Memory;
    int         Width;
    int         Height;
    int         Pitch;
    int         BytesPerPixel;
} win32_offset_buffer;

static bool GlobalRunning;
static win32_offset_buffer GlobalBackbuffer;

typedef struct {
    int         Width;
    int         Height;
} win32_window_dimension;

win32_window_dimension Win32GetWindowDimension(HWND Window) {
    win32_window_dimension Result;
    
    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Result.Width = ClientRect.right    - ClientRect.left;
    Result.Height = ClientRect.bottom   - ClientRect.top;
    
    return Result;
}

static int RenderGrandient(
    win32_offset_buffer Buffer, 
    int BlueOffset, 
    int GreenOffset
) {
    uint8_t *Row = (uint8_t *)Buffer.Memory;
    
    for (int Y = 0; Y < Buffer.Height; ++Y) {
        uint32_t *Pixel = (uint32_t *)Row;
        
        for (int X = 0; X < Buffer.Width; ++X) {
            uint8_t Blue = (X + BlueOffset);
            uint8_t Green = (Y + GreenOffset);
            
            *Pixel++ = ((Green << 8)|Blue);
        }
        
        Row += Buffer.Pitch;
    }
}

static void Win32ResizeDIBSection(win32_offset_buffer *Buffer, int Width, int Height) {
    if (Buffer->Memory) VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
    
    Buffer->Width = Width;
    Buffer->Height = Height;
    Buffer->BytesPerPixel = 4;
        
    Buffer->Info.bmiHeader.biSize          = sizeof(Buffer->Info.bmiHeader);
    Buffer->Info.bmiHeader.biWidth         = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight        = -Buffer->Height;
    Buffer->Info.bmiHeader.biPlanes        = 1;
    Buffer->Info.bmiHeader.biBitCount      = 32;
    Buffer->Info.bmiHeader.biCompression   = BI_RGB;
    
    int BitmapMemorySize = (Buffer->Width * Buffer->Height) * Buffer->BytesPerPixel;
    Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
    
    Buffer->Pitch = Width * Buffer->BytesPerPixel;
}

static void Win32DisplayBufferInWindow(
    HDC DeviceContext, 
    int WindowWidth, int WindowHeight,
    win32_offset_buffer Buffer,
    int X, int Y, int Width, int Height
) {
    
    StretchDIBits(
        DeviceContext,
        0, 0, WindowWidth, WindowHeight,
        0, 0, Buffer.Width, Buffer.Height,
        Buffer.Memory,
        &Buffer.Info,
        DIB_RGB_COLORS, SRCCOPY
    );
}

LRESULT CALLBACK Win32MainWindowCallback(
  HWND Window,
  UINT Message,
  WPARAM WParam,
  LPARAM LParam
) {
    LRESULT Result = 0;
    
    switch(Message) {
        case WM_SIZE: {
            win32_window_dimension Dimension = Win32GetWindowDimension(Window);
            Win32ResizeDIBSection(
                &GlobalBackbuffer, 
                Dimension.Width, Dimension.Height
            );
        } break;
        case WM_DESTROY: {
            GlobalRunning = false;
        } break;
        case WM_CLOSE: {
            GlobalRunning = false;
        } break;
        case WM_KEYDOWN: {
            if (VK_F11 == WParam) {
                DWORD WindowStyle = GetWindowLong(Window, GWL_STYLE);
                DWORD WindowStyleRemove = WS_CAPTION|WS_SYSMENU|
                                          WS_MINIMIZEBOX|WS_MAXIMIZEBOX;
                DWORD WindowNewStyle = WindowStyle & ~WindowStyleRemove;
                SetWindowLong(Window, GWL_STYLE, WindowNewStyle);

                int WinStyle = GetWindowLongA(Window, GWL_STYLE);
                HDC hDC = GetWindowDC(NULL);
                SetWindowPos(
                    Window, 
                    NULL, 0, 0, 
                    GetDeviceCaps(hDC, HORZRES), GetDeviceCaps(hDC, VERTRES), 
                    SWP_FRAMECHANGED
                );
            }
            if (VK_ESCAPE == WParam) GlobalRunning = false;
        } break;
        case WM_ACTIVATEAPP: {
        } break;
        case WM_PAINT: {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            
            int X = Paint.rcPaint.left;
            int Y = Paint.rcPaint.top;
            int Width = Paint.rcPaint.right - Paint.rcPaint.left;
            int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
            PatBlt(DeviceContext, X, Y, Width, Height, BLACKNESS);
            
            win32_window_dimension Dimension = Win32GetWindowDimension(Window);
            
            Win32DisplayBufferInWindow(
                DeviceContext, 
                Dimension.Width, Dimension.Height, 
                GlobalBackbuffer,
                X, Y, Width, Height
            );
            EndPaint(Window, &Paint);
        } break;
        default: {
            Result = DefWindowProcA(Window, Message, WParam, LParam);
        } break;
    }
    
    return Result;
}

int CALLBACK WinMain(
    HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR     CmdLine,
    int       ShowCmd
) {
    WNDCLASSA WinClass = {0};
    WinClass.style = CS_HREDRAW|CS_VREDRAW;
    WinClass.lpfnWndProc = Win32MainWindowCallback;
    // WinClass.cbClsExtra;
    // WinClass.cbWndExtra;
    WinClass.hInstance = Instance;
    WinClass.hIcon;
    WinClass.hCursor;
    // WinClass.hbrBackground;
    // WinClass.lpszMenuName;
    WinClass.lpszClassName = "SpectrumV";
    
    if (RegisterClassA(&WinClass)) {
        HWND Window = CreateWindowExA(
            0,
            WinClass.lpszClassName,
            WinClass.lpszClassName,
            WS_EX_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            Instance,
            0
        );
        
        if (Window) {
            GlobalRunning = true;
            int XOffset = 0;
            int YOffset = 0;
            while (GlobalRunning) {
                MSG Message;

                while (PeekMessageA(&Message, 0, 0, 0, PM_REMOVE)) {
                    if (Message.message == WM_CLOSE) GlobalRunning = false;
                    
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
                
                //for(DWORD ControllerIndex = 0; ControllerIndex < XUSER_MAX_COUNT; ++ControllerIndex) {
                //    XINPUT_STATE ControllerState;
                //    if (XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS) {
                //    } else {
                //    }
                //}
                
                RenderGrandient(GlobalBackbuffer, XOffset, YOffset);
                
                HDC DeviceContext = GetDC(Window);
                win32_window_dimension Dimension = Win32GetWindowDimension(Window);
                Win32DisplayBufferInWindow(
                    DeviceContext, 
                    Dimension.Width, Dimension.Height,
                    GlobalBackbuffer,
                    0, 0, Dimension.Width, Dimension.Height
                );
                ReleaseDC(Window, DeviceContext);
                
                XOffset += 1;
                YOffset += 2;
            }
        } else {
        }
    } else {
    }
}