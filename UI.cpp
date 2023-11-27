#include "UI.h"
#include <string>

using namespace std;;

void UI::mainMenu() {
    cout << R"(
     __      __       .__                                  __          
    /  \    /  \ ____ |  |   ____  ____   _____   ____   _/  |_  ____  
    \   \/\/   // __ \|  | _/ ___\/  _ \ /     \_/ __ \  \   __\/  _ \ 
     \        /\  ___/|  |_\  \__(  <_> )  Y Y  \  ___/   |  | (  <_> )
      \__/\  /  \___  >____/\___  >____/|__|_|  /\___  >  |__|  \____/ 
           \/       \/          \/            \/     \/   )"
        << endl;

    cout << R"(
       _____  .__                                                                  ._.
      /     \ |__| ____   ____   ________  _  __ ____   ____ ______   ___________  | |
     /  \ /  \|  |/    \_/ __ \ /  ___/\ \/ \/ // __ \_/ __ \\____ \_/ __ \_  __ \ | |
    /    Y    \  |   |  \  ___/ \___ \  \     /\  ___/\  ___/|  |_> >  ___/|  | \/  \|
    \____|__  /__|___|  /\___  >____  >  \/\_/  \___  >\___  >   __/ \___  >__|     __
            \/        \/     \/     \/              \/     \/|__|        \/         \/
    )" << "\n\n\n";

    cout << "1: Play \n";
    cout << "2: Instructions \n";
    cout << "3: Quit \n";
}

void UI::instructions() {
    cout << R"(
    .__                      __                  .__                
    |  |__   ______  _  __ _/  |_  ____   ______ |  | _____  ___.__.
    |  |  \ /  _ \ \/ \/ / \   __\/  _ \  \____ \|  | \__  \<   |  |
    |   Y  (  <_> )     /   |  | (  <_> ) |  |_> >  |__/ __ \\___  |
    |___|  /\____/ \/\_/    |__|  \____/  |   __/|____(____  / ____|
         \/                               |__|             \/\/ 
  )" << endl;
    cout << "A minesweeper board will be shown as the following: " << endl;
    cout << R"(        
        1 2 3 4 5 6 7 8

     1  ? ? ? ? ? ? ? ?
     2  ? ? f f f ? ? ?
     3  ? ? 2 3 2 ? ? ?
     4  ? ? 1 0 1 ? ? ?
     5  ? ? 2 1 2 ? ? ?
     6  ? ? ? ? ? ? ? ?
     7  ? ? ? ? ? ? ? ?
     8  ? ? ? ? ? ? ? ?
    )" << endl;
    cout << "To select a square type the x and y coordinates as the following x y"
        << endl;
    cout << "For example if you wanted to select a square in the middle type 5 5"
        << endl
        << endl;
    cout << "When you reveal a square it will either have a mine or a number"
        << endl;
    cout << "If it has a mine you lose the game" << endl;
    cout << "If it has a number you can use that information to find nearby mines"
        << endl;
    cout << "A number will show the position of nearby mines that are adjancet "
        "to that square"
        << endl;
    cout << "This means there could be a mine directly to the left, right, top, "
        "bottom, and diagonal to that square"
        << endl;
    cout << "If you think you know the position of a mine type flag x, y in "
        "order to keep track of mine positions"
        << endl;
    cout << "Below is an example gameboard showing this: " << endl;
    cout << R"(
        1 2 3 4 5 6 7 8

     1  ? ? ? ? ? ? ? ?
     2  ? ? f f f ? ? ?
     3  ? ? 2 3 2 ? ? ?
     4  ? ? 1 0 1 ? ? ?
     5  ? ? 2 1 2 ? ? ?
     6  ? ? ? ? ? ? ? ?
     7  ? ? ? ? ? ? ? ?
     8  ? ? ? ? ? ? ? ?
   )" << endl;

    cout << "1: Return To Main Menu" << endl;
    cout << "2: Difficulty Select" << endl;
}

