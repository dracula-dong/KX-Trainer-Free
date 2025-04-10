#include "hack_gui.h"
#include "hack.h"
#include "constants.h"
#include <iostream>
#include <thread>

using namespace Constants::Hotkeys;

HackGUI::HackGUI(Hack& hack) : m_hack(hack)
{
    m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void HackGUI::start()
{
    printWelcomeMessage();
    displayInfo();
}

void HackGUI::run() {
    while (true) {
        m_hack.refreshAddresses();
        checkFog();
        checkObjectClipping();
        checkFullStrafe();
        checkSprint();
        checkSuperSprint();
        checkPositionKeys();
        checkInvisibility();
        checkWallClimb();
        checkClipping();
        checkFly();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // To avoid high CPU usage
    }
}

void HackGUI::checkFog() {
    if (GetAsyncKeyState(KEY_NO_FOG) & 1) {
        m_fogEnabled = !m_fogEnabled;
        m_hack.toggleFog(m_fogEnabled);
        std::cout << "\nNo Fog: " << (m_fogEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkObjectClipping() {
    if (GetAsyncKeyState(KEY_OBJECT_CLIPPING) & 1) {
        m_objectClippingEnabled = !m_objectClippingEnabled;
        m_hack.toggleObjectClipping(m_objectClippingEnabled);
        std::cout << "\nObject Clipping: " << (m_objectClippingEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkFullStrafe() {
    if (GetAsyncKeyState(KEY_FULL_STRAFE) & 1) {
        m_fullStrafeEnabled = !m_fullStrafeEnabled;
        m_hack.toggleFullStrafe(m_fullStrafeEnabled);
        std::cout << "\nFull Strafe: " << (m_fullStrafeEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkSprint() {
    if (GetAsyncKeyState(KEY_SPRINT) & 1) {
        m_sprintEnabled = !m_sprintEnabled;
        std::cout << "\nSprint: " << (m_sprintEnabled ? "Enabled" : "Disabled") << std::endl;
    }

    m_hack.handleSprint(m_sprintEnabled);
}

void HackGUI::checkSuperSprint() {
    bool superSprintKeyPressed = GetAsyncKeyState(KEY_SUPER_SPRINT);
    if (superSprintKeyPressed != m_superSprintEnabled) {
        m_superSprintEnabled = superSprintKeyPressed;
        m_hack.handleSuperSprint(m_superSprintEnabled);
        std::cout << "\nSuper Sprint: " << (m_superSprintEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkPositionKeys() {
    if (GetAsyncKeyState(KEY_SAVEPOS) & 1) {
        m_hack.savePosition();
        std::cout << "\nPosition Saved." << std::endl;
    }
    if (GetAsyncKeyState(KEY_LOADPOS) & 1) {
        m_hack.loadPosition();
        std::cout << "\nPosition Loaded." << std::endl;
    }
}

void HackGUI::checkInvisibility() {
    if (GetAsyncKeyState(KEY_INVISIBILITY) & 1) {
        m_invisibilityEnabled = !m_invisibilityEnabled;
        m_hack.toggleInvisibility(m_invisibilityEnabled);
        std::cout << "\nInvisibility: " << (m_invisibilityEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkWallClimb() {
    if (GetAsyncKeyState(KEY_WALLCLIMB) & 1) {
        m_wallClimbEnabled = !m_wallClimbEnabled;
        m_hack.toggleWallClimb(m_wallClimbEnabled);
        std::cout << "\nWall Climb: " << (m_wallClimbEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkClipping() {
    if (GetAsyncKeyState(KEY_CLIPPING) & 1) {
        m_clippingEnabled = !m_clippingEnabled;
        m_hack.toggleClipping(m_clippingEnabled);
        std::cout << "\nClipping: " << (m_clippingEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::checkFly() {
    bool flyKeyPressed = GetAsyncKeyState(KEY_FLY);
    if (flyKeyPressed != m_flyEnabled) {
        m_flyEnabled = flyKeyPressed;
        m_hack.handleFly(m_flyEnabled);
        std::cout << "\nFly: " << (m_flyEnabled ? "Enabled" : "Disabled") << std::endl;
    }
}

void HackGUI::displayInfo()
{
    std::cout << "[Hotkeys]\n"
        << "NUMPAD1 - Save Position\n"
        << "NUMPAD2 - Load Position\n"
        << "NUMPAD3 - Invisibility (for mobs)\n"
        << "NUMPAD4 - Wall Climb\n"
        << "NUMPAD5 - Clipping\n"
        << "NUMPAD6 - Object Clipping\n"
        << "NUMPAD7 - Full Strafe\n"
        << "NUMPAD8 - Toggle No Fog\n"
        << "NUMPAD+ - Super Sprint (hold)\n"
        << "CTRL - Fly (hold)\n"
        << "SHIFT - Sprint\n"
        << "\n[Logs]\n";
}

void HackGUI::printWelcomeMessage()
{
    system("cls");

    // Header
    std::cout << "===================================\n";
    setConsoleColor(BLUE);
    std::cout << "      KX Trainer by Krixx\n";
    setConsoleColor(DEFAULT);
    std::cout << "===================================\n\n";

    // GitHub Repo
    std::cout << "GitHub Repo: ";
    setConsoleColor(BLUE);
    std::cout << "https://github.com/Krixx1337/KX-Trainer-Free";
    setConsoleColor(DEFAULT);
    std::cout << "\n\n";

    // Paid Version
    std::cout << "If you like the trainer, consider upgrading to the paid version for more features and support!\n";
    std::cout << "Visit: ";
    setConsoleColor(BLUE);
    std::cout << "https://kxtools.xyz";
    setConsoleColor(DEFAULT);
    std::cout << "\n\n";

    // Status Section
    std::cout << "[STATUS] ";
    setConsoleColor(GREEN);
    std::cout << "Gw2-64.exe process found!";
    setConsoleColor(DEFAULT);
    std::cout << "\n\n";
}

void HackGUI::setConsoleColor(int color)
{
    SetConsoleTextAttribute(m_consoleHandle, color);
}
