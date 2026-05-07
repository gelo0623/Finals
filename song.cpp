#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <vector>
#pragma comment(lib, "winmm.lib")

using namespace std;

int main() {
    vector<string> songs = {
        "songs/Fallen.wav",
        "songs/Lifetime.wav",
        "songs/Multo.wav"
    };

    vector<string> songNames = {
        "Fallen - Lola Amour",
        "Lifetime - Ben&Ben",
        "Multo - Cup of Joe"
    };

    int choice = -1;

    while (true) {
        cout << "\n===== MUSIC PLAYER =====\n";
        for (int i = 0; i < (int)songs.size(); i++) {
            cout << i + 1 << ". " << songNames[i] << "\n";
        }
        cout << "0. Exit\n";
        cout << "========================\n";
        cout << "Choose a song: ";
        cin >> choice;

        if (choice == 0) {
            PlaySound(NULL, NULL, 0);
            cout << "Goodbye!\n";
            break;
        }

        if (choice < 1 || choice > (int)songs.size()) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        PlaySound(NULL, NULL, 0);
        cout << "Now playing: " << songNames[choice - 1] << "\n";
        cout << "Press Enter to stop and go back to menu...\n";

        PlaySound(
            TEXT(songs[choice - 1].c_str()),
            NULL,
            SND_FILENAME | SND_ASYNC | SND_LOOP
        );

        cin.ignore();
        cin.get();

        PlaySound(NULL, NULL, 0);
    }

    return 0;
}