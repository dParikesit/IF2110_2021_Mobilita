#include "command.h"
#include "../../include/wrapper.h"
#include "../../object/ability/ability.h"
#include "../gameplay/gameplay.h"

void showMainMenu() {
    printf("1. NEW_GAME -> Untuk memulai permainan dengan membuat state game baru\n");
    printf("2. EXIT -> Untuk menutup program\n");
    printf("3. LOAD_GAME -> Untuk memuat state game sebelumnya\n");
    printf("4. HELP -> menampilkan list command yang dapat dijalankan\n");
}
void showListCommand() {
    printf("1. MOVE -> Untuk berpindah ke lokasi selanjutnya\n");
    printf("2. PICK_UP -> Untuk mengambil item dilokasi sekarang\n");
    printf("3. DROP_OFF -> Untuk mengantarkan item ke lokasi\n");
    printf("4. MAP -> Untuk memunculkan peta\n");
    printf("5. TO_DO -> Untuk menampilkan pesanan yang masuk ke To Do List\n");
    printf("6. IN_PROGRESS -> Untuk menampilkan pesanan yang sedang dikerjakan\n");
    printf("7. BUY -> Untuk menampilkan gadget yang dapat dibeli lalu membelinya\n");
    printf("8. INVENTORY -> Untuk melihat gadget yang dimiliki dan menggunakannya\n");
    printf("9. HELP -> Untuk mengeluarkan list command dan kegunaannya\n");
    printf("10. SAVE_GAME -> Untuk melakukan save state dari permainan yang sedang dijalankan\n");
    printf("11. RETURN -> Untuk mengembalikan item di tumpukan teratas pada tas kembali ke lokasi pick up jika Mobita memiliki ability Return To Sender\n");
    printf("12. EXIT -> Untuk menutup program\n");
} 
// Show available command list (HELP)

void invalidCommandMsg() {
    printf("Masukkan command anda tidak valid\n");
}

CommandType parseCommand() {
    char* command;
    int i;
    CommandType ret;

    printf("\nENTER COMMAND: ");
    command = readLine();
    i = NEW_GAME;
    while (i <= RETURN && !isEqualString(command, stringCommand[i]))
        i++;
    if (i > RETURN) {
        ret = INVALID;
    } else {
        ret = (CommandType)i;
    }
    return ret;
}

boolean isCommandAvailable(CommandType cmdType) {
    boolean res;
    char* err = "None";
    
    switch (cmdType) {
        case NEW_GAME:
        case LOAD_GAME:
            res = !GAME.isPlaying;
            break;
        case BUY:
            res = isInHQ();
            if (!res)
                err = "Mobita tidak berada di HQ\n";
            break;
        case RETURN:
            res = GSTATS.returnToSender > 0;
            if (!res)
                err = "Mobita tidak punya ability Return to Sender\n";
            break;
        case INVALID:
            printf("Command masukan tidak valid.\n");
            res = false;
            break;
        default:
            res = true;
            break;
    }
    if (cmdType > LOAD_GAME) {
        if (GAME.isPlaying)  {
            if (!res && cmdType < INVALID)
                printf("%s\n", err);
        } else if (cmdType < INVALID) {
            printf("Kamu belum memulai permainan!\n");
            res = false;
        }
    } else if (cmdType != EXIT && cmdType != HELP) {
        if (GAME.isPlaying) {
            printf("Kamu sudah memulai permainan!\n");
            res = false;
        }
    }
    return res;
}
// Check if command can be run

void runCommand(CommandType cmdType) {
    switch (cmdType) {
        case NEW_GAME:
            newGame();
            break;
        case EXIT:
            exitGame();
            break;
        case LOAD_GAME:
            loadGame();
            break;
        case MOVE:
            doMovePlayer();
            break;
        case PICK_UP:
            doPickUp();
            break;
        case DROP_OFF:
            doDropOff();
            break;
        case MAP:
            displayMap();
            break;
        case TO_DO:
            displayToDo();
            break;
        case IN_PROGRESS:
            displayInProgress();
            break;
        case BUY:
            buyGadget();
            break;
        case INVENTORY:
            showAndUseGadget();
            break;
        case HELP:
            if (GAME.isPlaying) {
                showListCommand();
            } else {
                showMainMenu();
            }
            break;
        case SAVE_GAME:
            saveGame();
            break;
        case RETURN:
            applyAbility(RETURN_TO_SENDER);
            break;
    }
} 
// Run command