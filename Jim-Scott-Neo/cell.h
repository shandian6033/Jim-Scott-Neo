#ifndef  CELL_H
#define CELL_H
class cell
{

public:
    cell(int, int);

    void SetPiece(char);
    void UpCopy();

private:
    int row_coor;
    int col_coor;
    char state;

    cell* left;
    cell* right;
    cell* up;
    cell* down;

};
#endif


