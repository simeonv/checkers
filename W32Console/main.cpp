#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef int player;

//// CONSTANTS
// The dimensions of the playing surface (zero-based)
static const int BOARDHEIGHT = 8;
static const int BOARDWIDTH  = 8;

// The "color" played by a given user. Color selection determines order of
// play and side of the board used.
enum Team
{
  black,   // "dark" color common in USA 
  red = 0, // "dark" color common in England
  white    // standard "light" color
};

// Basic information about a "draught" or piece on the board.
struct draught
{
  Team player;   // Color played by the current player (black or white)
  //Position pos;  // Position of the draught.
  
  // xloc - Distance from left edge   (1 = leftmost,   BOARDHEIGHT = rightmost)
  // yloc - Distance from bottom edge (1 = bottommost, BOARDWIDTH  = topmost)
};

// Board location. Specifies the location of a draught or
// where the user would like to move a draught. 
struct location
{
  int y; // 1 character numeric value [1-8]
  int x; // 1 character numeric value [1-8] -- maps to [a-h]
};

// Convert position notation into board row and column coordinates.
void posToCord(int pos, int& row, int& col)
{
  // Row and column converstion notes:
  // 
  // * Rows - distance from board's bottom edge.
  // * Cols - distance from board's left edge.
  //
  // Rows are straight forward, but columns have special rules that determine
  // the coordinates of valid positions.

  // Convert position to zer-based index
  pos -= 1;

  //// ROW CALCULATION
  // Row number = quotient of (position / positions per row)
  row = pos / 4;
  
  //// COL CALCULATION
  // Initial col value = remainder of (position / positions per row)
  col = pos % 4;

  // Col now represents a position offest from the right side, but we need the
  // column offset from the left side. To get this value we must 
  //
  // 1. Derive an offset of positions from the right side.
  // 2. Add additional spaces based on distance from right
  // 3. Adjust for odd/even row count.

  // Step 1. Derive offset from right (0..3)
  col = 3 - col;
  // Step 2. Adjust for additional spaces (2 spaces for every 1 unit from left)
  col *= 2;
  // Step 3. Adjust even rows (even board rows are odd due to zero-based index)
  if (row % 2 != 0)
  {
    col += 1;
  }
};

bool isValidInputFormat()
{
  // Check string lenght; expecting 2 characters
  // Check string contents; expecting 1 alpha, 1 numeric
  //   Store alpha and numeric as seperate vars
  //   Convert numeric to zero-based numeric y coord value
  //   Convert alpha to zero-based numeric x coord value
  //
  // if success: return true, update x and y coords
  return true;
};

//bool isValidCoord(string userInput, Position pos)
//{
//  // Verify that x,y coords point to a valid position
//  // 
//  // if success: return true, update pos with position
//  return true;
//};

//void IsMoveValid(Position draughtLoc, Position targetLoc)
//{};

void DrawCell()
{

}

// User enters coordinates. Specifies draught and targets.
//  - Entered as a number-leter combination (e.g. 1a 5d, etc.)
//  - May enter target as where they want to move or the piece to jump.
// System stores positions. Must properly handle coords; this includes:
//  - Convert user input to meaingful data.
//  - Convert internal data to user-understandable output.
//    - Board view
//    - Coordinate map
//    - Meaningful error messages
//  - Validate user input
//    - Draught must be a valid draught location (e.g. D2=valid, D3=invalid)
//      - convert coord to position, error if invalid
//      - valide current user owns draught, error if invalid
//    - Target may be empty space, draught to jump, or location after jump
//      - convert coord to position, error if invalid
//      - check if target is a valid position, error if not
//      - check if location is free or contains a draught
//        - if target = draught
//          - check if druaght is owned by other player, error if not
//          - check if draught is in an attackable location, error if not
//          - check if location behind draught is clear, error if not
//        - if target = free, may be a direct move or jump...
//          - check if location is 1 or 2 moves away, error if not
//          - if 1 move away and clear it is a move. execute
//          - if 1 move away and contains a draught, it is a jump.
//            - check if position after draught is clear, if not error
//          - if 2 moves away (and clear) it is a jump
//            - verify that move sequence is diagonal (e.g. 2-11 okay, 2-10 bad, 2-9 okay)
//            - verify that enemy draught appears in the interveining space, error if not
//   ^ Need to add checks to make sure target does not ignore a possible jump.

int main ()
{
  vector<draught> draughts;
  
  //TODO Move this to the body of the draw function
  int row = 0;
  int column = 0;

  // Box characters
  // http://msdn.microsoft.com/en-us/library/9hxt0028(VS.80).aspx
  //
  // TL \xDA    TS \xC4    TC \xC2    TR \xBF
  // LS \xB3         MC \xC5          RS \xB3
  // LC \xC3                          RC \xB4
  // BL \xC0    BS \xC4    BC \xC1    BR \xD9

    for (int i = 0; i != BOARDHEIGHT; i++)
  {
    // If this is the first pass through, draw extra top row.
    if (i == 0)
    { 
      for (int j = 0; j != BOARDWIDTH; j++)
      {
        if (j == 0)
        { // first column, top left corner (┌)
          cout << "\xDA"; 
        }

        // Top edge
        cout << "\xC4\xC4\xC4";

        if (j != BOARDWIDTH - 1)
        { // Not last column, internal top edge (┬)
          cout << "\xC2";
        }
        else
        { // Last column, top right corner (┐)
          cout << "\xBF";
        }
      }
      cout << endl;
    }

    for (int j = 0; j != BOARDWIDTH; j++)
    {
      // ----------------------------------------
      // CELL BODY

      // body left edge
      cout << "\xB3";

      // body text
      string temp = "x";
      cout << " " << temp << " ";

      // body right edge
      if (j == BOARDWIDTH - 1)
      {
        cout << "\xB3";
      }
      // End line
    }
    cout << endl;

    for (int j = 0; j != BOARDWIDTH; j++)
    {
      // ----------------------------------------
      // CELL'S BOTTOM EDGE

      // Left element in the repeating bottom edge string
      if (j == 0) 
      { // Not first column ...
        if (i != BOARDHEIGHT - 1)
        { // Not the last row, left edge (├)
          cout << "\xC3";
        }
        else
        { // Last row, bottom left corner (└)
          cout << "\xC0";
        }
      }
      else 
      { // Not first column ...
        if (i != BOARDHEIGHT - 1) 
        { // Not last row, internal intersection (┼)
          cout << "\xC5";
        }
        else
        { // Last row, bottom edge (┴)
          cout << "\xC1";
        }
      }

      //// Straight bottom edge
      if ((i + j) % 2)
      {
        cout << "\xFA\xFA\xFA";
      }
      else
      {
        cout << "\xC4\xC4\xC4";
      }
      
      // ----------------------------------------
      // CELL'S RIGHT EDGE
      // Top right corner is handled seperately

      if (j == BOARDWIDTH - 1)
      {
        if (i != BOARDHEIGHT - 1)  
        { // Not last column, internal right edge (┤)
          cout << "\xB4";  
        }
        else
        { // Last column, bottom right corner (┘)
          cout << "\xD9";        
        }
      }
    }
    cout << endl;
  }

  //while (true)
  //{
  //  cout << "Enter position (Ctlr-Z to exit): ";

  //  if (!(cin >> pos))
  //  {
  //    break;
  //  }

  //  int row = 0,
  //    col = 0;
  //  posToCord(pos, row, col);

  //  // Print results
  //  cout << "Row:"     << row << endl;
  //  cout << "Column: " << col << endl;
  //}
  return 0;
}