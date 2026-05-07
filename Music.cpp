#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "winmm.lib")

int main() {
    // --- Add your songs here ---
    std::vector<std::string> songs = {
        "songs/song1.wav",
        "songs/song2.wav",
        "songs/song3.wav"
    };

    std::vector<std::string> songNames = {
        "Song 1 - Artist A",
        "Song 2 - Artist B",
        "Song 3 - Artist C"
    };

    int choice = -1;

    while (true) {
        // Display menu
        std::cout << "\n===== MUSIC PLAYER =====\n";
        for (int i = 0; i < songs.size(); i++) {
            std::cout << i + 1 << ". " << songNames[i] << "\n";
        }
        std::cout << "0. Exit\n";
        std::cout << "========================\n";
        std::cout << "Choose a song: ";
        std::cin >> choice;

        // Exit
        if (choice == 0) {
            PlaySound(NULL, NULL, 0); // Stop any playing sound
            std::cout << "Goodbye!\n";
            break;
        }

        // Validate input
        if (choice < 1 || choice > songs.size()) {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        // Stop previous song and play selected
        PlaySound(NULL, NULL, 0);
        std::cout << "Now playing: " << songNames[choice - 1] << "\n";
        std::cout << "Press Enter to stop and go back to menu...\n";

        // Play async so we can wait for input
        PlaySound(
            TEXT(songs[choice - 1].c_str()),
            NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP
        );

        std::cin.ignore();
        std::cin.get(); // Wait for Enter

        PlaySound(NULL, NULL, 0); // Stop song
    }

    return 0;
}
