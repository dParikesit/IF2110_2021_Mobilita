#include "command.h"
#include "../../system/gamemanager/gamemanager.h"

void showMainMenu() {
    printf("1. NEW_GAME -> Untuk memulai permainan dengan membuat state game baru\n");
    printf("2. EXIT -> Untuk menutup program\n");
    printf("3. LOAD_GAME -> Untuk memuat state game sebelumnya\n");  
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
} 
// Show available command list (HELP)

void invalidCommandMsg() {
    printf("Masukkan command anda tidak valid\n");
}

CommandType parseCommand() {
    char* command;
    int i, ret;

    printf("ENTER COMMAND: ");
    command = readLine();

    if (!(_gm.isPlaying)) {
        i=NEW_GAME;
        while (i<=LOAD_GAME && command != stringCommand[i]) {
            i++;
        }
        if (i > LOAD_GAME) {
            ret = INVALID;
        } else {
            // runCommand(i);
            ret = i;
        }
    } else {
        i=MOVE;
        while (i<= RETURN && command != stringCommand[i]) {
            i++;
        }
        if (i > RETURN) {
            ret = INVALID;
        } else {
            ret = i;
        }
    }
    return ret;
}
// Read and parse command from stdin.

// DELETE THIS LATER
void doMovePlayer(){}
void doPickUp(){}
void doDropOff(){}
void displayToDo(){}
void displayInProgress(){}
void useGadget(){}
void saveGame(){}
void applyAbility(){}


boolean isCommandAvailable(CommandType cmdType) {
    // boolean res;
    
    // switch (cmdType) {
    //     case NEW_GAME:
    //         res = !_gm.isPlaying;
    //         break;
    //     case EXIT:
    //         res = _gm.isPlaying;
    //         break;
    //     case LOAD_GAME:
    //         res = !_gm.isPlaying;
    //         break;
    //     case PICK_UP:
    //         res = isThereAnyPickUpItem();
    //         break;
    //     case DROP_OFF:
    //         res = isThereAnyDropOffItem();
    //         break;
    //     case BUY:
    //         res = isInHQ();
    //         break;
    //     case SAVE_GAME:
    //         res = _gm.isPlaying;
    //         break;
    //     case RETURN:
    //         res = hasReturnAbility();
    //         break;
    //     default:
    //         res = true;
    //         break;
    // }
    // return res;
    return true;
}
// Check if command can be run

void runCommand(CommandType cmdType) {
    switch (cmdType) {
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
            useGadget();
            break;
        case HELP:
            showListCommand();
            break;
        case SAVE_GAME:
            saveGame();
            break;
        case RETURN:
            applyAbility();
            break;
        default:
            printf("wrong input\n");
            break;
    }
} 
// Run command