void UI::difficultySelect() {
    cout << R"(
    _________      .__                 __    ________  .__  _____  _____.__             .__   __          
   /   _____/ ____ |  |   ____   _____/  |_  \______ \ |__|/ ____\/ ____\__| ____  __ __|  |_/  |_ ___.__.
   \_____  \_/ __ \|  | _/ __ \_/ ___\   __\  |    |  \|  \   __\\   __\|  |/ ___\|  |  \  |\   __<   |  |
   /        \  ___/|  |_\  ___/\  \___|  |    |    `   \  ||  |   |  |  |  \  \___|  |  /  |_|  |  \___  |
  /_______  /\___  >____/\___  >\___  >__|   /_______  /__||__|   |__|  |__|\___  >____/|____/__|  / ____|
          \/     \/          \/     \/               \/                         \/                 \/ 
  )" << endl;

    cout << "1: Easy" << endl;
    cout << "2: Medium" << endl;
    cout << "3: Hard" << endl;
    cout << "4: Custom" << endl;
    cout << "5: Back to Menu" << endl;
}

void UI::createCustomDifficulty() {
    cout << R"(
    _________                __                  
    \_   ___ \ __ __  ______/  |_  ____   _____  
    /    \  \/|  |  \/  ___|   __\/  _ \ /     \ 
    \     \___|  |  /\___ \ |  | (  <_> )  Y Y  \
     \______  /____//____  >|__|  \____/|__|_|  /
            \/           \/                   \/ )" << endl << endl;
    cout << "Enter the number of rows, cols then mines in the Custom Board" << endl;
    cout << "Seperate each value by a space" << endl;
    cout << "Example: 24 24 100" << endl;
}

void UI::loseScreen() {
    cout << R"( 
  _____.___.                 ___ ___ .__  __        _____        _____  .__               
  \__  |   | ____  __ __    /   |   \|__|/  |_     /  _  \      /     \ |__| ____   ____  
  /   |   |/  _ \|  |  \  /    ~    \  \   __\   /  /_\  \    /  \ /  \|  |/    \_/ __ \ 
  \____   (  <_> )  |  /  \    Y    /  ||  |    /    |    \  /    Y    \  |   |  \  ___/ 
  / ______|\____/|____/    \___|_  /|__||__|    \____|__  /  \____|__  /__|___|  /\___  >
  \/                             \/                     \/           \/        \/     \/ 
  )" << endl;

    cout << "1: Try Again" << endl;
    cout << "2: Back to menu" << endl;
}

void UI::winScreen() {
    cout << R"(
    _________                                     __        .__          __  .__                      
    \_   ___ \  ____   ____    ________________ _/  |_ __ __|  | _____ _/  |_|__| ____   ____   ______
    /    \  \/ /  _ \ /    \  / ___\_  __ \__  \\   __\  |  \  | \__  \\   __\  |/  _ \ /    \ /  ___/
    \     \___(  <_> )   |  \/ /_/  >  | \// __ \|  | |  |  /  |__/ __ \|  | |  (  <_> )   |       \\___ \ 
     \______  /\____/|___|  /\___  /|__|  (____  /__| |____/|____(____  /__| |__|\____/|___|  /____  >
            \/            \//_____/            \/                     \/                    \/     \/ 
  )";
    cout << R"(
                        _____.___.               __      __.__         ._.
                        \__  |   | ____  __ __  /  \    /  \__| ____   | |
                         /   |   |/  _ \|  |  \ \   \/\/   /  |/    \  | |
                         \____   (  <_> )  |  /  \        /|  |   |  \  \|
                         / ______|\____/|____/    \__/\  / |__|___|  /  __
                         \/                            \/          \/   \/
  )" << endl;

    cout << "1: Play Again" << endl;
    cout << "2: Back to Menu" << endl;
}