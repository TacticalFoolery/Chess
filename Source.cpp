#include <iostream> 

#include <SFML/Graphics.hpp>  

#include <Windows.h>  

#include <vector> 



enum pieces { blkrook, blkknight, blkbishop, blkqueen, blkking, blkpawn, whtrook, whtknight, whtbishop, whtqueen, whtking, whtpawn };



class piece {

public:

    int pieceType;

    sf::Vector2f piecePosition;

    sf::Sprite pieceSprite;



    piece(int pie, sf::Vector2f piecePos, sf::Sprite spri)

        : pieceType(pie), piecePosition(piecePos), pieceSprite(spri) {

    }


};



int main() {



    // Hides background console window   

    HWND hWnd = GetConsoleWindow();

    ShowWindow(hWnd, SW_HIDE);



    // Creates the display window   

    unsigned int width = 640;

    unsigned int height = 360;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Chess");

    window->setFramerateLimit(60);



    // Loads textures   

    sf::Texture bg;

    sf::Texture pieces;

    pieces.loadFromFile("Img/figures.png");

    bg.loadFromFile("Img/board.png");



    // Creates board sprite   

    sf::Sprite board(bg);

    board.setScale({ 0.7f, 0.7f });

    board.setOrigin({ 252.f, 450.f });

    board.setPosition({ 320.f, 320.f });



    // The position of all the spaces   

    sf::Vector2f boardPositions[8][8] = {

         {{162.00f, 22.00f}, {204.00, 22.00f}, {243.00f,22.00f}, {282.00f,22.00f}, {320.00f, 22.00f}, {360.00f, 22.00f}, {400.00f, 22.00f}, {437.00f, 22.00f}},

         {{162.00f, 62.00f}, {204.00f, 62.00f}, {243.00f, 62.00f}, {282.00f,62.00f}, {320.00f, 62.00f}, {360.00f, 62.00f}, {400.00f, 62.00f}, {437.00f, 62.00f}},

         {{162.00f, 102.00f}, {204.00f, 102.00f}, {243.00f, 102.00f}, {282.00f, 102.00f}, {320.00f, 102.00f}, {360.00f, 102.00f}, {400.00f, 102.00f}, {437.00f, 102.00f}},

         {{162.00f, 142.00f}, {204.00f, 142.00f}, {243.00f, 142.00f}, {282.00f, 142.00f}, {320.00f, 142.00f}, {360.00f, 142.00f}, {400.00f, 142.00f}, {437.00f, 142.00f}},

         {{162.00f, 182.00f}, {204.00f, 182.00f}, {243.00f, 182.00f}, {282.00f, 182.00f}, {320.00f, 182.00f}, {360.00f, 182.00f}, {400.00f, 182.00f}, {437.00f, 182.00f}},

         {{162.00f, 218.00f}, {204.00f, 218.00f}, {243.00f, 218.00f}, {282.00f, 218.00f}, {320.00f, 218.00f}, {360.00f, 218.00f}, {400.00f, 218.00f}, {437.00f, 218.00f}},

         {{162.00f, 258.00f}, {204.00f, 258.00f}, {244.00f, 258.00f}, {284.00f, 258.00f}, {322.00f, 258.00f}, {360.00f, 258.00f}, {400.00f, 258.00f}, {442.00f, 258.00f}},

         {{162.00f, 298.00f}, {204.00f, 298.00f}, {243.00f, 298.00f}, {282.00f, 298.00f}, {320.00f, 298.00f}, {360.00f, 298.00f}, {400.00f, 298.00f}, {437.00f, 298.00f}}

    };



    //square object   

    sf::RectangleShape square(sf::Vector2f(55.f, 55.f));

    square.setScale({ 0.7f,0.7f });

    square.setPosition({ -1000.f, -1000.f });

    square.setFillColor(sf::Color::Transparent);

    square.setOutlineThickness(2.f);

    square.setOutlineColor(sf::Color::Yellow);





    //circle object   

    sf::CircleShape circle(10.f);

    circle.setOrigin({ -10.0f, -10.0f });

    circle.setFillColor(sf::Color::Yellow);

    circle.setPosition({ -1000.f, -1000.f });

    std::vector<sf::CircleShape> circles;

    sf::CircleShape check(10.f);

    check.setPosition({ -1000.f, -1000.f });



    sf::Font font("Img/Vogue.ttf");
    sf::Text whtwin(font, "White Wins!", 72);
    whtwin.setFillColor(sf::Color::White);
    whtwin.setPosition({ 100.f, 100.f });
    sf::Text blkwin(font, "Black Wins!", 72);
    blkwin.setFillColor(sf::Color::Black);
    blkwin.setPosition({ 100.f, 100.f });




    for (int i = 0; i < 27; i++)

    {

        circles.push_back(circle);

    
    }


    // Defines texture sections for each piece   

    sf::IntRect type[12];

    type[blkrook] = sf::IntRect({ {0, 0}, {55, 55} });

    type[blkknight] = sf::IntRect({ {60, 0}, {55, 55} });

    type[blkbishop] = sf::IntRect({ {115, 0}, {55, 55} });

    type[blkqueen] = sf::IntRect({ {170, 0}, {55, 55} });

    type[blkking] = sf::IntRect({ {225, 0}, {55, 55} });

    type[blkpawn] = sf::IntRect({ {285, 0}, {55, 55} });

    type[whtrook] = sf::IntRect({ {0, 58},{55, 55} });

    type[whtknight] = sf::IntRect({ {60, 58},{55, 55} });

    type[whtbishop] = sf::IntRect({ {115, 58},{55, 55} });

    type[whtqueen] = sf::IntRect({ {170,58},{55, 55} });

    type[whtking] = sf::IntRect({ {225, 58},{55, 55} });

    type[whtpawn] = sf::IntRect({ {285,58},{55, 55} });





    std::vector<piece> PieceVec;



    //displays black pieces and moves them into start position   

    for (int i = 1; i <= 16; i++) {

        sf::Sprite chess(pieces);

        chess.setScale({ 0.75f, 0.7f });

        if (i <= 8) {
            chess.setTextureRect(type[blkpawn]);

            chess.setPosition(boardPositions[1][i - 1]);

            PieceVec.emplace_back(blkpawn, chess.getPosition(), chess);

        }

        else if (i <= 10) {

            if (i == 9) {
                //sets sprites texture
                chess.setTextureRect(type[blkrook]);

                //sets the position of the piece
                chess.setPosition(boardPositions[0][0]);

                //places it into the class
                PieceVec.emplace_back(blkrook, chess.getPosition(), chess);

            }

            else

            {

                chess.setTextureRect(type[blkrook]);

                chess.setPosition(boardPositions[0][7]);

                PieceVec.emplace_back(blkrook, chess.getPosition(), chess);

            }

        }

        else if (i <= 12) {

            if (i == 11) {

                chess.setTextureRect(type[blkbishop]);

                chess.setPosition(boardPositions[0][2]);

                PieceVec.emplace_back(blkbishop, chess.getPosition(), chess);

            }

            else

            {

                chess.setTextureRect(type[blkbishop]);

                chess.setPosition(boardPositions[0][5]);

                PieceVec.emplace_back(blkbishop, chess.getPosition(), chess);

            }

        }

        else if (i <= 14) {

            if (i == 13) {





                chess.setTextureRect(type[blkknight]);

                chess.setPosition(boardPositions[0][1]);



                PieceVec.emplace_back(blkknight, chess.getPosition(), chess);

            }

            else

            {



                chess.setTextureRect(type[blkknight]);

                chess.setPosition(boardPositions[0][6]);



                PieceVec.emplace_back(blkknight, chess.getPosition(), chess);

            }

        }

        else if (i == 15)

        {

            chess.setTextureRect(type[blkqueen]);

            chess.setPosition(boardPositions[0][3]);



            PieceVec.emplace_back(blkqueen, chess.getPosition(), chess);

        }

        else if (i == 16) {

            chess.setTextureRect(type[blkking]);

            chess.setPosition(boardPositions[0][4]);



            PieceVec.emplace_back(blkking, chess.getPosition(), chess);

        }

    }



    //displays white pieces and moves them into positon   

    for (int i = 1; i <= 16; i++) {

        sf::Sprite chess(pieces);

        chess.setScale({ 0.75f, 0.7f });



        if (i <= 8) {

            chess.setTextureRect(type[whtpawn]);

            chess.setPosition(boardPositions[6][i - 1]);



            PieceVec.emplace_back(whtpawn, chess.getPosition(), chess);

        }

        else if (i <= 10) {

            if (i == 9) {

                chess.setTextureRect(type[whtrook]);

                chess.setPosition(boardPositions[7][0]);



                PieceVec.emplace_back(whtrook, chess.getPosition(), chess);

            }

            else {

                chess.setTextureRect(type[whtrook]);

                chess.setPosition(boardPositions[7][7]);



                PieceVec.emplace_back(whtrook, chess.getPosition(), chess);

            }

        }

        else if (i <= 12) {

            if (i == 11) {

                chess.setTextureRect(type[whtbishop]);

                chess.setPosition(boardPositions[7][2]);



                PieceVec.emplace_back(whtbishop, chess.getPosition(), chess);

            }

            else {

                chess.setTextureRect(type[whtbishop]);

                chess.setPosition(boardPositions[7][5]);



                PieceVec.emplace_back(whtbishop, chess.getPosition(), chess);

            }

        }

        else if (i <= 14) {

            if (i == 13) {

                chess.setTextureRect(type[whtknight]);

                chess.setPosition(boardPositions[7][1]);



                PieceVec.emplace_back(whtknight, chess.getPosition(), chess);

            }

            else {

                chess.setTextureRect(type[whtknight]);

                chess.setPosition(boardPositions[7][6]);



                PieceVec.emplace_back(whtknight, chess.getPosition(), chess);

            }

        }

        else if (i == 15) {

            chess.setTextureRect(type[whtqueen]);

            chess.setPosition(boardPositions[7][3]);



            PieceVec.emplace_back(whtqueen, chess.getPosition(), chess);

        }

        else if (i == 16) {

            chess.setTextureRect(type[whtking]);

            chess.setPosition(boardPositions[7][4]);



            PieceVec.emplace_back(whtking, chess.getPosition(), chess);

        }

    }


    int selectedPieceIndex = -1;



    for (int i = 0; i < 27; i++) {
        circles[i].setPosition({ -1000,-1000 });
    }

    bool iswhitesturn = true;
    // Main loop   

    while (window->isOpen()) {



        while (const std::optional event = window->pollEvent()) {

            if (event->is<sf::Event::Closed>()) {

                window->close();

            }

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {

                    window->close();

                }

            }

        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

            //gets the position of the mouse and maps it to a coord on the window   

            sf::Vector2i mousepos = sf::Mouse::getPosition(*window);

            sf::Vector2f worldPos = window->mapPixelToCoords(mousepos);
            
            square.setPosition({ -1000,-1000 });

            bool theCirclePlayed = false;

            if (iswhitesturn) {

                //checks clicked on circle
                for (int i = 16; i < 32; i++) {
                    for (int i = 0; i < 27; i++) {

                        if (circles[i].getGlobalBounds().contains(worldPos) && selectedPieceIndex != -1) {

                            // Move the piece to the selected circle's position 

                            PieceVec[selectedPieceIndex].pieceSprite.setPosition(circles[i].getPosition());

                            PieceVec[selectedPieceIndex].piecePosition = circles[i].getPosition();

                            // logic for capturing a piece 

                            for (int i = 0; i < 16; i++) {

                                int capture = i;

                                if (PieceVec[selectedPieceIndex].piecePosition == PieceVec[capture].piecePosition) {

                                    PieceVec[capture].pieceSprite.setPosition({ -1000.f, -1000.f });

                                    PieceVec[capture].piecePosition = { -1000.f, -1000.f };

                                }

                            }


                            square.setPosition({ -1000.f, -1000.f });

                            // Deselect the piece after moving 

                            selectedPieceIndex = -1;

                            iswhitesturn = false;

                            theCirclePlayed = true;
                        }

                    }

                    if (theCirclePlayed == true) {
                        for (auto& dot : circles) {

                            dot.setPosition({ -1000.f, -1000.f });

                        }

                        selectedPieceIndex = i;
                    }

                    if (PieceVec[i].pieceSprite.getGlobalBounds().contains(worldPos) && theCirclePlayed == false) {

                        if (PieceVec[i].pieceType == whtrook) {

                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;


                            sf::Vector2f rookPos = PieceVec[i].piecePosition;

                            square.setPosition(rookPos);

                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (rookPos == boardPositions[col][row]) {



                                        int circleIndex = 0;





                                        for (int x = col - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsWhite) {

                                                break; // Stop placing circles — a piece is in the way   

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }

                                            if (containsWhite) {

                                                break;

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }

                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;


                                        }

                                        for (int x = col + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsWhite) {

                                                break; // Stop placing circles — a piece is in the way   

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }





                                            if (containsWhite) {

                                                break;

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;
                                        }

                                    }

                                }



                            }

                        }

                        else if (PieceVec[i].pieceType == whtknight){

                            
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;


                            sf::Vector2f knightPos = PieceVec[i].piecePosition;

                            square.setPosition(knightPos);





                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (knightPos == boardPositions[col][row]) {



                                        std::vector<sf::Vector2f> knightMoves = {

                                        {2, 1}, { 2, -1 }, { -2, 1}, { -2, -1},

                                            {1, 2}, {1, -2}, { -1, 2}, { -1, -2}

                                        };



                                        int circleIndex = 0;

                                        for (int m = 0; m < knightMoves.size(); m++) {

                                            int newCol = col + knightMoves[m].x;

                                            int newRow = row + knightMoves[m].y;



                                            if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                sf::Vector2f update = boardPositions[newCol][newRow];



                                                bool containsWhite = false;

                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == update) {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }



                                                if (!containsWhite) {

                                                    circles[circleIndex].setPosition(update);

                                                    circleIndex++;

                                                }

                                            }

                                        }



                                    }

                                }

                            }

                        }

                        else if (PieceVec[i].pieceType == whtbishop) {

                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f bishopPos = PieceVec[i].piecePosition;

                            square.setPosition(bishopPos);



                            // find rook's board position  

                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (bishopPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> bishopMoves = {

                                            { -1,-1},

                                            {1,-1},

                                            {-1,1},

                                            {1, 1}

                                        };





                                        for (int m = 0; m < bishopMoves.size(); m++) {

                                            int newCol = col + bishopMoves[m].x;

                                            int newRow = row + bishopMoves[m].y;







                                            while (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                bool containsWhite = false;

                                                bool containsBlack = false;



                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                if (containsWhite) {

                                                    break; // Stop placing circles — a piece is in the way   

                                                }

                                                if (containsBlack) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    break;

                                                }



                                                circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                circleIndex++;



                                                newCol += bishopMoves[m].x;

                                                newRow += bishopMoves[m].y;





                                            }



                                        }

                                    }

                                }

                            }

                        }

                        else if (PieceVec[i].pieceType == whtqueen) {

                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f queenPos = PieceVec[i].piecePosition;

                            square.setPosition(queenPos);

                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (queenPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> queenMoves = {

                                            {-1, -1},

                                            { 0, -1},

                                            { 1, -1},

                                            {-1,  0},

                                            { 1,  0},

                                            {-1,  1},

                                            { 0,  1},

                                            { 1,  1}

                                        };






                                        for (int m = 0; m < queenMoves.size(); m++) {

                                            int newCol = col + queenMoves[m].x;

                                            int newRow = row + queenMoves[m].y;







                                            while (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                bool containsWhite = false;

                                                bool containsBlack = false;



                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                if (containsWhite) {

                                                    break;

                                                }

                                                if (containsBlack) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    break;

                                                }



                                                circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                circleIndex++;



                                                newCol += queenMoves[m].x;

                                                newRow += queenMoves[m].y;





                                            }



                                        }





                                        for (int x = col - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsWhite) {

                                                break;

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }





                                            if (containsWhite) {

                                                break;

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;





                                        }

                                        for (int x = col + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsWhite) {

                                                break; // Stop placing circles — a piece is in the way   

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }





                                            if (containsWhite) {

                                                break;

                                            }

                                            if (containsBlack) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;





                                        }









                                    }

                                }

                            }

                        }

                        else if (PieceVec[i].pieceType == whtking) {

                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f kingPos = PieceVec[i].piecePosition;

                            square.setPosition(kingPos);





                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (kingPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> kingMoves = {

                                            {-1, -1},

                                            { 0, -1},

                                            { 1, -1},

                                            {-1,  0},

                                            { 1,  0},

                                            {-1,  1},

                                            { 0,  1},

                                            { 1,  1}

                                        };





                                        for (int m = 0; m < kingMoves.size(); m++) {

                                            int newCol = col + kingMoves[m].x;

                                            int newRow = row + kingMoves[m].y;



                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                if (containsWhite) {

                                                    continue;

                                                }

                                                if (containsBlack) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    continue;

                                                }



                                                circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                circleIndex++;

                                            }

                                        }

                                    }

                                }

                            }



                        }

                        else if (PieceVec[i].pieceType == whtpawn) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f pawnPos = PieceVec[i].piecePosition;

                            square.setPosition(pawnPos);





                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (pawnPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> pawnMoves = {

                                            {-1,-1},

                                            { -1,0},

                                            { -1,  1}

                                        };





                                        for (int m = 0; m < pawnMoves.size(); m++) {

                                            int newCol = col + pawnMoves[m].x;

                                            int newRow = row + pawnMoves[m].y;



                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                //Stops if it contains Black 

                                                if (containsWhite) {

                                                    continue;

                                                }





                                                //Stops after placing a circle on the square if it is not the square in front of it  

                                                if (containsBlack && pawnMoves[m] != sf::Vector2f{ 1,0 }) {



                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    continue;

                                                }

                                                else if (containsBlack && pawnMoves[m] == sf::Vector2f{ -1,0 }) {

                                                    continue;

                                                }

                                                else if (pawnMoves[m] == sf::Vector2f{ -1,0 }) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    if (col == 6) {

                                                        bool hasblack = false;

                                                        bool haswhite = false;



                                                        int tempcol = newCol;

                                                        int tempRow = newRow;



                                                        for (int j = 0; j < 32; j++) {

                                                            if (PieceVec[j].piecePosition == boardPositions[tempcol - 1][tempRow]) {

                                                                if (j < 16) {

                                                                    hasblack = true;

                                                                }

                                                                else

                                                                {

                                                                    haswhite = true;

                                                                    break;

                                                                }

                                                            }

                                                        }

                                                        if (hasblack) {

                                                            continue;

                                                        }

                                                        if (haswhite) {

                                                            continue;

                                                        }

                                                        circles[circleIndex].setPosition(boardPositions[newCol - 1][newRow]);

                                                        circleIndex++;





                                                    }

                                                    continue;

                                                }



                                            }



















                                        }

                                    }

                                }

                            }

                        }

                    }

                }
             
            }

            else {
                //checks clicked on circle
                for (int i = 16; i < 32; i++) {
                    for (int i = 0; i < 27; i++) {

                        if (circles[i].getGlobalBounds().contains(worldPos) && selectedPieceIndex != -1) {

                            // Move the piece to the selected circle's position 

                            PieceVec[selectedPieceIndex].pieceSprite.setPosition(circles[i].getPosition());

                            PieceVec[selectedPieceIndex].piecePosition = circles[i].getPosition();

                            // logic for capturing a piece 

                            for (int i = 16; i < 32; i++) {

                                int capture = i;

                                if (PieceVec[selectedPieceIndex].piecePosition == PieceVec[capture].piecePosition) {

                                    PieceVec[capture].pieceSprite.setPosition({ -1000.f, -1000.f });

                                    PieceVec[capture].piecePosition = { -1000.f, -1000.f };

                                }

                            }
                            

                            square.setPosition({ -1000.f, -1000.f });

                            // Deselect the piece after moving 

                            selectedPieceIndex = -1;

                            iswhitesturn = true;

                            theCirclePlayed = true;

                        }

                    }

                for (int i = 0; i < 16; i++) {
                    if (theCirclePlayed == true) {
                        for (auto& dot : circles) {

                            dot.setPosition({ -1000.f, -1000.f });

                        }

                        selectedPieceIndex = i;
                    }

                    if (PieceVec[i].pieceSprite.getGlobalBounds().contains(worldPos) && theCirclePlayed == false) {

                        if (PieceVec[i].pieceType == blkrook) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f rookPos = PieceVec[i].piecePosition;

                            square.setPosition(rookPos);

                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (rookPos == boardPositions[col][row]) {



                                        int circleIndex = 0;





                                        for (int x = col - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsBlack) {

                                                break; // Stop placing circles — a piece is in the way   

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }


                                            if (containsBlack) {

                                                break;

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }

                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;
                                        }

                                        for (int x = col + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsBlack) {

                                                break; // Stop placing circles — a piece is in the way   

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }





                                            if (containsBlack) {

                                                break;

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;





                                        }





                                    }

                                }



                            }







                            iswhitesturn = false; // switch turn after valid selection  

                            break;

                        }
                        else if (PieceVec[i].pieceType == blkknight) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f knightPos = PieceVec[i].piecePosition;

                            square.setPosition(knightPos);





                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (knightPos == boardPositions[col][row]) {



                                        std::vector<sf::Vector2f> knightMoves = {

                                        {2, 1}, {2, -1}, { -2, 1}, { -2, -1},

                                            {1, 2}, {1, -2}, { -1, 2}, { -1, -2}

                                        };



                                        int circleIndex = 0;

                                        for (int m = 0; m < knightMoves.size(); m++) {

                                            int newCol = col + knightMoves[m].x;

                                            int newRow = row + knightMoves[m].y;



                                            if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                sf::Vector2f knightPos = boardPositions[newCol][newRow];



                                                bool containsBlack = false;

                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == knightPos) {

                                                        containsBlack = true;

                                                        break;

                                                    }

                                                }



                                                if (!containsBlack) {

                                                    circles[circleIndex].setPosition(knightPos);

                                                    circleIndex++;

                                                }

                                            }

                                        }



                                    }

                                }

                            }

                        }
                        else if (PieceVec[i].pieceType == blkbishop) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f bishopPos = PieceVec[i].piecePosition;

                            square.setPosition(bishopPos);



                            // find rook's board position  

                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (bishopPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> bishopMoves = {

                                            { -1,-1},

                                            {1,-1},

                                            {-1,1},

                                            {1, 1}

                                        };





                                        for (int m = 0; m < bishopMoves.size(); m++) {

                                            int newCol = col + bishopMoves[m].x;

                                            int newRow = row + bishopMoves[m].y;



                                            while (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                bool containsWhite = false;

                                                bool containsBlack = false;



                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                if (containsBlack) {

                                                    break;

                                                }

                                                if (containsWhite) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    break;

                                                }



                                                circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                circleIndex++;



                                                newCol += bishopMoves[m].x;

                                                newRow += bishopMoves[m].y;





                                            }



                                        }

                                    }

                                }

                            }

                        }
                        else if (PieceVec[i].pieceType == blkqueen) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f queenPos = PieceVec[i].piecePosition;

                            square.setPosition(queenPos);



                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (queenPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> queenMoves = {

                                            { -1, -1},

                                            { -1,0 },

                                            {0,-1 },

                                            {1,0},

                                            {0,1},

                                            {1,-1},

                                            {-1,1},

                                            {1, 1}

                                        };



                                        for (int m = 0; m < queenMoves.size(); m++) {

                                            int newCol = col + queenMoves[m].x;

                                            int newRow = row + queenMoves[m].y;



                                            while (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                bool containsWhite = false;

                                                bool containsBlack = false;



                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                if (containsBlack) {

                                                    break;

                                                }

                                                if (containsWhite) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    break;

                                                }



                                                circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                circleIndex++;



                                                newCol += queenMoves[m].x;

                                                newRow += queenMoves[m].y;

                                            }



                                        }





                                        for (int x = col - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsBlack) {

                                                break;

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row - 1; x >= 0; x--) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }





                                            if (containsBlack) {

                                                break;

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;





                                        }

                                        for (int x = col + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[x][row]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }



                                            if (containsBlack) {

                                                break; // Stop placing circles — a piece is in the way   

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[x][row]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[x][row]);

                                            circleIndex++;

                                        }

                                        for (int x = row + 1; x <= 7; x++) {

                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            for (int j = 0; j < 32; j++) {

                                                if (PieceVec[j].piecePosition == boardPositions[col][x]) {

                                                    if (j < 16) {

                                                        containsBlack = true;

                                                    }

                                                    else

                                                    {

                                                        containsWhite = true;

                                                        break;

                                                    }

                                                }

                                            }





                                            if (containsBlack) {

                                                break;

                                            }

                                            if (containsWhite) {

                                                circles[circleIndex].setPosition(boardPositions[col][x]);

                                                circleIndex++;

                                                break;

                                            }



                                            circles[circleIndex].setPosition(boardPositions[col][x]);

                                            circleIndex++;





                                        }









                                    }

                                }

                            }

                        }
                        else if (PieceVec[i].pieceType == blkking) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f kingPos = PieceVec[i].piecePosition;

                            square.setPosition(kingPos);





                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (kingPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> kingMoves = {

                                            {-1, -1},

                                            { 0, -1},

                                            { 1, -1},

                                            {-1,  0},

                                            { 1,  0},

                                            {-1,  1},

                                            { 0,  1},

                                            { 1,  1}

                                        };





                                        for (int m = 0; m < kingMoves.size(); m++) {

                                            int newCol = col + kingMoves[m].x;

                                            int newRow = row + kingMoves[m].y;



                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                if (containsBlack) {

                                                    continue;

                                                }

                                                if (containsWhite) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    continue;

                                                }



                                                circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                circleIndex++;

                                            }

                                        }

                                    }

                                }

                            }



                        }
                        else if (PieceVec[i].pieceType == blkpawn) {
                            for (auto& dot : circles) {

                                dot.setPosition({ -1000.f, -1000.f });

                            }

                            selectedPieceIndex = i;

                            sf::Vector2f pawnPos = PieceVec[i].piecePosition;

                            square.setPosition(pawnPos);





                            for (int row = 0; row < 8; row++) {

                                for (int col = 0; col < 8; col++) {

                                    if (pawnPos == boardPositions[col][row]) {



                                        int circleIndex = 0;



                                        std::vector<sf::Vector2f> pawnMoves = {

                                            {1,-1},

                                            { 1,0},

                                            { 1,  1}

                                        };





                                        for (int m = 0; m < pawnMoves.size(); m++) {

                                            int newCol = col + pawnMoves[m].x;

                                            int newRow = row + pawnMoves[m].y;



                                            bool containsWhite = false;

                                            bool containsBlack = false;



                                            if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {

                                                for (int j = 0; j < 32; j++) {

                                                    if (PieceVec[j].piecePosition == boardPositions[newCol][newRow]) {

                                                        if (j < 16) {

                                                            containsBlack = true;

                                                        }

                                                        else

                                                        {

                                                            containsWhite = true;

                                                            break;

                                                        }

                                                    }

                                                }



                                                //Stops if it contains Black 

                                                if (containsBlack) {

                                                    continue;

                                                }





                                                //Stops after placing a circle on the square if it is not the square in front of it  

                                                if (containsWhite && pawnMoves[m] != sf::Vector2f{ 1,0 }) {



                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    continue;

                                                }

                                                else if (containsWhite && pawnMoves[m] == sf::Vector2f{ 1,0 }) {

                                                    continue;

                                                }

                                                else if (pawnMoves[m] == sf::Vector2f{ 1,0 }) {

                                                    circles[circleIndex].setPosition(boardPositions[newCol][newRow]);

                                                    circleIndex++;

                                                    if (col == 1) {

                                                        bool hasblack = false;

                                                        bool haswhite = false;



                                                        int tempcol = newCol;

                                                        int tempRow = newRow;



                                                        for (int j = 0; j < 32; j++) {

                                                            if (PieceVec[j].piecePosition == boardPositions[tempcol + 1][tempRow]) {

                                                                if (j < 16) {

                                                                    hasblack = true;

                                                                }

                                                                else

                                                                {

                                                                    haswhite = true;

                                                                    break;

                                                                }

                                                            }

                                                        }

                                                        if (hasblack) {

                                                            continue;

                                                        }

                                                        if (haswhite) {

                                                            continue;

                                                        }

                                                        circles[circleIndex].setPosition(boardPositions[newCol + 1][newRow]);

                                                        circleIndex++;





                                                    }

                                                    continue;

                                                }

















                                            }

                                        }

                                    }

                                }

                            }

                        }

                        

                    }
                }
            }
         }

         }


        window->clear(sf::Color(118, 92, 72));

        window->draw(board);





        for (int i = 0; i < PieceVec.size(); i++) {

            window->draw(PieceVec[i].pieceSprite);

        }

        window->draw(square);

        for (int i = 0; i < 27; i++) {



            window->draw(circles[i]);

        }
        if (PieceVec[15].piecePosition == check.getPosition()) {

            window->draw(whtwin);

        }

        if (PieceVec[31].piecePosition == check.getPosition()) {

            window->draw(blkwin);

        }
        window->display(); 
    }
}



