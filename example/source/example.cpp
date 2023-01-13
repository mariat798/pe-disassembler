/// example.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

#define NO_TYPES
#include <pe disassembler.hpp>
#pragma comment(lib, "pe disassembler.lib")

#pragma comment(lib, "d3d9.lib")
#include <d3d9.h>

#define IMGUI_IMPLEMENTATION
#include <misc/single_file/imgui_single_file.h>
#include <backends/imgui_impl_dx9.h>
#include <backends/imgui_impl_dx9.cpp>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_win32.cpp>

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

std::vector<char> read_file()
{
    std::ifstream file(R"(C:\Users\cole\Desktop\messagebox.dll)", std::ios::binary);
    std::vector<char> out;

    file.seekg(0, std::ios::end);

    auto size = file.tellg();

    file.seekg(0);
    out.resize(size);
    file.read(&out[0], size);

    return out;
}

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)

{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);

    
   
}
void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}
void main()
{
    auto data = read_file();

    auto mb = pe(&data[0], data.size());
    auto dos = mb.get_dos();
    auto nt = mb.get_nt();

    auto imports = nt.get_directory<image_import_list>();
    auto exports = nt.get_directory<image_export>();
    auto relocs = nt.get_directory<image_base_relocations>();

    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"PE Dissassembler", NULL };
    RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"PE Dissasembler", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        std::time_t time = nt->FileHeader.TimeDateStamp;

        ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        {
            ImGui::SetWindowPos(ImVec2(0, 0));
            ImGui::SetWindowSize(ImVec2(1260, 800));

            if (ImGui::CollapsingHeader("NT Header"))
            {
                ImGui::Text(("Image base: " + std::to_string(nt->OptionalHeader.ImageBase)).c_str());
                ImGui::Text(("Image size: " + std::to_string(nt->OptionalHeader.SizeOfImage)).c_str());
                ImGui::Text(("Image base: " + std::string(std::asctime(std::localtime(&time)))).c_str());
                ImGui::Text(("Entry point: " + std::to_string(nt->OptionalHeader.AddressOfEntryPoint)).c_str());
            }

            if (ImGui::CollapsingHeader("Sections"))
            {
                ImGui::BeginGroup();
                ImGui::Indent(16.f);

                for (auto s : nt.get_sections())
                    if (ImGui::CollapsingHeader(reinterpret_cast<char*>(s->Name)))
                    {
                        ImGui::Text(("Size: " + std::to_string(s->SizeOfRawData)).c_str());
                        ImGui::Text(("RVA: " + std::to_string(s->VirtualAddress)).c_str());
                    }

                ImGui::EndGroup();
            }

            if (ImGui::CollapsingHeader("Exports"))
                for (auto e : exports)
                    ImGui::Text((std::string(e.first) + " at RVA " + std::to_string(e.second)).c_str());

            if (ImGui::CollapsingHeader("Imports"))
            {
                ImGui::BeginGroup();
                ImGui::Indent(16.f);

                for (auto i : imports)
                    if (ImGui::CollapsingHeader(i.name()))
                        for (auto t : i)
                            ImGui::Text(t.name());

                ImGui::EndGroup();
            }

            if (ImGui::CollapsingHeader("Relocation tables"))
                for (auto reloc : relocs)
                    ImGui::Text((std::to_string(reloc->VirtualAddress) + " with " + std::to_string(reloc.entries()) + " entries").c_str());
        }
        ImGui::End();

        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
    }
}
